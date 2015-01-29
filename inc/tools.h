#ifndef _TOOLS_INC_H_
#define _TOOLS_INC_H_

#include <string>
#include <vector>

namespace fc
{
class Tools
{
public:
  static void debug(const std::string& s1, const std::string& lib);
  static std::vector<std::string> getCompleteWord(const std::string& word);

};
} // end namespace

#endif

