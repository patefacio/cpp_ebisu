#include "ebisu/logger/logger.hpp"
#include "ebisu/utils/streamers/containers.hpp"
#include <boost/program_options.hpp>
#include <iostream>
#include <string>
#include <vector>

namespace ebisu {
namespace {
char const* app_descr = R"(
Converts data_sets in hdf5 files to csv

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

    if (parsed_options.count("data-set") > 0) {
      data_set_ = parsed_options["data-set"].as<std::vector<std::string> >();
    }

    if (parsed_options.count("input-file") > 0) {
      input_file_ =
          parsed_options["input-file"].as<std::vector<std::string> >();
    } else {
      std::ostringstream msg;
      msg << "h5ds2csv option 'input-file' is required";
      throw boost::program_options::error(msg.str());
    }

    if (parsed_options.count("output-file") > 0) {
      output_file_ = parsed_options["output-file"].as<std::string>();
    }

    log_level_ = parsed_options["log-level"].as<std::string>();
  }

  static boost::program_options::options_description const& description() {
    using namespace boost::program_options;
    static options_description options{app_descr};

    if (options.options().empty()) {
      options.add_options()("help,h", "Display help information")(
          "data-set,d", value<std::vector<std::string> >(),
          "Name of data_set to make into csv")(
          "input-file,i", value<std::vector<std::string> >(),
          "Name of hdf5 file containing data_set(s)")(
          "output-file,o", value<std::string>(),
          "Name of hdf5 file containing data_set(s)")(
          "log-level", value<std::string>()->default_value("off"),
          "Specify log level [trace, debug, info, warn, err, critical, off]");
    }
    return options;
  }

  static void show_help(std::ostream& out) {
    out << description();
    out.flush();
  }

  friend inline std::ostream& operator<<(std::ostream& out,
                                         Program_options const& item) {
    using ebisu::utils::streamers::operator<<;
    out << "Program_options(" << &item << ") {";
    out << "\n  help:" << item.help_;
    out << "\n  data_set:" << item.data_set_;
    out << "\n  input_file:" << item.input_file_;
    out << "\n  output_file:" << item.output_file_;
    out << "\n  log_level:" << item.log_level_;
    out << "\n}\n";
    return out;
  }

  //! getter for help_ (access is Ro)
  bool help() const { return help_; }

  //! getter for data_set_ (access is Ro)
  std::vector<std::string> const& data_set() const { return data_set_; }

  //! getter for input_file_ (access is Ro)
  std::vector<std::string> const& input_file() const { return input_file_; }

  //! getter for output_file_ (access is Ro)
  std::string const& output_file() const { return output_file_; }

  //! getter for log_level_ (access is Ro)
  std::string const& log_level() const { return log_level_; }

 private:
  bool help_{};
  std::vector<std::string> data_set_{};
  std::vector<std::string> input_file_{};
  std::string output_file_{};
  std::string log_level_{};
};

}  // namespace ebisu

int main(int argc, char** argv) {
  using namespace ebisu;
  try {
    //////////////////////////////////////////////////////////////////////
    // Read program options and display help if requested
    //////////////////////////////////////////////////////////////////////
    Program_options options = {argc, argv};
    if (options.help()) {
      Program_options::show_help(std::cout);
      return 0;
    }

    std::string const desired_log_level{options.log_level()};
    if (desired_log_level == "off") {
      spdlog::set_level(spdlog::level::off);
    } else if (desired_log_level == "debug") {
      spdlog::set_level(spdlog::level::debug);
    } else if (desired_log_level == "info") {
      spdlog::set_level(spdlog::level::info);
    } else if (desired_log_level == "warn") {
      spdlog::set_level(spdlog::level::warn);
    } else if (desired_log_level == "err") {
      spdlog::set_level(spdlog::level::err);
    } else if (desired_log_level == "critical") {
      spdlog::set_level(spdlog::level::critical);
    } else if (desired_log_level == "trace") {
      spdlog::set_level(spdlog::level::trace);
    } else {
      throw std::invalid_argument(
          "log_level must be one of: [trace, debug, info, notice, warn, err, "
          "critical, alert, emerg, off]");
    }
    //////////////////////////////////////////////////////////////////////
    // User supplied h5ds2csv protect block
    //////////////////////////////////////////////////////////////////////
    // custom <main>
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
