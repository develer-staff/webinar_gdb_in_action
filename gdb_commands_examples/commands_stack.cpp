#include <iostream>

int foo_3(int c) {
    int k = c*(c-1);
    return c/2;
}

int foo_2(int b) {
    int w = b*2;
    return foo_3(w);
}

int foo_1(int a) {
    int z = a+1;
    return foo_2(z);
}

int main(int argc, char **argv) {
    int value = foo_1(12);
    std::cout << value << std::endl;
    return 0;
}

