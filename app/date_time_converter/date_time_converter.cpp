#include "fcs/utils/streamers/containers.hpp"
#include <boost/program_options.hpp>
#include <string>
#include <vector>

namespace fcs {
namespace app {
namespace date_time_converter {
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

      if(parsed_options.count("timestamp") > 0) {
        timestamp_ = parsed_options["timestamp"]
          .as< std::vector< std::string > >();
      }

    }

    static boost::program_options::options_description const& description() {
      using namespace boost::program_options;
      static options_description options {
        R"(
    App for converting between various forms of date/time

    Allowed Options)"
      };
      if(options.options().empty()) {
        options.add_options()
        ("help,h", "Display help information")
        ("timestamp,t", value< std::vector< std::string > >(),
          "Some form of date or timestamp");
      }
      return options;
    }

    static void show_help(std::ostream& out) {
      out << description();
      out.flush();
    }

    //! getter for help_ (access is Ro)
    bool help() const { return help_; }

    //! getter for timestamp_ (access is Ro)
    std::vector< std::string > const& timestamp() const { return timestamp_; }
    friend inline std::ostream& operator<<(std::ostream& out, Program_options const& item) {
      using fcs::utils::streamers::operator<<;
      out << '\n' << "help:" << item.help_;
      out << '\n' << "timestamp:" << item.timestamp_;
      return out;
    }

  private:
    bool help_ {};
    std::vector< std::string > timestamp_ {};

  };


} // namespace date_time_converter
} // namespace app
} // namespace fcs

int main(int argc, char** argv) {
  using namespace fcs::app::date_time_converter;
  try{
    Program_options options = { argc, argv };
    if(options.help()) {
      Program_options::show_help(std::cout);
      return 0;
    }

    std::cout << options << std::endl;
    // custom <main>

    for(auto const& ts : options.timestamp()) {
      std::cout << "Converting " << ts << std::endl;
    }

    // end <main>

  } catch(std::exception const& e) {
    std::cout << "Caught exception: " << e.what() << std::endl;
    Program_options::show_help(std::cout);
    return -1;
  }

  return 0;
}
