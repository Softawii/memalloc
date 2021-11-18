#include <iostream>
#include "memalloc.hpp"
using namespace std;

int main(int argc, char **argv) {

    int * arr = (int *) memalloc::malloc(sizeof(int) * 10000);

    for(int i = 0; i < 10000; i++) {
        arr[i] = i;
    }

    for(int i = 0; i < 10000; i++) {
        cout << arr[i] << endl;
    }
}