#include <iostream>
#include "tools.h"

namespace fc
{
E_level Tools::_lvl {E_level::INFO};

std::string Tools::getStrLevel(E_level lvl)
{
  std::string sLevel {""};
  switch (lvl) {
    case E_level::TRACE: sLevel = "[TRACE]";
		break;

    case E_level::DEBUG: sLevel = "[DEBUG]";
		break;

    case E_level::WARN: sLevel = "[WARN]";
	       break;

    case E_level::INFO: sLevel = "[INFO]";
	       break;

    case E_level::FATAL: sLevel = "[FATAL]";
		break;
  }
  if (sLevel == "") {
    std::cerr << "Tools::getStrLevel() is not up-to-date" << std::endl;
    throw std::exception();
  }
  else 
    return sLevel;
}

std::string Tools::currentDateTime()
{
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );

  char chDateTime[32];
  strftime(chDateTime, 32, "%d-%m-%y %X", timeinfo);
  return chDateTime;
}

// TODO : use regex when it's implemented in GCC
std::vector<std::string> Tools::getCompleteWord(const std::string& word)
{
  std::vector<std::string> v{};
  v.push_back(" "+word+" ");
  v.push_back(" "+word+",");
  v.push_back(" "+word+";");
  v.push_back(" "+word+"*");
  v.push_back(" "+word);
  v.push_back(word+" ");
  return v;
}

void Tools::strReplace(std::string& subject, const std::string& search, const std::string& replace)
{
  size_t pos = 0;
  while((pos = subject.find(search, pos)) != std::string::npos) {
    subject.replace(pos, search.length(), replace);
    pos += replace.length();
  }
}

} // end namespace fc

