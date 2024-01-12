#include <coroutines/coroutine.hpp>
#include <cstdlib>
#include <iostream>

void func(int num) { std::cout << "NUM: " << num << std::endl; }

int main(int argc, char *argv[]) {
    Coroutine cr = Coroutine([&cr] {
        func(2);
        cr.Suspend();
        func(4);
    });

    func(1);
    cr.Call();
    func(3);
    cr.Resume();
    func(5);

    return EXIT_SUCCESS;
}
