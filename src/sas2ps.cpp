//============================================================================
// main program
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "wrapper.h"
#include "database.h"
#include "tools.h"

void usage(char * s)
{
    std::cerr << "usage: " << s << " -i input_file -o output_file -c category";
    std::cerr << " -m match_word [-m match_word2] ...";
    std::cerr << " -x exclude_word [-x exclude_word2] ...";
    std::cerr << " -p min_price";
    std::cerr << " -d debug_level -n db_name -s db_server -u db_user -a db_password";
    std::cerr << std::endl;
}

int main(int argc, char *argv[])
{
  if (argc < 5) {
    usage(argv[0]);
    return 1;
  }

  short int debug_level=3;
  std::string input_file(""), output_file(""), category("");
  std::string db_name(""), db_server(""), db_user(""), db_password("");
  std::vector<std::string> matching_words{}, excluded_words{};
  double min_price=0.0;
  int i = 1;
  while (i < argc) {
    if (argv[i][0]=='-' && argv[i][1]=='d') {
      debug_level = atoi(argv[i+1]);
    }
    if (argv[i][0]=='-' && argv[i][1]=='n') {
      db_name = argv[i+1];
    }
    if (argv[i][0]=='-' && argv[i][1]=='s') {
      db_server = argv[i+1];
    }
    if (argv[i][0]=='-' && argv[i][1]=='u') {
      db_user = argv[i+1];
    }
    if (argv[i][0]=='-' && argv[i][1]=='a') {
      db_password = argv[i+1];
    }
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
      matching_words.push_back(word);
    }
    if (argv[i][0]=='-' && argv[i][1]=='x') {
      std::string word{argv[i+1]};
      std::transform(word.begin(), word.end(), word.begin(), ::tolower);
      excluded_words.push_back(word);
    }
    if (argv[i][0]=='-' && argv[i][1]=='p') {
      min_price = atof(argv[i+1]);
    }
    i+=2;
  }

  fc::Tools::setDebugLevel(debug_level);
  fc::Tools::log(fc::E_level::INFO, "JOB", "Starting");

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
  std::cout << "Connecting to " << db_user << "@" << db_name << " on server " << db_server << std::endl;

  std::ifstream sas_file(input_file);
  std::ofstream ps_file(output_file);
  fc::Wrapper wrapper('|', ';', category, matching_words, excluded_words, min_price);
  long int added_lines=0, ignored_lines=0, updated_lines=0, up_to_date=0;
  fc::Database db(db_name, db_server, db_user, db_password);

  while (! sas_file.eof()) {
    std::string in_str, out_str("");
    getline(sas_file, in_str);
    if (in_str.length() == 0) {
      out_str = "";
    }
    else {
      if (db.product_exist(in_str, '|')) {
	if (db.update(in_str, '|')) {
	  updated_lines += 1;
	}
	else
	  up_to_date += 1;
      }
      else {
	if (wrapper.wrap(in_str, out_str))
	  added_lines += 1;
	else
	  ignored_lines += 1;
      }
    }
    ps_file << out_str;
  }

  fc::Tools::log(fc::E_level::INFO, "updated products", updated_lines);
  fc::Tools::log(fc::E_level::INFO, "up-to-date products", up_to_date);
  fc::Tools::log(fc::E_level::INFO, "added products", added_lines);
  fc::Tools::log(fc::E_level::INFO, "ignored products", ignored_lines);
  ps_file.close();
  sas_file.close();

  fc::Tools::log(fc::E_level::INFO, "JOB", "End");
}

