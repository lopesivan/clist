#!/bin/bash

 ##############################################################################
 #'CList' profiler program.                                                   #
 #Copyright (C) 2008 Kevin P. Barry (ta0kira@users.sourceforge.net)           #
 #Licensed under the GPL.                                                     #
 ##############################################################################

cd "`dirname \"\`readlink -f $0\`\"`"

if [ $# -lt 3 ]; then
  echo "$0 [algorithm] [size] [factor] (compilation options)"
  echo "$0 [algorithm] [built-in type] [factor] (compilation options)"
  echo "$0 [algorithm] [user type] [user file] [factor] (compilation options)"
  echo "  SIMPLE CList/SORTING PROFILER"
  echo
  echo "  [algorithm]:  0 = CList 0.12.5"
  echo
  echo "              (Circular Linear Merge Sort)"
  echo "                1 = clist CURRENT default VAS"
  echo "                2 = clist CURRENT without VAS"
  echo "                3 = clist CURRENT with VAS"
  echo
  echo "              (Global Sort Functions)"
  echo "               -1 = std::sort"
  echo "               -2 = std::stable_sort"
  echo
  echo "  [size]:   data element size"
  echo "  [factor]: X * 1M list size"
  echo
  echo "SUGGEST STARTING WITH size = 4 AND factor = 1"

  exit 1
fi

compiler=

if [ -x "$CC" ]; then
  compiler="$CC"
else if [ -x "`which g++`" ]; then
  compiler="g++"
else
  echo "$0: choose a C++ compiler and set the CC env. variable"
  exit 1
fi fi

echo "using compiler $compiler (use CC env. variable to change)"

file_name1=

if [ -r "../../ta0kira/clist.hpp" ]; then
  file_name1="\"../../ta0kira/clist.hpp\""
  echo "using CList CURRENT header from package"
else if [ -r "/usr/local/include/ta0kira/clist.hpp" ]; then
  file_name1="\"/usr/local/include/ta0kira/clist.hpp\""
  echo "using CList CURRENT header from /usr/local"
else if [ -r "/usr/include/ta0kira/clist.hpp" ]; then
  file_name1="\"/usr/include/ta0kira/clist.hpp\""
  echo "using CList CURRENT header from /usr"
else
  file_name1="<ta0kira/clist.hpp>"
  echo "using CList CURRENT header from default include path (if present)"
fi fi fi

rm -f .t_profile

[ "$2" -gt 0 ] 2> /dev/null

if [ $? -eq 2 ]; then
  [ "$3" -gt 0 ] 2> /dev/null

  if [ $? -eq 2 ]; then
    echo "using user type '$2' from file '#include \"$3\"'"

    if [ -n "$5" ]; then
      echo "using compiler options:" "$5"
    fi

    ( $compiler -DFILE_NAME1="$file_name1" -DT_TYPE=$1 -DUSER_FILE="\"$3\"" -DUSER_TYPE="$2" -DT_FACTOR=$4 $5 test.cpp -o .t_profile 2> /dev/null && ./.t_profile ) || echo "ERROR!"
  else
    echo "using build-in type '$2'"

    if [ -n "$4" ]; then
      echo "using compiler options:" "$4"
    fi

    ( $compiler -DFILE_NAME1="$file_name1" -DT_TYPE=$1 -DUSER_TYPE="$2" -DT_FACTOR=$3 $4 test.cpp -o .t_profile 2> /dev/null && ./.t_profile ) || echo "ERROR!"
  fi

else
    echo "using generic $2-byte structure"

  if [ -n "$4" ]; then
    echo "using compiler options:" "$4"
  fi

  ( $compiler -DFILE_NAME1="$file_name1" -DT_SIZE=$2 -DT_TYPE=$1 -DT_FACTOR=$3 $4 test.cpp -o .t_profile 2> /dev/null && ./.t_profile ) || echo "ERROR!"

fi

rm -f .t_profile
