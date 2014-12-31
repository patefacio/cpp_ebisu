#include <boost/program_options.hpp>
#include <iostream>

namespace fcs {
namespace app {
namespace display_csv {
struct Program_options {
  Program_options(int argc, char** argv) {
    using namespace boost::program_options;
    variables_map parsed_options;
    store(parse_command_line(argc, argv, description()), parsed_options);
    if (parsed_options.count("help") > 0) {
      help_ = true;
      return;
    }
  }

  static boost::program_options::options_description const& description() {
    using namespace boost::program_options;
    char const* descr = R"(
    null

    AllowedOptions
    )";

    static options_description options{descr};

    if (options.options().empty()) {
      options.add_options()("help,h", "Display help information");
    }
    return options;
  }

  static void show_help(std::ostream& out) {
    out << description();
    out.flush();
  }

  //! getter for help_ (access is Ro)
  bool help() const { return help_; }
  friend inline std::ostream& operator<<(std::ostream& out,
                                         Program_options const& item) {
    out << '\n' << "help:" << item.help_;
    return out;
  }

 private:
  bool help_{};
};

}  // namespace display_csv
}  // namespace app
}  // namespace fcs

int main(int argc, char** argv) {
  using namespace fcs::app::display_csv;
  try {
    Program_options options = {argc, argv};
    if (options.help()) {
      Program_options::show_help(std::cout);
      return 0;
    }

    // custom <main>
    // end <main>
  }
  catch (std::exception const& e) {
    std::cout << "Caught exception: " << e.what() << std::endl;
    Program_options::show_help(std::cout);
    return -1;
  }

  return 0;
}
