//============================================================================
// main program
//============================================================================

#include <iostream>
#include "shareasale.h"
#include "prestashop.h"

void usage(char * s)
{
    std::cerr << "usage: " << s << " -i input_file -o output_file" << std::endl;
}

int main(int argc, char *argv[])
{
  fc::Shareasale sas;
  fc::Prestashop ps;

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
    std::cout << "i : " << i << std::endl;
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

  return 0;
}

