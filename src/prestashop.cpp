#include "prestashop.h"

namespace fc
{

Prestashop::Prestashop(const std::string& file_name) :
  _file_name(file_name)
{
  //_file = new ifstream (_file_name);
  //_file = ifstream (_file_name);
}

Prestashop::~Prestashop()
{
}

} // end namespace fc

