#include "database.h"
#include "shareasale_record.h"
#include "tools.h"
#include <iostream>
#include <iomanip>

using namespace std;
using namespace mysqlpp;

namespace fc
{
Database::Database(string db, string host, string user, string passwd)
  : connection((const char *) db.c_str(), (const char *) host.c_str(), (const char *) user.c_str(), (const char *) passwd.c_str()),
  query(&connection)
{
}

Database::~Database()
{
}

bool Database::product_exist(const string& in_str, const char _in_sep)
{
  Shareasale_record in_rec(in_str, _in_sep);
  long id_product = atol(in_rec.at(0).c_str());
  return product_exist(id_product);
}

bool Database::product_exist(long id_product)
{
  query.reset();
  query << "select 1 from product where id_product=" << id_product;
  StoreQueryResult res = query.store();
  return res.size();
}

template <class T>
bool Database::do_update(const string& q, long id_product, T v)
{
  try {
    query.reset();
    query << q;
    query.parse();
    SimpleResult res = query.execute(v, id_product);
    Tools::log(E_level::INFO, "id product", id_product);
    Tools::log(E_level::INFO, "value", v);
    Tools::log(E_level::INFO, "affected row(s)", to_string(query.affected_rows()));
    if (query.affected_rows() > 0) {
      Tools::log(E_level::INFO, "query", q);
      return true;
    }
    else
      return false;
  }
  catch (const mysqlpp::BadQuery& er) {
    // Handle any query errors
    cerr << "Query error: " << er.what() << endl;
    cerr << q << endl;
    cerr << query.str() << endl;
    Tools::log(E_level::FATAL, "id product", id_product);
    Tools::log(E_level::FATAL, "value", v);
    throw;
  }
  catch (const mysqlpp::BadConversion& er) {
    // Handle bad conversions
    cerr << "Conversion error: " << er.what() << endl <<
      "\tretrieved data size: " << er.retrieved <<
      ", actual size: " << er.actual_size << endl;
    cerr << q << endl;
    cerr << query.str() << endl;
    Tools::log(E_level::FATAL, "id product", id_product);
    Tools::log(E_level::FATAL, "value", v);
    throw;
  }
  catch (const mysqlpp::Exception& er) {
    // Catch-all for any other MySQL++ exceptions
    cerr << "Error: " << er.what() << endl;
    cerr << q << endl;
    cerr << query.str() << endl;
    Tools::log(E_level::FATAL, "id product", id_product);
    Tools::log(E_level::FATAL, "value", v);
    throw;
  }
  catch (...) {
    cerr << "Unknown error: " << endl;
    cerr << q << endl;
    cerr << query.str() << endl;
    Tools::log(E_level::FATAL, "id product", id_product);
    Tools::log(E_level::FATAL, "value", v);
    throw;
  }
}

bool Database::update(const string& in_str, const char _in_sep)
{
  Shareasale_record in_rec(in_str, _in_sep);
  long id_product = atol(in_rec.at(0).c_str());
  bool res {false};

  // update price
  double price = atof(in_rec.at(7).c_str());
  res |= do_update("update product set price = %0q where id_product= %1q", id_product, price);
  res |= do_update("update product_shop set price = %0q where id_product= %1q", id_product, price);

  // update name
  res |= do_update("update product_lang set name = %0q where id_product= %1q", id_product, in_rec.at(1));

  // TODO: fix encoding issue with UTF-8
  // update description
  //res |= do_update("update product_lang set description = %0q where id_product= %1q", id_product, in_rec.at(11));

  // TODO
  // update description_short

  return res;
}

} // end namespace fc

