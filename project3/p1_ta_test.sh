for i in {1..9}
do
  echo "test case: $i"
  ./bin/splc ../project1/ta_test/test_1_r0$i.spl | diff ../project1/ta_test/test_1_r0$i.out -
done

for i in {10..12}
do
  echo "test case: $i"
  ./bin/splc ../project1/ta_test/test_1_r$i.spl | diff ../project1/ta_test/test_1_r$i.out -
done
