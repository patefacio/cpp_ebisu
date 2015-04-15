#include "fcs/timestamp/conversion.hpp"
#include "fcs/utils/block_indenter.hpp"
#include "fcs/utils/streamers/containers.hpp"
#include "fcs/utils/streamers/table.hpp"
#include <boost/program_options.hpp>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace fcs {
namespace {
char const* app_descr = R"(
App for converting between various forms of date/time

Example:

> date_time_converter -t '2014-Oct-21 15:06:54.748639' -t 212280707214748639 -d 20010101 -d 2456952 -d 56951 -t 20010101T000000
|-----------------------------|--------------------|------------|------------------------|-----------------------------|-------------|---------|------------|
| input                       | ticks              | time_t     | iso                    | timestamp                   | date        | julian  | modjulian  |
|-----------------------------|--------------------|------------|------------------------|-----------------------------|-------------|---------|------------|
| min_date_time               | 192879360000000000 | -807574016 | 14000101T000000        | 1400-Jan-01 00:00:00        | 1400-Jan-01 | 2232400 | 4294799695 |
| min_date_time               | 464269103999999999 | -769665    | 99991231T235959.999999 | 9999-Dec-31 23:59:59.999999 | 9999-Dec-31 | 5373484 | 2973483    |
| now                         | 212285674057364146 | 1418870857 | 20141218T024737.364146 | 2014-Dec-18 02:47:37.364146 | 2014-Dec-18 | 2457010 | 57009      |
| 20010101                    | 211845110400000000 | 978307200  | 20010101T000000        | 2001-Jan-01 00:00:00        | 2001-Jan-01 | 2451911 | 51910      |
| 2456952                     | 212280652800000000 | 1413849600 | 20141021T000000        | 2014-Oct-21 00:00:00        | 2014-Oct-21 | 2456952 | 56951      |
| 56951                       | 212280652800000000 | 1413849600 | 20141021T000000        | 2014-Oct-21 00:00:00        | 2014-Oct-21 | 2456952 | 56951      |
| 2014-Oct-21 15:06:54.748639 | 212280707214748639 | 1413904014 | 20141021T150654.748639 | 2014-Oct-21 15:06:54.748639 | 2014-Oct-21 | 2456952 | 56951      |
| 212280707214748639          | 212280707214748639 | 1413904014 | 20141021T150654.748639 | 2014-Oct-21 15:06:54.748639 | 2014-Oct-21 | 2456952 | 56951      |
| 20010101T000000             | 211845110400000000 | 978307200  | 20010101T000000        | 2001-Jan-01 00:00:00        | 2001-Jan-01 | 2451911 | 51910      |


AllowedOptions)";
}

struct Program_options {
  Program_options(int argc, char** argv) {
    using namespace boost::program_options;
    variables_map parsed_options;
    store(parse_command_line(argc, argv, description()), parsed_options);
    if (parsed_options.count("help") > 0) {
      help_ = true;
      return;
    }

    if (parsed_options.count("timestamp") > 0) {
      timestamp_ = parsed_options["timestamp"].as<std::vector<std::string> >();
    }

    if (parsed_options.count("date") > 0) {
      date_ = parsed_options["date"].as<std::vector<std::string> >();
    }
  }

  static boost::program_options::options_description const& description() {
    using namespace boost::program_options;
    static options_description options{app_descr};

    if (options.options().empty()) {
      options.add_options()("help,h", "Display help information")(
          "timestamp,t", value<std::vector<std::string> >(),
          "Some form of timestamp")(
          "date,d", value<std::vector<std::string> >(), "Some form of date");
    }
    return options;
  }

  static void show_help(std::ostream& out) {
    out << description();
    out.flush();
  }

  friend inline std::ostream& operator<<(std::ostream& out,
                                         Program_options const& item) {
    using fcs::utils::streamers::operator<<;
    out << "Program_options(" << &item << ") {";
    out << "\n  help:" << item.help_;
    out << "\n  timestamp:" << item.timestamp_;
    out << "\n  date:" << item.date_;
    out << "\n}\n";
    return out;
  }

  //! getter for help_ (access is Ro)
  bool help() const { return help_; }

  //! getter for timestamp_ (access is Ro)
  std::vector<std::string> const& timestamp() const { return timestamp_; }

  //! getter for date_ (access is Ro)
  std::vector<std::string> const& date() const { return date_; }

 private:
  bool help_{};
  std::vector<std::string> timestamp_{};
  std::vector<std::string> date_{};
};

// custom <FcbEndNamespace date_time_converter>

void add_detail_row(fcs::utils::streamers::String_matrix_t& table,
                    std::string const& input, fcs::timestamp::Timestamp_t ts) {
  using namespace utils::streamers;
  using namespace fcs::timestamp;
  String_list_t row;
  Date_t date{ts.date()};
  row.push_back(input);
  row.push_back(boost::lexical_cast<std::string>(ticks(ts)));
  row.push_back(boost::lexical_cast<std::string>(to_time_t(ts)));
  row.push_back(boost::posix_time::to_iso_string(ts));
  row.push_back(boost::lexical_cast<std::string>(ts));
  row.push_back(boost::lexical_cast<std::string>(date));
  row.push_back(boost::lexical_cast<std::string>(date.julian_day()));
  row.push_back(boost::lexical_cast<std::string>(date.modjulian_day()));
  table.push_back(row);
}

// end <FcbEndNamespace date_time_converter>

}  // namespace fcs

int main(int argc, char** argv) {
  using namespace fcs;
  try {
    Program_options options = {argc, argv};
    if (options.help()) {
      Program_options::show_help(std::cout);
      return 0;
    }

    // custom <main>

    using namespace fcs::timestamp;
    using namespace fcs::utils::streamers;

    String_matrix_t table;
    // first add reference times
    add_detail_row(table, "min_date_time", boost::posix_time::min_date_time);
    add_detail_row(table, "min_date_time", boost::posix_time::max_date_time);
    add_detail_row(table, "now", current_time());
    add_detail_row(table, "epoch",
                   Timestamp_t{boost::gregorian::date(1970, 1, 1)});
    for (auto const& date_text : options.date()) {
      try {
        Date_t date;
        if (convert_to_date_from_undelimited_string(date_text, date)) {
          add_detail_row(table, date_text, Timestamp_t{date});
        } else if (convert_to_date_from_julian(date_text, date)) {
          try {
            add_detail_row(table, date_text, Timestamp_t{date});
          } catch (std::exception const& e) {
            if (convert_to_date_from_modjulian(date_text, date)) {
              add_detail_row(table, date_text, Timestamp_t{date});
            } else {
              std::cerr << "Could not figure out date for julian looking date: "
                        << date_text << std::endl;
            }
          }
        } else {
          std::cerr << "Could not figure out date: " << date_text << std::endl;
        }
      } catch (std::exception const& e) {
        std::cerr << "Failed to convert date: " << date_text
                  << " with exception: " << e.what() << std::endl;
      }
    }

    for (auto const& ts : options.timestamp()) {
      Timestamp_t timestamp;
      try {
        if (convert_to_timestamp_from_ticks(ts, timestamp) or
            convert_to_timestamp_from_iso(ts, timestamp) or
            convert_to_timestamp_from_string(ts, timestamp)) {
          add_detail_row(table, ts, timestamp);
        } else {
          throw std::invalid_argument(ts);
        }
      } catch (std::exception const& e) {
        std::cerr << "Failed to convert timestamp: " << ts
                  << " with exception: " << e.what() << std::endl;
      }
    }

    String_list_t header{"input",     "ticks", "time_t", "iso",
                         "timestamp", "date",  "julian", "modjulian"};
    Table_streamer<> table_streamer{table, header};
    table_streamer.print_string_table(std::cout);

    // end <main>

  } catch (std::exception const& e) {
    std::cout << "Caught exception: " << e.what() << std::endl;
    Program_options::show_help(std::cout);
    return -1;
  }

  return 0;
}
