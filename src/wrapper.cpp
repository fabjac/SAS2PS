#include "wrapper.h"
#include "shareasale_record.h"
#include "prestashop_record.h"

namespace fc
{

Wrapper::Wrapper(const char in_sep, const char out_sep) :
  _in_sep(in_sep), _out_sep(out_sep)
{
}

void Wrapper::wrap(const std::string& in_str, std::string& out_str)
{
  out_str = in_str;
  Shareasale_record in_rec(in_str, _in_sep);
  Prestashop_record out_rec(_out_sep);
  wrap(in_rec, out_rec);
  out_str = out_rec.asString();
}

void Wrapper::wrap(const Shareasale_record& in_record, Prestashop_record& out_record)
{
  // TODO
  // ex : map 1 -> 0 and 0 -> 1
  out_record.setField(1, in_record.at(0));
  out_record.setField(0, in_record.at(1));
}

Wrapper::~Wrapper()
{
}

} // end namespace fc

