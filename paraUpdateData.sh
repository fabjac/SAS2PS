#!/bin/bash

usage()
{
  echo "usage: $0 <in_file> <conf_file>" 
  echo "ex: $0 inTestFile.csv sample.conf"
  exit 1
}

SOURCE_DIR=/tmp/sas2ps.data
LOG_DIR=/tmp/sas2ps.log

test "$1" = '' && usage
test ! -f "$1" && usage
IN_FILE=$1
test "$2" = '' && usage
test ! -f "$2" && usage

source $2
PARAMS="-n $DB_NAME -s $DB_SERVER -u $DB_USER -a $DB_PASSWORD"

shift 2
PARAMS="$PARAMS $*"

rm -rf $SOURCE_DIR $LOG_DIR 2>/dev/null
mkdir $SOURCE_DIR $LOG_DIR

cd $SOURCE_DIR
split -l 1000 $IN_FILE splitted.$(basename $IN_FILE).

cd -
ls -1 $SOURCE_DIR | while read fic
do
  ./bin/sas2ps -i $SOURCE_DIR/$fic -o $SOURCE_DIR/$fic.csv -c 999 $PARAMS > $LOG_DIR/$fic.log 2> $LOG_DIR/$fic.err &
done

