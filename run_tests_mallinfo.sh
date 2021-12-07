echo -e "Teste Fragmentação:\n"

    ./bin/testing.out --test_fragmentation --find_first_fit
    ./bin/testing.out --test_fragmentation --find_worst_fit
    ./bin/testing.out --test_fragmentation --find_null

    ./bin/testing.out --test_fragmentation --std 
