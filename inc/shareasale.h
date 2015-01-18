#ifndef _SHAREASALE_INC_H_
#define _SHAREASALE_INC_H_

#include <string>
#include <fstream>

namespace fc
{
class Shareasale
{
public:
  Shareasale(const std::string& file_name);
  ~Shareasale();

private:
  std::string _file_name;
};
} // end namespace

#endif

