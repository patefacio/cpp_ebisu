#include <boost/program_options.hpp>

namespace fcs {
namespace app {
namespace display_csv {
  struct Program_options
  {
  public:
    Program_options(int argc, char** argv) {
      using namespace boost::program_options;
      static options_description options {
        R"(
    null

    Allowed Options:
    )"
      };
      if(options.options().empty()) {
        options.add_options()
        ("help,h", "Display help information");
      }
      variables_map parsed_options;
      store(parse_command_line(argc, argv, options), parsed_options);
      if(parsed_options.count("help") > 0) {
        help_ = true;
        return;
      }

    }
    friend inline std::ostream& operator<<(std::ostream& out, Program_options const& item) {
      out << '\n' << "help:" << item.help_;
      return out;
    }

  private:
    bool help_ {};

  };


} // namespace display_csv
} // namespace app
} // namespace fcs

int main(int argc, char** argv) {
  using namespace fcs::app::display_csv;
  Program_options options = { argc, argv };

  return 0;
}
