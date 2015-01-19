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
  int i=0;
  out_record.setField(i++, in_record.at(1));
  out_record.setField(i++, "1");
  out_record.setField(i++, in_record.at(2));
  out_record.setField(i++, "44");  // TODO cat #
  out_record.setField(i++, in_record.at(9));
  out_record.setField(i++, "0");
  out_record.setField(i++, "0");
  out_record.setField(i++, "1");
  out_record.setField(i++, "");
  double old_price = atof(in_record.at(9).c_str());
  if (old_price == 0.0)
    out_record.setField(i++, "0");
  else {
    double new_price = atof(in_record.at(8).c_str());
    double reduction = (old_price - new_price) / old_price;
    out_record.setField(i++, std::to_string(static_cast<int>(reduction)));
  }
  // TODO
  //"2000-01-01","2099-12-31",$1,$21,$3,"","","","","0","0","0","0","99","1","","","","",$2,$12,"","","","","","in stock","","1","2000-01-01","2000-01-01","1",$6,"1","","","","0","0","0","0","0","0","0","0"
}

Wrapper::~Wrapper()
{
}

} // end namespace fc

