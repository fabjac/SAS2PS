//============================================================================
// main program
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "wrapper.h"

void usage(char * s)
{
    std::cerr << "usage: " << s << " -i input_file -o output_file -c category";
    std::cerr << " -m match_word [-m match_word2] ...";
    std::cerr << " -x exclude_word [-x exclude_word2] ...";
    std::cerr << " -p min_price";
    std::cerr << std::endl;
}

int main(int argc, char *argv[])
{
  if (argc < 5) {
    usage(argv[0]);
    return 1;
  }

  std::string input_file(""), output_file(""), category("");
  std::vector<std::string> matching_words{}, excluded_words{};
  double min_price=0.0;
  int i = 1;
  while (i < argc) {
    if (argv[i][0]=='-' && argv[i][1]=='i') {
      input_file = argv[i+1];
    }
    if (argv[i][0]=='-' && argv[i][1]=='o') {
      output_file = argv[i+1];
    }
    if (argv[i][0]=='-' && argv[i][1]=='c') {
      category = argv[i+1];
    }
    if (argv[i][0]=='-' && argv[i][1]=='m') {
      std::string word{argv[i+1]};
      std::transform(word.begin(), word.end(), word.begin(), ::tolower);
      matching_words.push_back(" "+word+" ");
    }
    if (argv[i][0]=='-' && argv[i][1]=='x') {
      std::string word{argv[i+1]};
      std::transform(word.begin(), word.end(), word.begin(), ::tolower);
      excluded_words.push_back(" "+word+" ");
    }
    if (argv[i][0]=='-' && argv[i][1]=='p') {
      min_price = atof(argv[i+1]);
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

  if (category == "") {
    usage(argv[0]);
    return 1;
  }

  std::cout << "Input file  : " << input_file << std::endl;
  std::cout << "Output file : " << output_file << std::endl;
  std::cout << "Category : " << category << std::endl;

  std::ifstream sas_file(input_file);
  std::ofstream ps_file(output_file);
  fc::Wrapper wrapper('|', ';', category, matching_words, excluded_words, min_price);
  long int added_lines=0, ignored_lines=0;

  while (! sas_file.eof()) {
    std::string in_str, out_str("");
    getline(sas_file, in_str);
    if (in_str.length() == 0) {
      out_str = "";
    }
    else {
      if (wrapper.wrap(in_str, out_str))
	added_lines += 1;
      else
	ignored_lines += 1;
    }
    ps_file << out_str;
  }

  std::cout << added_lines << " lines added." << std::endl;
  std::cout << ignored_lines << " lines ignored." << std::endl;
  ps_file.close();
  sas_file.close();

  return 0;
}

