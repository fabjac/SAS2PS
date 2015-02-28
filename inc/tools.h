#ifndef _TOOLS_INC_H_
#define _TOOLS_INC_H_

#include <string>
#include <vector>

namespace fc
{
class Tools
{
public:

  // TODO use debug level INFO, WARN, FATAL...
  template <class T>
  static void debug(const std::string& s1, const T& v)
  {
    std::cerr << "[" << s1 << "] " << v << std::endl;
  };

  static std::vector<std::string> getCompleteWord(const std::string& word);
  static void strReplace(std::string& subject, const std::string& search, const std::string& replace);

};
} // end namespace

#endif

