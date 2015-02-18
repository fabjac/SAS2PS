#include <sstream>
#include <iostream>
#include "shareasale_record.h"
#include "tools.h"

namespace fc
{

Shareasale_record::Shareasale_record(const std::string& record, const char sep) :
  _record(record), _sep(sep)
{
  fields.clear();
  std::string rec(record);
  update_html_entities(rec);
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

void Shareasale_record::update_html_entities(std::string& s)
{
  Tools::strReplace(s, "&amp;", "&");
  Tools::strReplace(s, "&apos;", "'");
  Tools::strReplace(s, "&quot;", "\"");
  Tools::strReplace(s, "&lt;", "<");
  Tools::strReplace(s, "&gt;", ">");
  Tools::strReplace(s, "&copy;", "(c)");
  Tools::strReplace(s, "&reg;", "(r)");
}

std::string Shareasale_record::at(int i) const
{
  return fields.at(i);
}

Shareasale_record::~Shareasale_record()
{
}

} // end namespace fc

