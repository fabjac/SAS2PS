# SAS2PS
convert CSV feeds from shareasale.com to prestashop CSV format

update products in database if they already exists

INSTALL
-------
Requirements :
- a Linux box
- a C++ compiler (C++11 compliant)

Dependencies :

mysql++

mysql++-dev

in fileConverter directory, type :

make

tested with GCC 4.8.2

RUN
---
usage: ./bin/fileConverter -i input_file -o output_file -c category -m match_word [-m match_word2] ... -x exclude_word [-x exclude_word2] ... -p min_price -d db_name -s db_server -u db_user -a db_password

EXAMPLE
-------
./bin/fileConverter -i inTestFile.csv -o outTestFile.csv -c 42 -m iphone -x case -x box -p 599 -d shop_db -s localhost -u shop_user -p secretPass

