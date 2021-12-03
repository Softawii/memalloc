rm "res/results.csv"
clear

echo -e "Teste base:\n"
./testing.out --test_base
echo
./testing.out --test_base --std
echo -e "\nAperte enter para continuar..."
read x
clear


echo -e "Teste de alocação e desalocação:\n"
./testing.out --test_malloc_free
echo
./testing.out --test_malloc_free --std
echo -e "\nAperte enter para continuar..."
read x
clear

echo -e "Teste de alocação: \n"
./testing.out --test_alloc
echo
./testing.out --test_alloc --std
echo -e "\nAperte enter para continuar..."
read x
clear

echo -e "Teste de sobreposição:\n"
./testing.out --test_overlap
echo
./testing.out --test_overlap --std
echo -e "\nAperte enter para continuar..."
read x
clear