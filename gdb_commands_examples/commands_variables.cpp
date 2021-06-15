#include<iostream>
#include<vector>
#include<string>

struct A {
    int a_1;
    int a_2;
    double a_3;
};

struct B {
    A b_1;
    std::vector<bool> b_2;
};

struct C {
    A c_1;
    B c_2;
};

void foo(C &c) {
    std::cout << c.c_1.a_1 << std::endl;
}

int main(int argc, char **argv) {
    
    std::cout << "start" << std::endl;
    C my_var = {
        .c_1 = {.a_1=1, .a_2=2, .a_3=3.14},
    };

    foo(my_var);
    std::cout << "end" << std::endl;
    return 0;
}

