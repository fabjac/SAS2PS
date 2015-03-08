#include "database.h"
#include "shareasale_record.h"
#include "tools.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <string.h>

using namespace std;

namespace fc
{
Database::Database(string db, string host, string user, string passwd)
{
  mysql_init(&mysql);
  if (!mysql_real_connect(&mysql,host.c_str(),user.c_str(),passwd.c_str(),db.c_str(),0,NULL,0))
  {
    Tools::log(E_level::FATAL, "mysql_real_connect()", mysql_error(&mysql));
    exit(1);
  }

  if (!mysql_set_character_set(&mysql, "utf8"))
  {
    Tools::log(E_level::INFO, "New client character set", mysql_character_set_name(&mysql));
  }
}

Database::~Database()
{
  mysql_close(&mysql);
}

bool Database::product_exist(const string& in_str, const char _in_sep)
{
  Shareasale_record in_rec(in_str, _in_sep);
  long id_product = atol(in_rec.at(0).c_str());
  return product_exist(id_product);
}

bool Database::product_exist(long id_product)
{
  std::string query = "select 1 from product where id_product=" + std::to_string(id_product);
  Tools::log(E_level::TRACE, "product_exist()", query);
  int r = mysql_query(&mysql, query.c_str());
  Tools::log(E_level::TRACE, "return", r);
  if (r != 0) {
    Tools::log(E_level::FATAL, "mysql error", mysql_error(&mysql));
    throw std::exception();
  }
  MYSQL_RES * res = mysql_store_result(&mysql);
  r = (int) mysql_num_rows(res);
  Tools::log(E_level::TRACE, "affected rows", r);
  return r;
}

std::string Database::escape_string(const std::string& s)
{
  const char * ch = s.c_str();
  int lg = strlen(ch);
  char ch2[2 * lg];
  try {
    //TODO: use mysql_real_escape_string_quote with a newer release of mysqlclient library
    //int r = mysql_real_escape_string_quote(&mysql, ch2, ch, lg,'\'');
    int r = mysql_real_escape_string(&mysql, ch2, ch, lg);
    Tools::log(E_level::TRACE, "mysql_real_escape_string() return", r);
    if (r <= 0) {
      throw std::exception();
    }
    return ch2;
  }
  catch (...) {
    Tools::log(E_level::FATAL, "escape_string()", "Unknown error");
    Tools::log(E_level::FATAL, "in string", string(ch));
    Tools::log(E_level::FATAL, "out string", string(ch2));
    throw;
  }
}

bool Database::do_update(const char * q)
{
  try {
    Tools::log(E_level::TRACE, "do_update() query", string(q));
    int r = mysql_query(&mysql, q);
    Tools::log(E_level::TRACE, "return", r);
    if (r != 0) {
      Tools::log(E_level::FATAL, "mysql error", mysql_error(&mysql));
      throw std::exception();
    }
    r = (int) mysql_affected_rows(&mysql);
    Tools::log(E_level::TRACE, "affected rows", r);
    if (r > 0)
      return true;
    else
      return false;
  }
  catch (...) {
    Tools::log(E_level::FATAL, "do_update()", "Unknown error");
    Tools::log(E_level::FATAL, "q", string(q));
    throw;
  }
}

bool Database::update(const string& in_str, const char _in_sep)
{
  Shareasale_record in_rec(in_str, _in_sep);
  long id_product = atol(in_rec.at(0).c_str());
  bool res {false};
  std::stringstream ss{};

  // update price
  double price = atof(in_rec.at(7).c_str());
  ss << "update product set price = " << price << " where id_product = " << id_product;
  res |= do_update(std::string(ss.str()).c_str());

  ss.str(""); ss.clear();
  ss << "update product_shop set price = " << price << " where id_product = " << id_product;
  res |= do_update(std::string(ss.str()).c_str());

  // update name
  ss.str(""); ss.clear();
  ss << "update product_lang set name = '" << escape_string(in_rec.at(1)) \
    << "', description = '" << escape_string(in_rec.at(11)) \
    << "', description_short = '" << escape_string(in_rec.at(1)) \
    << "' where id_product = " << id_product;
  res |= do_update(std::string(ss.str()).c_str());

  return res;
}

} // end namespace fc

