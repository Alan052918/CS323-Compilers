for i in {1..9}
do
  echo "test case {$i}"
  ./bin/splc ../project2/ta_test/test_2_r0$i.spl | diff ../project2/ta_test/test_2_r0$i.out -
done

for i in {10..15}
do
  echo "test case {$i}"
  ./bin/splc ../project2/ta_test/test_2_r$i.spl | diff ../project2/ta_test/test_2_r$i.out -
done
