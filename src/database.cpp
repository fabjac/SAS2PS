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

bool Database::update(const string& in_str, const char _in_sep)
{
  Shareasale_record in_rec(in_str, _in_sep);
  long id_product = atol(in_rec.at(0).c_str());
  double price = atof(in_rec.at(7).c_str());
  try {
    query.reset();
    query << "update product set price = %0q where id_product= %1q";
    query.parse();
    SimpleResult res = query.execute(price, id_product);
    Tools::debug("id product", to_string(id_product));
    Tools::debug("affected row(s)", to_string(query.affected_rows()));
    if (query.affected_rows() > 0)
      return true;
    else
      return false;
  }
  catch (const mysqlpp::BadQuery& er) {
    // Handle any query errors
    cerr << "Query error: " << er.what() << endl;
    return false;
  }
  catch (const mysqlpp::BadConversion& er) {
    // Handle bad conversions
    cerr << "Conversion error: " << er.what() << endl <<
      "\tretrieved data size: " << er.retrieved <<
      ", actual size: " << er.actual_size << endl;
    return false;
  }
  catch (const mysqlpp::Exception& er) {
    // Catch-all for any other MySQL++ exceptions
    cerr << "Error: " << er.what() << endl;
    return false;
  }
}

} // end namespace fc

