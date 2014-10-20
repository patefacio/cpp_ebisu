#include <boost/program_options.hpp>
#include <string>
#include <vector>

namespace fcs {
namespace app {
namespace h5ds2csv {
  struct Program_options
  {
  public:
    Program_options(int argc, char** argv) {
      using namespace boost::program_options;
      static options_description options {
        R"(
    Converts data_sets in hdf5 files to csv

    Allowed Options:
    )"
      };
      if(options.options().empty()) {
        options.add_options()
        ("help,h", "Display help information")
        ("data-set,d", value< std::vector< std::string > >(),
          "Name of data_set to make into csv")
        ("input-file,i", value< std::vector< std::string > >(),
          "Name of hdf5 file containing data_set(s)")
        ("output-file,o", value< std::string >(),
          "Name of hdf5 file containing data_set(s)");
      }
      variables_map parsed_options;
      store(parse_command_line(argc, argv, options), parsed_options);
      if(parsed_options.count("help") > 0) {
        help_ = true;
        return;
      }

      if(parsed_options.count("data_set") > 0) {
        data_set_ = parsed_options["data_set"]
          .as< std::vector< std::string > >();
      }

      if(parsed_options.count("input_file") > 0) {
        input_file_ = parsed_options["input_file"]
          .as< std::vector< std::string > >();
      } else {
        std::ostringstream msg;
        msg << "h5ds2csv option 'input_file' is required";
        throw std::runtime_error(msg.str());
      }

      if(parsed_options.count("output_file") > 0) {
        output_file_ = parsed_options["output_file"]
          .as< std::string >();
      }

    }
    friend inline std::ostream& operator<<(std::ostream& out, Program_options const& item) {
      out << '\n' << "help:" << item.help_;
      out << '\n' << "data_set:" << item.data_set_;
      out << '\n' << "input_file:" << item.input_file_;
      out << '\n' << "output_file:" << item.output_file_;
      return out;
    }

  private:
    bool help_ {};
    std::vector< std::string > data_set_ {};
    std::vector< std::string > input_file_ {};
    std::string output_file_ {};

  };


} // namespace h5ds2csv
} // namespace app
} // namespace fcs

int main(int argc, char** argv) {
  using namespace fcs::app::h5ds2csv;
  Program_options options = { argc, argv };

  return 0;
}
