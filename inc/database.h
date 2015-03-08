#ifndef _DATABASE_INC_H_
#define _DATABASE_INC_H_

#include <mysql/mysql.h>
#include <string>

using namespace std;

namespace fc
{
class Database
{
public:
  Database(string db, string host, string user, string passwd);
  ~Database();

  bool product_exist(const string& in_str, const char _in_sep);
  bool product_exist(long id_product);
  bool do_update(const char * q);
  bool update(const string& in_str, const char _in_sep);

private:
  MYSQL mysql;

  std::string escape_string(const string&);

};
} // end namespace

#endif

