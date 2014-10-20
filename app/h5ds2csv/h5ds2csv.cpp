#include "fcs/utils/streamers/containers.hpp"
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
      variables_map parsed_options;
      store(parse_command_line(argc, argv, description()), parsed_options);
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

    static boost::program_options::options_description const& description() {
      using namespace boost::program_options;
      static options_description options {
        R"(
    Converts data_sets in hdf5 files to csv

    Allowed Options)"
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
      return options;
    }

    static void show_help(std::ostream& out) {
      out << description();
      out.flush();
    }

    //! getter for help_ (access is Ro)
    bool help() const { return help_; }

    //! getter for data_set_ (access is Ro)
    std::vector< std::string > data_set() const { return data_set_; }

    //! getter for input_file_ (access is Ro)
    std::vector< std::string > input_file() const { return input_file_; }

    //! getter for output_file_ (access is Ro)
    std::string output_file() const { return output_file_; }
    friend inline std::ostream& operator<<(std::ostream& out, Program_options const& item) {
      using fcs::utils::streamers::operator<<;
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
  try{
    Program_options options = { argc, argv };
    if(options.help()) {
      Program_options::show_help(std::cout);
      return 0;
    }

    std::cout << options << std::endl;
  } catch(std::exception const& e) {
    std::cout << "Caught exception: " << e.what() << std::endl;
    Program_options::show_help(std::cout);
    return -1;
  }

  return 0;
}
