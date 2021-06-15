#include<iostream>


void __attribute__((noinline)) foo(int a) {

    int b = a+1;
    int res = 0;
    while (b>0) {
        res += b;
        b--;
    }
    std::cout<<res<<std::endl;
}


int main(int argc, char **argv) {

    foo(12);
    return 0;
}

