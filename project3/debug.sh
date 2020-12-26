#!/bin/bash
echo "-----------------------------------------"
echo "DEBUG running project [$1] test case [$2]"
echo "-----------------------------------------"

if test $# -lt 2; then
    echo "Too few arguments: debug <project index> <test case index>"
    exit 1
fi

if test $# -gt 2; then
    echo "Too many arguments: debug <project index> <test case index>"
    exit 1
fi


if test $1 -eq 1 && test $2 -gt 12; then
    echo "Test case index out of bounds: project 1 only has 12 test cases"
    exit 1
fi

if test $1 -eq 2 && test $2 -gt 15; then
    echo "Test case index out of bounds: project 2 only has 15 test cases"
    exit 1
fi

if test $2 -lt 10; then
    ./bin/debug ../project$1/ta_test/test_$1_r0$2.spl
else
    ./bin/debug ../project$1/ta_test/test_$1_r$2.spl
fi
