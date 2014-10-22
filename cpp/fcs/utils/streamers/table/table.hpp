#ifndef __FCS_UTILS_STREAMERS_TABLE_TABLE_HPP__
#define __FCS_UTILS_STREAMERS_TABLE_TABLE_HPP__

#include "fcs/utils/block_indenter.hpp"
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

  using String_list_t = std::vector< std::string >;
  using String_matrix_t = std::vector< String_list_t >;
  using Size_list_t = std::vector< size_t >;

  //! Outputs data in tabular format - like output from database query
  // custom <ClsPreDecl Table_streamer>

  inline void grow_string_to(std::string &s, size_t len) {
    s += std::string(len-s.size(), ' ');
  }

  template < typename T >
  inline
  void to_string(T const& t, std::string &result) {
    result = boost::lexical_cast< std::string >(t);
  }

  template < >
  inline
  void to_string(bool const& t, std::string &result) {
    result = (t? "T" : "F");
  }

  template < >
  inline
  void to_string(std::string const& t, std::string &result) {
    result = t;
  }

  inline void print_string_row(std::ostream & out, String_list_t & row,
                               Size_list_t const& size_list,
                               char spacer = ' ', char sep = '|') {
    size_t const num_columns(row.size());
    if(num_columns) {
      size_t const last_index(num_columns - 1);
      out << sep << spacer;
      for(size_t column(0); column < num_columns; ++column) {
        grow_string_to(row[column], size_list[column]);
        out << row[column] << spacer << sep;
        if(column != last_index) {
          out << spacer;
        }
      }
      out << '\n';
    }
  }

  template < typename T, typename ALLOC, typename ALLOC_OUTER >
  inline void make_string_matrix(std::vector< std::vector< T, ALLOC >, ALLOC_OUTER > const& v,
                                 String_matrix_t &result) {
    result.clear();
    for(auto const& src_row : v) {
      String_list_t row;
      for(auto const& cell : src_row) {
        row.push_back(boost::lexical_cast< std::string >(cell));
      }
      result.push_back(row);
    }
  }

  //! Support for streaming std::vector
  template < typename T, typename ALLOC, typename ALLOC_OUTER >
  inline std::ostream& operator<<(std::ostream& out,
                                  std::vector< std::vector< T, ALLOC >, ALLOC_OUTER > const& matrix) {
    String_matrix_t string_matrix;
    make_string_matrix(matrix, string_matrix);
    out << string_matrix;
    return out;
  }

  template < typename ALLOC, typename ALLOC_OUTER >
  inline std::ostream& operator<<(std::ostream& out,
                                  std::vector< std::vector< std::string, ALLOC >, ALLOC_OUTER > const& v) {
    typedef std::vector< std::string, ALLOC > Row_t;
    typedef std::vector< Row_t > Row_list_t;
    typedef std::vector< size_t > Size_list_t;
    if(v.size()) {
      size_t column_size(v[0].size());
      Size_list_t size_list(column_size, 0);
      typename Row_list_t::const_iterator row_it(v.begin());
      typename Row_list_t::const_iterator row_end(v.end());
      for( ; row_it != row_end; ++row_it) {
        size_t cell_index(0);
        typename Row_t::const_iterator cell_it(row_it->begin());
        typename Row_t::const_iterator cell_end(row_it->end());
        for( ; cell_it != cell_end; ++cell_it, ++cell_index) {
          size_list[cell_index] = std::max(size_list[cell_index], cell_it->size() + 1);
        }
      }

      row_it = v.begin();
      row_end = v.end();
      for( ; row_it != row_end; ++row_it) {
        Row_t row(*row_it);
        print_string_row(out, row, size_list);
      }
    }

    return out;
  }

  // end <ClsPreDecl Table_streamer>

  template< typename MatrixContainer = String_matrix_t,
            typename T = typename MatrixContainer::value_type::value_type >
  class Table_streamer
  {
  public:
    using Row_container_t = typename MatrixContainer::value_type;

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

    inline void print_string_table(std::ostream &out) const {
      String_matrix_t string_matrix;

      if(!matrix_container_.empty()) {
        Row_container_t const& first_row(matrix_container_[0]);
        size_t const num_columns(first_row.size());
        Size_list_t size_list;

        if(!header_.empty()) {
          string_matrix.push_back(header_);
          for(size_t i(0); i < header_.size(); ++i) {
            size_list.push_back(header_[i].size());
          }
        } else {
          size_list.assign(num_columns, 0);
        }

        typename MatrixContainer::const_iterator row_it(matrix_container_.begin());
        typename MatrixContainer::const_iterator row_end(matrix_container_.end());
        using fcs::utils::streamers::operator<<;
        for(; row_it != row_end; ++row_it) {
          String_list_t row;
          typename Row_container_t::const_iterator cell_it(row_it->begin());
          typename Row_container_t::const_iterator cell_end(row_it->end());
          for(size_t i(0); cell_it != cell_end; ++cell_it, ++i) {
            std::string cell_value_text;
            to_string(*cell_it, cell_value_text);
            row.push_back(cell_value_text);
            size_list[i] = std::max(size_list[i], row.back().size());
          }
          string_matrix.push_back(row);
        }

        size_t const num_rows(string_matrix.size());
        std::string const empty;
        String_list_t divider(num_columns, empty);
        for(size_t column(0); column < num_columns; ++column) {
          std::string dashed(size_list[column], '-');
          std::swap(divider[column], dashed);
        }
        print_string_row(out, divider, size_list, '-', '|');
        print_string_row(out, string_matrix[0], size_list);
        print_string_row(out, divider, size_list, '-', '|');
        for(size_t row(1); row < num_rows; ++row) {
          print_string_row(out, string_matrix[row], size_list);
        }

      }
    }

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
