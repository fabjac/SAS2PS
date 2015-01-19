#ifndef _PS_RECORD_H_
#define _PS_RECORD_H_

#include <string>
#include <vector>

namespace fc
{
class Prestashop_record
{
public:
  Prestashop_record(const char sep);
  ~Prestashop_record();

  std::string asString();
  void setField(int i, const std::string& s);

private:
  static const int _nb_fields = 55;
  char _sep;
  std::vector<std::string> fields;

  // fields
  long int _product_id;
  std::string _name;
};
} // end namespace

#endif

