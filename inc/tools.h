#ifndef _TOOLS_INC_H_
#define _TOOLS_INC_H_

#include <string>
#include <vector>

namespace fc
{
enum class E_level { TRACE, DEBUG, WARN, INFO, FATAL };

class Tools
{
public:

  template <class T>
  static void debug(const std::string& s1, const T& v)
  {
    // FIXME
    log(Tools::_lvl, s1, v);
  };

  template <class T> 
  static void log(E_level lvl, std::string msg, const T& v)
  {
    std::string sLevel = getStrLevel(lvl);
    std::cerr << currentDateTime() << " " << sLevel << " " << msg << " " << v << std::endl;
  };

  static std::vector<std::string> getCompleteWord(const std::string& word);
  static void strReplace(std::string& subject, const std::string& search, const std::string& replace);
  static void setDebugLevel(E_level level)
{
  Tools::_lvl = level;
};

  static E_level _lvl;

private:
  static std::string getStrLevel(E_level);
  static std::string currentDateTime();

};
} // end namespace

#endif

