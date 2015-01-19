#include "prestashop_record.h"
#include <iostream>
#include <exception>
#include <stdexcept>      // std::out_of_range

namespace fc
{

Prestashop_record::Prestashop_record(const char sep) :
  _sep(sep), fields{_nb_fields, ""}
{
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
    fields.at(i) = s;
  }
  catch (const std::out_of_range& e) {
    std::cerr << "[out of range] vector index : " << i << std::endl;
    throw;
  }
  catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    std::cerr << "vector index : " << i << std::endl;
    throw;
  }
  catch (...) {
    std::cerr << "[unknown exception] vector index : " << i << std::endl;
    throw;
  }
}

Prestashop_record::~Prestashop_record()
{
}

} // end namespace fc

