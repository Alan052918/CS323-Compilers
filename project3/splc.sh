#!/bin/bash
echo "---------------------------------------------"
echo "SPLC running [$1] test case [$2]"
echo "---------------------------------------------"

if test $1 = "sample"; then
    ./bin/splc ./sample/test0$2.spl
elif test $1 = "test"; then
    if test $2 -lt 10; then
        ./bin/splc ./test/test_3_r0$2.spl
    else
        ./bin/splc ./test/test_3_r$2.spl
    fi
fi
