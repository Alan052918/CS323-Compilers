#!/bin/bash
echo "---------------------------------------------"
echo "SIMULATING running [$1] test case [$2]"
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
    $IRSIM ./test/test_3_r0$2.ir
  else
    $IRSIM ./test/test_3_r$2.ir
  fi
elif test $1 = "sample"; then
  if test $2 -lt 10; then
    $IRSIM ./sample/test0$2.ir
  else
    echo "test case index out of bounds: sample only has 4 test cases"
  fi
else
  echo "Unsupported directory: $1"
fi
