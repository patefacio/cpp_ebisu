#ifndef __FCS_UTILS_STREAMERS_TABLE_TABLE_HPP__
#define __FCS_UTILS_STREAMERS_TABLE_TABLE_HPP__

#include "fcs/utils/streamers/containers.hpp"
#include <boost/lexical_cast.hpp>
#include <boost/range.hpp>
#include <algorithm>
#include <iostream>
#include <vector>

namespace fcs {
namespace utils {
namespace streamers {
namespace table {
  // custom <FcbBeginNamespace table>
  // end <FcbBeginNamespace table>

  //! Outputs data in tabular format - like output from database query
  template< typename MatrixContainer,
            typename T = typename MatrixContainer::value_type::value_type >
  class Table_streamer
  {
  public:
    Table_streamer(
      MatrixContainer const & matrix_container,
      String_list_t const & header = String_list_t()) :
      matrix_container_ { matrix_container },
      header_ { header } {
    }

    friend inline
    std::ostream& operator<<(std::ostream &out, Table_streamer const& item) {
      using fcs::utils::streamers::operator<<;
      fcs::utils::Block_indenter indenter;
      char const* indent(indenter.current_indentation_text());
      out << '\n' << indent << "Table_streamer(" << &item << ") {";
      out << '\n' << indent << "  matrix_container:" << item.matrix_container_;
      out << '\n' << indent << "  header:" << item.header_;
      out << '\n' << indent << "}\n";
      return out;
    }

    // custom <ClsPublic Table_streamer>
    // end <ClsPublic Table_streamer>

  private:
    //! Matrix with data to stream
    MatrixContainer const& matrix_container_;
    //! List of headers for the columns
    String_list_t const& header_;

  };

} // namespace table
} // namespace streamers
} // namespace utils
} // namespace fcs
#endif // __FCS_UTILS_STREAMERS_TABLE_TABLE_HPP__
