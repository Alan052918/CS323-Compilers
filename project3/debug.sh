#!/bin/bash
echo "-----------------------------------------"
echo "DEBUG running [$1] test case [$2]"
echo "-----------------------------------------"

if test $1 = "sample"; then
    ./bin/debug ./sample/test0$2.spl
elif test $1 = "test"; then
    if test $2 -lt 10; then
        ./bin/debug ./test/test_3_r0$2.spl
    else
        ./bin/debug ./test/test_3_r$2.spl
    fi
fi
