#!/bin/bash
echo "DEBUG running project [$1] test case [$2]"

if test $2 -lt 10; then
    ./bin/splc ../project$1/ta_test/test_$1_r0$2.spl
elif test $1 -eq 1 && test $2 -gt 12; then
    echo "Test case index out of bounds: project 1 only has 12 test cases"
elif test $1 -eq 2 && test $2 -gt 15; then
    echo "Test case index out of bounds: project 2 only has 15 test cases"
else
    ./bin/splc ../project$1/ta_test/test_$1_r$2.spl
fi
