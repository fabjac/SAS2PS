#ifndef _WRAPPER_INC_H_
#define _WRAPPER_INC_H_

#include <string>

namespace fc
{
class Wrapper
{
public:
  Wrapper(const std::string& in_sep, const std::string& out_sep);
  void wrap(const std::string& in_str, std::string& out_str);
  ~Wrapper();

private:
  std::string _in_sep;
  std::string _out_sep;
};
} // end namespace

#endif

