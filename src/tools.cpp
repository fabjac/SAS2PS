#include <iostream>
#include "tools.h"

namespace fc
{

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

