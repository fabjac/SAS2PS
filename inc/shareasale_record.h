#ifndef _SAS_RECORD_H_
#define _SAS_RECORD_H_

#include <string>
#include <vector>

namespace fc
{
class Shareasale_record
{
public:
  Shareasale_record(const std::string& record, const char sep);
  ~Shareasale_record();

  std::string at(int i) const;

private:
  std::string _record;
  char _sep;
  std::vector<std::string> fields;

  // fields
  long int _product_id;
  std::string _name;
};
} // end namespace

#endif

