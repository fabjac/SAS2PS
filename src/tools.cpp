#include <iostream>
#include "tools.h"

namespace fc
{

// TODO use debug level INFO, WARN, FATAL...
void Tools::debug(const std::string& s1, const std::string& lib)
{
  std::cerr << "[" << s1 << "] " << lib << std::endl;
}

} // end namespace fc

