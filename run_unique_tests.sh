rm -f "res/results.csv"

echo -e "Teste base:\n"
./testing.out --test_base --print
echo
./testing.out --test_base --std --print
 
echo -e "\nTeste de alocação e desalocação:\n"
./testing.out --test_malloc_free --print
echo
./testing.out --test_malloc_free --std --print

echo -e "\nTeste de alocação: \n"
./testing.out --test_alloc --print
echo
./testing.out --test_alloc --std --print

echo -e "\nTeste de sobreposição:\n"
./testing.out --test_overlap --print
echo
./testing.out --test_overlap --std --print

echo -e "\nTeste de sobreposição intensivo:\n"
./testing.out --test_intensive_overlap --print
echo
./testing.out --test_intensive_overlap --std --print