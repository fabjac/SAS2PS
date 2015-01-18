//============================================================================
// main program
//============================================================================

#include <iostream>
#include <fstream>
#include "wrapper.h"

void usage(char * s)
{
    std::cerr << "usage: " << s << " -i input_file -o output_file" << std::endl;
}

int main(int argc, char *argv[])
{
  if (argc < 5) {
    usage(argv[0]);
    return 1;
  }

  std::string input_file(""), output_file("");
  int i = 1;
  while (i < argc) {
    if (argv[i][0]=='-' && argv[i][1]=='i') {
      input_file = argv[i+1];
    }
    if (argv[i][0]=='-' && argv[i][1]=='o') {
      output_file = argv[i+1];
    }
    i+=2;
  }

  if (input_file=="") {
    usage(argv[0]);
    return 1;
  }
  if (output_file=="") {
    usage(argv[0]);
    return 1;
  }

  std::cout << "Input file  : " << input_file << std::endl;
  std::cout << "Output file : " << output_file << std::endl;

  std::ifstream sas_file(input_file);
  std::ofstream ps_file(output_file);
  fc::Wrapper wrapper(std::string("|"), std::string(";"));

  while (! sas_file.eof()) {
    std::string in_str, out_str("");
    sas_file >> in_str;
    wrapper.wrap(in_str, out_str);
    ps_file << out_str;
  }

  ps_file.close();
  sas_file.close();

  return 0;
}

