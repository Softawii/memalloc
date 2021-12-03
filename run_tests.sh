rm -f "res/results.csv"

echo -e "Teste base:\n"
for counter in {1..5001..10}; do
    if [ $(((counter - 1)%100)) = $((0)) ]; then 
        echo -e '\e[1A\e[K'$((counter-1))'/5000'
    fi
    ./testing.out --test_base -n $((counter))
    ./testing.out --test_base --std -n $((counter))
done

echo -e "\nTeste de alocação e desalocação:\n"
for counter in {1..5001..10}; do
    if [ $(((counter - 1)%100)) = $((0)) ]; then 
        echo -e '\e[1A\e[K'$((counter-1))'/5000'
    fi
    ./testing.out --test_malloc_free -n $((counter))
    ./testing.out --test_malloc_free --std -n $((counter))
done

echo -e "\nTeste de alocação:\n"
for counter in {1..5001..10}; do
    if [ $(((counter - 1)%100)) = $((0)) ]; then 
        echo -e '\e[1A\e[K'$((counter-1))'/5000'
    fi
    ./testing.out --test_alloc -n $((counter))
    ./testing.out --test_alloc --std -n $((counter))
done

echo -e "\nTeste de sobreposição:\n"
for counter in {1..5001..10}; do
    if [ $(((counter - 1)%100)) = $((0)) ]; then 
        echo -e '\e[1A\e[K'$((counter-1))'/5000'
    fi
    ./testing.out --test_overlap -n $((counter))
    ./testing.out --test_overlap --std -n $((counter))
done

echo -e "\nTeste de sobreposição intensivo:\n"
for counter in {1..5001..10}; do
    if [ $(((counter - 1)%100)) = $((0)) ]; then 
        echo -e '\e[1A\e[K'$((counter-1))'/5000'
    fi
    ./testing.out --test_intensive_overlap -n $((counter))
    ./testing.out --test_intensive_overlap --std -n $((counter))
done