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
      header_ { header }) {
    }

    operator<<(TBD)

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
