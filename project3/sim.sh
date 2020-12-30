#!/bin/bash
echo "---------------------------------------------"
echo "SIMULATING running [$1] test case [$2]"
echo "---------------------------------------------"

if test $1 = "test"; then
  if test $2 -lt 10; then
    ./simulator/dist/irsim ./test/test_3_r0$2.ir
  else
    ./simulator/dist/irsim ./test/test_3_r$2.ir
  fi
elif test $1 = "sample"; then
  if test $2 -lt 10; then
    ./simulator/dist/irsim ./sample/test0$2.ir
  else
  echo "test case index out of bounds: sample only has 4 test cases"
  fi
else
  echo "Unsupported directory: $1"
fi
