namespace fcs {
namespace app {
namespace date_time_converter {
  struct Program_options
  {
  public:
    Program_options(int argc, char** argv) {
      using namespace boost::program_options;
      static option_description options {
        R"(
    App for converting between various forms of date/time

    Allowed Options:
    )"
      };
      if(options.options.empty()) {
        options.add_options()
        ("help,h", "Display help information")
        ("timestamp", value< std::vector< std::string > >(),
          "Some form of date or timestamp")
      }
      variables_map parsed_options;
      store(parse_command_line(argc, argv, options), parsed_options);
      if(parsed_options.count("help") > 0) {
        help_ = true;
        return;
      }

      if(parsed_options.count("timestamp") > 0) {
        timestamp_ = parsed_options["timestamp"]
          .as< std::vector< std::string > >();
      }

  };


} // namespace date_time_converter
} // namespace app
} // namespace fcs

int main(int argc, char** argv) {
  using fcs::app::date_time_converter;
  Program_options options = { argc, argv };

  return 0;
}
