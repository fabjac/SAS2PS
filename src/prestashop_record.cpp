#include "prestashop_record.h"
#include <iostream>

namespace fc
{

Prestashop_record::Prestashop_record(const char sep) :
  _sep(sep)
{
  for (int i=0 ; i<_nb_fields ; i++) {
    fields.push_back("");
  }
}

std::string Prestashop_record::asString()
{
  std::string s("");
  std::string sep(1, _sep);
  for (auto& field : fields) {
    s += field;
    s += sep;
  }
  s += "\n";
  return s;
}

void Prestashop_record::setField(int i, const std::string& s)
{
  try {
    fields[i] = s;
  }
  catch (const std::exception& e) {
    std::cerr << "vector index : " << i << std::endl;
    throw;
  }
  catch (...) {
    std::cerr << "vector index : " << i << std::endl;
    throw;
  }
}

Prestashop_record::~Prestashop_record()
{
}

} // end namespace fc

