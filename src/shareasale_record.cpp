#include <sstream>
#include <iostream>
#include "shareasale_record.h"

namespace fc
{

Shareasale_record::Shareasale_record(const std::string& record, const char sep) :
  _record(record), _sep(sep)
{
  fields.clear();
  std::string rec(record);
  rec += std::string(1, sep);
  int lg = rec.length();
  int ptr = 0;
  while (ptr < lg) {
    if (rec[ptr] == sep) {
      std::string cell = rec.substr(0, ptr);
      fields.push_back(cell);
      rec = rec.substr(ptr+1);
      lg = rec.length();
      ptr = 0;
    }
    else {
      ptr++;
    }
  }
}

std::string Shareasale_record::at(int i) const
{
  return fields.at(i);
}

Shareasale_record::~Shareasale_record()
{
}

} // end namespace fc

