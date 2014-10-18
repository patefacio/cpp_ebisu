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
        ("timestamp", value< std::vector< bool > >(), "Some form of date or timestamp")
      }
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
