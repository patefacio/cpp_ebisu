namespace fcs {
namespace app {
namespace h5ds2csv {
  struct Program_options
  {
  public:
    Program_options(int argc, char** argv) {
      using namespace boost::program_options;
      static option_description options {
        R"(
    Converts data_sets in hdf5 files to csv

    Allowed Options:
    )"
      };
      if(options.options.empty()) {
        options.add_options()
        ("data-set,d", value< std::vector< std::string > >(),
          "Name of data_set to make into csv")
        ("input-file,i", value< std::vector< std::string > >(),
          "Name of hdf5 file containing data_set(s)")
        ("output-file,o", value< std::string >(),
          "Name of hdf5 file containing data_set(s)")
      }
      variables_map parsed_options;
      store(parse_command_line(argc, argv, options), parsed_options);
    }



  };


} // namespace h5ds2csv
} // namespace app
} // namespace fcs

int main(int argc, char** argv) {
  using fcs::app::h5ds2csv;
  Program_options options = { argc, argv };

  return 0;
}
