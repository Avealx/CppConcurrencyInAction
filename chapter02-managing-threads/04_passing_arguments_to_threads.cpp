#include <iostream>
#include <string>
#include <thread>
using namespace std;

template <typename T>
void foo(T&& x)
{

    cout << "got: " << x++ << endl;
    cout << "its now: " << x << endl;
}

void bar(int x, string const & str) {
    cout << "got string: " << str << endl;
}

int main()
{
    int x = 42;
    thread t{foo<int&>, ref(x)};
    t.detach();
    cout << "The original value of x is: " << x << endl;

    thread th{bar, 3, "Hello world!"}; // undefined behaviour
    th.join();                         // with th.join() it's ok

    char buffer[] = "Hello world!!"; // undefined behaviour
    thread thr{bar, 3, buffer};      // with thr.detach(), with thr.join() it's ok
    thr.detach();

    char buffer2[] = "Hello world!!!";       // should be okay, but is also undefined behaviour 
    thread thre{bar, 3, string(buffer2)};    // in gcc-11 o.o
    thre.detach();
}
