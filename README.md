# fileConverter
convert CSV feeds from shareasale.com to prestashop CSV format

INSTALL
-------
Requirements :
- a Linux box
- a C++ compiler (C++11 compliant)

in fileConverter directory, type :
make

tested with GCC 4.8.2

RUN
---
usage: ./bin/fileConverter -i input_file -o output_file -c category

EXAMPLE
-------
./bin/fileConverter -i inTestFile.csv -o outTestFile.csv -c 42

