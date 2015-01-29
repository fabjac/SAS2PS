#include <iostream>
#include "tools.h"

namespace fc
{

// TODO use debug level INFO, WARN, FATAL...
void Tools::debug(const std::string& s1, const std::string& lib)
{
  //std::cerr << "[" << s1 << "] " << lib << std::endl;
}

// TODO : use regex when it's implemented in GCC
std::vector<std::string> Tools::getCompleteWord(const std::string& word)
{
  std::string sep{"|"};
  std::vector<std::string> v{};
  v.push_back(" "+word+" ");
  v.push_back(" "+word+",");
  v.push_back(" "+word+";");
  v.push_back(" "+word+"*");
  v.push_back(" "+word+sep);
  v.push_back(sep+word+" ");
  return v;
}

} // end namespace fc

