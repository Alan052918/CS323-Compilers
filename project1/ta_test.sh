for i in {1..9}
do
  echo "test case {$i}"
  ./bin/splc ta_test/test_1_r0$i.spl | diff ta_test/test_1_r0$i.out -
done

for i in {10,11,12}
do
  echo "test case {$i}"
  ./bin/splc ta_test/test_1_r$i.spl | diff ta_test/test_1_r$i.out -
done
