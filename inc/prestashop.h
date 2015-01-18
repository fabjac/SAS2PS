#ifndef _PRESTASHOP_INC_H_
#define _PRESTASHOP_INC_H_

#include <string>
#include <fstream>

namespace fc
{
class Prestashop
{
public:
  Prestashop(const std::string& file_name);
  ~Prestashop();

private:
  std::string _file_name;
};
} // end namespace

#endif

