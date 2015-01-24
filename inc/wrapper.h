#ifndef _WRAPPER_INC_H_
#define _WRAPPER_INC_H_

#include "shareasale_record.h"
#include "prestashop_record.h"
#include <string>
#include <vector>

namespace fc
{
class Wrapper
{
public:
  Wrapper(const char in_sep, const char out_sep, const std::string& category,
    		const std::vector<std::string>& matching_w, const std::vector<std::string>& excluded_w, double mp);
  bool wrap(const std::string& in_str, std::string& out_str);
  void wrap(const Shareasale_record& in_record, Prestashop_record& out_record);
  bool match(const std::string& s, double price);
  bool doMatch(const std::string& s, const std::vector<std::string>& v, bool);
  ~Wrapper();

private:
  char _in_sep;
  char _out_sep;
  std::string _category;
  std::vector<std::string> mw;
  std::vector<std::string> xw;
  double _min_price;
};
} // end namespace

#endif

