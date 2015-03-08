#ifndef _TOOLS_INC_H_
#define _TOOLS_INC_H_

#include <string>
#include <vector>
#include <iostream>

namespace fc
{
enum class E_level { TRACE=0, DEBUG, WARN, INFO, FATAL };

class Tools
{
public:
  template <class T> 
  static void log(E_level lvl, std::string msg, const T& v)
  {
    if (lvl >= Tools::_lvl) {
      std::string sLevel = getStrLevel(lvl);
      std::cerr << currentDateTime() << " " << sLevel << " " << msg << " : " << v << std::endl;
    }
  };

  static std::vector<std::string> getCompleteWord(const std::string& word);
  static void strReplace(std::string& subject, const std::string& search, const std::string& replace);

  // FIXME
  //static void setDebugLevel(E_level level)
  static void setDebugLevel(short int level)
  {
    Tools::_lvl = static_cast<E_level>(level);
  };

  static E_level _lvl;

private:
  static std::string getStrLevel(E_level);
  static std::string currentDateTime();

};
} // end namespace

#endif

