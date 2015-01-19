#ifndef _WRAPPER_INC_H_
#define _WRAPPER_INC_H_

#include "shareasale_record.h"
#include "prestashop_record.h"
#include <string>

namespace fc
{
class Wrapper
{
public:
  Wrapper(const char in_sep, const char out_sep);
  void wrap(const std::string& in_str, std::string& out_str);
  void wrap(const Shareasale_record& in_record, Prestashop_record& out_record);
  ~Wrapper();

private:
  char _in_sep;
  char _out_sep;
};
} // end namespace

#endif

