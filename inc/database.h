#ifndef _DATABASE_INC_H_
#define _DATABASE_INC_H_

#include <mysql++.h>
/*
#include "shareasale_record.h"
#include "prestashop_record.h"
#include <string>
#include <vector>
*/

using namespace std;
using namespace mysqlpp;

namespace fc
{
class Database
{
public:
  Database(string db, string host, string user, string passwd);
  ~Database();

  bool product_exist(const string& in_str, const char _in_sep);
  bool product_exist(long id_product);
  template <class T> bool do_update(const string& q, long id_product, T v);
  bool update(const string& in_str, const char _in_sep);

private:
  Connection connection;
  Query query;

};
} // end namespace

#endif

