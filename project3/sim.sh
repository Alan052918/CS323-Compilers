#!/bin/bash
echo "---------------------------------------------"
echo "SIMULATE running [$1] test case [$2]"
echo "---------------------------------------------"

OS=$(uname -a | cut -d" " -f 1)
LINUX_IRSIM=./simulator/dist-Ubuntu/irsim
MACOS_IRSIM=./simulator/dist-macOS/irsim

if test $OS = "Darwin"; then
  IRSIM=$MACOS_IRSIM
elif test $OS = "Linux"; then
  IRSIM=$LINUX_IRSIM
else
  echo "Unsupported operating system"
  exit 1
fi

if test $1 = "test"; then
  if test $2 -lt 10; then
    if test $# -eq 2; then
      $IRSIM ./test/test_3_r0$2.ir
    elif test $# -eq 3; then
      $IRSIM ./test/test_3_r0$2.ir -i $3
    elif test $# -eq 4; then
      $IRSIM ./test/test_3_r0$2.ir -i $3,$4
    else
      echo "Too many arguments"
      exit 1
    fi
  else
    if test $# -eq 2; then
      $IRSIM ./test/test_3_r$2.ir
    elif test $# -eq 3; then
      $IRSIM ./test/test_3_r$2.ir -i $3
    elif test $# -eq 4; then
      $IRSIM ./test/test_3_r$2.ir -i $3,$4
    else
      echo "Too many arguments"
      exit 1
    fi
  fi
elif test $1 = "sample"; then
  if test $2 -lt 10; then
    if test $# -eq 2; then
      $IRSIM ./sample/test0$2.ir
    elif test $# -eq 3; then
      $IRSIM ./sample/test0$2.ir -i $3
    elif test $# -eq 4; then
      $IRSIM ./sample/test0$2.ir -i $3,$4
    else
      echo "Too many arguments"
      exit 1
    fi
  else
    echo "test case index out of bounds: sample only has 4 test cases"
    exit 1
  fi
else
  echo "Unsupported directory: $1"
  exit 1
fi
