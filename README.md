# TinyCoroutines

:warning:
works only on `x86-64`

Wrapper on top of [tinycontext]("https://github.com/ppaprikaa/tinycontext") written for my own learning purposes.


:warning:
Please do not use this library, because I'm too lazy to add tests, address sanitizing to internal core library, and many other reasons.



But if you want to play.

Build:
```sh
mkdir build
cmake -S . -B build
cmake --build build/
```

Run:
```
./build/play/coroutines_PLAY
```

Or include this library into your cmake project.

Example:
```C++
void func(int num) { std::cout << "NUM: " << num << std::endl; }

int main(int argc, char *argv[]) {
    Coroutine cr = Coroutine([&cr] {
        func(2);
        cr.Suspend();
        func(4);
    });

    func(1);
    cr();
    func(3);
    cr.Resume();
    func(5);

    return EXIT_SUCCESS;
}
```

output:
```
NUM: 1
NUM: 2
NUM: 3
NUM: 4
NUM: 5
```