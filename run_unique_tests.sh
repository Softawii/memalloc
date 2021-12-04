rm -f "res/results.csv"

echo -e "Teste base:\n"
./bin/testing.out --test_base --print
echo
./bin/testing.out --test_base --std --print
 
echo -e "\nTeste de alocação e desalocação:\n"
./bin/testing.out --test_malloc_free --print
echo
./bin/testing.out --test_malloc_free --std --print

echo -e "\nTeste de alocação: \n"
./bin/testing.out --test_alloc --print
echo
./bin/testing.out --test_alloc --std --print

echo -e "\nTeste de sobreposição:\n"
./bin/testing.out --test_overlap --print
echo
./bin/testing.out --test_overlap --std --print

echo -e "\nTeste de sobreposição intensivo:\n"
./bin/testing.out --test_intensive_overlap --print
echo
./bin/testing.out --test_intensive_overlap --std --print