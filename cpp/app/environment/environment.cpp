#include "QApplication"
#include "QPushButton"
#include "ebisu/environment/environment.hpp"
#include "ebisu/gui/environment/q_environment.hpp"
#include <boost/program_options.hpp>
#include <iostream>

namespace ebisu {
namespace gui {
namespace {
char const* app_descr = R"(

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
  }

  static boost::program_options::options_description const& description() {
    using namespace boost::program_options;
    static options_description options{app_descr};

    if (options.options().empty()) {
      options.add_options()("help,h", "Display help information");
    }
    return options;
  }

  static void show_help(std::ostream& out) {
    out << description();
    out.flush();
  }

  friend inline std::ostream& operator<<(std::ostream& out,
                                         Program_options const& item) {
    out << "Program_options(" << &item << ") {";
    out << "\n  help:" << item.help_;
    out << "\n}\n";
    return out;
  }

  //! getter for help_ (access is Ro)
  bool help() const { return help_; }

 private:
  bool help_{};
};

// custom <FcbEndNamespace environment>
// end <FcbEndNamespace environment>

}  // namespace gui
}  // namespace ebisu

int main(int argc, char** argv) {
  using namespace ebisu::gui;
  try {
    //////////////////////////////////////////////////////////////////////
    // Read program options and display help if requested
    //////////////////////////////////////////////////////////////////////
    Program_options options = {argc, argv};
    if (options.help()) {
      Program_options::show_help(std::cout);
      return 0;
    }

    //////////////////////////////////////////////////////////////////////
    // User supplied environment protect block
    //////////////////////////////////////////////////////////////////////
    // custom <main>

    using namespace ebisu::gui::environment;

    QApplication app(argc, argv);
    Q_environment env(nullptr);
    env.show();

    return app.exec();

    // end <main>

  } catch (boost::program_options::error const& e) {
    std::cerr << "Caught boost program options exception: " << e.what()
              << std::endl;
    Program_options::show_help(std::cout);
    return -1;
  } catch (std::exception const& e) {
    std::cerr << "Caught exception: " << e.what() << std::endl;
    return -1;
  }
  return 0;
}
