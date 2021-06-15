#include <thread>
#include <iostream>

void foo1() {
    int a;
    std::cin >> a;
}

void foo2() {
    int a;
    while(true) a++;
}

int main(int argc, char **argv) {

    std::thread t1(foo1);
    std::thread t2(foo2);

    t1.join();
    t2.join();

}
