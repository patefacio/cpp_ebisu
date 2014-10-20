namespace fcs {
namespace app {
namespace display_csv {
  struct Program_options
  {
  public:
    Program_options(int argc, char** argv) {
      using namespace boost::program_options;
      static option_description options {
        R"(
    null

    Allowed Options:
    )"
      };
      if(options.options.empty()) {
        options.add_options()
        ("help,h", "Display help information")
      }
      variables_map parsed_options;
      store(parse_command_line(argc, argv, options), parsed_options);
      if(parsed_options.count("help") > 0) {
        help_ = true;
        return;
      }

  };


} // namespace display_csv
} // namespace app
} // namespace fcs

int main(int argc, char** argv) {
  using fcs::app::display_csv;
  Program_options options = { argc, argv };

  return 0;
}
