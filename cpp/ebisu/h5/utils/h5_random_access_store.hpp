#ifndef __EBISU_H5_UTILS_H5_RANDOM_ACCESS_STORE_HPP__
#define __EBISU_H5_UTILS_H5_RANDOM_ACCESS_STORE_HPP__

#include "H5Cpp.h"
#include "H5File.h"
#include "H5PacketTable.h"
#include "ebisu/h5/utils/h5_utils_logging.hpp"
#include "ebisu/utils/streamers/array.hpp"
#include <boost/filesystem/path.hpp>
#include <array>
#include <exception>
#include <memory>
#include <string>

namespace ebisu {
namespace h5 {
namespace utils {
/**
 H5_random_access_store may create a packet table or be created from an
 existing packet table.
*/
enum Store_open_type { Open_create_e, Open_read_e };

inline char const* to_c_str(Store_open_type e) {
  switch (e) {
    case Store_open_type::Open_create_e:
      return "Open_create_e";
    case Store_open_type::Open_read_e:
      return "Open_read_e";
    default: { return "Invalid Store_open_type"; }
  }
}

inline std::ostream& operator<<(std::ostream& out, Store_open_type e) {
  return out << to_c_str(e);
}

/**
 Stores objects of type TYPE_STORED in an hdf5 data_set for basic random access
 whose hdf5 data_set type (when used for creation) is specified by
 H5_DATA_SET_SPECIFIER.

*/
template <typename TYPE_STORED>
class H5_random_access_store {
 public:
  using H5_file_sptr_t = std::shared_ptr<H5::H5File>;
  using Record_t = TYPE_STORED;
  using H5_data_set_specifier_t = typename Record_t::H5_data_set_specifier;
  using Group_id_list_t = std::vector<hid_t>;
  using Packet_table_uptr_t = std::unique_ptr<FL_PacketTable>;

  H5_random_access_store(H5_file_sptr_t const& file, Store_open_type open_type,
                         std::string const& group)
      : file_(file), open_type_(open_type), group_(group) {
    // custom <H5_random_access_store(create packet table)>

    group_ += H5_data_set_specifier_t::DATA_SET_NAME;
    switch (open_type_) {
      case Open_create_e: {
        make_groups_in_path();
        packet_table_ = std::make_unique<FL_PacketTable>(
            file_->getId(), const_cast<char*>(group_.c_str()),
            H5_data_set_specifier_t::instance().compound_data_type_id(), 1 << 8,
            5);
        break;
      }
      case Open_read_e: {
        packet_table_ = std::make_unique<FL_PacketTable>(
            file_->getId(), const_cast<char*>(group_.c_str()));
        break;
      }
    }

    // end <H5_random_access_store(create packet table)>
  }

  // custom <ClsPublic H5_random_access_store>

  hsize_t size() const { return packet_table_->GetPacketCount(); }

  void get(hsize_t index, TYPE_STORED& result) {
    if (packet_table_->GetPacket(index, &result) < 0) {
      std::ostringstream msg;
      msg << "Failed call to GetPacket";
      throw std::runtime_error(msg.str());
    }
  }

  void append(TYPE_STORED const& additional) {
    if (packet_table_->AppendPacket(const_cast<TYPE_STORED*>(&additional)) <
        0) {
      std::ostringstream msg;
      msg << "Failed call to AppendPacket";
      throw std::runtime_error(msg.str());
    }
  }

  // end <ClsPublic H5_random_access_store>

 private:
  // custom <ClsPrivate H5_random_access_store>

  void make_groups_in_path() {
    using namespace boost::filesystem;
    hid_t current_group_id(file_->getId());
    Group_id_list_t group_ids;
    {
      path path(group_);
      path::iterator it(path.begin());
      path::iterator end(path.end());
      ++it;
      for (; it != end; ++it) {
        std::string const& current_group(it->string());
        if (!H5Lexists(current_group_id, current_group.c_str(), H5P_DEFAULT)) {
          hid_t new_group_id(H5Gcreate(current_group_id, current_group.c_str(),
                                       H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT));
          H5_UTILS_TRACE("Creating group: {} result gid: {}",
                         current_group.c_str(), new_group_id);
          if (new_group_id > 0) {
            current_group_id = new_group_id;
          } else {
            std::ostringstream msg;
            msg << "Failed to create group: " << current_group;
            throw std::runtime_error(msg.str());
          }
        } else {
          hid_t existing_group_id(
              H5Gopen2(current_group_id, current_group.c_str(), H5P_DEFAULT));
          h5_utils_logger->info("Opening existing group: {} result gid: {}",
                                current_group.c_str(), existing_group_id);
          if (existing_group_id > 0) {
            current_group_id = existing_group_id;
          } else {
            std::ostringstream msg;
            msg << "Failed to open group: " << current_group;
            throw std::runtime_error(msg.str());
          }
        }
        group_ids.push_back(current_group_id);
      }
    }

    if (group_ids.size() > 1) {
      for (auto group_id : group_ids) {
        h5_utils_logger->info("Closing group gid: {}", group_id);
        H5Gclose(group_id);
      }
    }
  }

  // end <ClsPrivate H5_random_access_store>

  /**
   Pointer to file containing (or to contain) data set for random access
  */
  H5_file_sptr_t const file_;

  /**
   Determines if packet table will be created [open_create] or read [open_read]
  */
  Store_open_type const open_type_;

  /**
   The group indicating where to find the data set
  */
  std::string group_;

  /**
   Pointer to the packet table
  */
  Packet_table_uptr_t packet_table_{};
};

// custom <FcbEndNamespace h5_random_access_store>
// end <FcbEndNamespace h5_random_access_store>

}  // namespace utils
}  // namespace h5
}  // namespace ebisu

#endif  // __EBISU_H5_UTILS_H5_RANDOM_ACCESS_STORE_HPP__
