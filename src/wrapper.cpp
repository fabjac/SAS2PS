#include "wrapper.h"

namespace fc
{

Wrapper::Wrapper(const std::string& in_sep, const std::string& out_sep) :
  _in_sep(in_sep), _out_sep(out_sep)
{
}

void Wrapper::wrap(const std::string& in_str, std::string& out_str)
{
  out_str = in_str;
}

Wrapper::~Wrapper()
{
}

} // end namespace fc

