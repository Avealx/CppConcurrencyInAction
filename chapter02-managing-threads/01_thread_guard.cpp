#include <iostream>
#include <concepts>
#include <thread>

using namespace std;

class thread_guard
{
public:
    thread_guard(thread & t) : t{t}
    {
    }

    ~thread_guard()
    {
        t.join();
    }

    thread_guard(thread_guard const &) = delete;
    thread_guard& operator=(thread_guard const &) = delete;

private:
        thread & t;
};

class joining_thread
{
public:
    template <invocable F>
    joining_thread(F f) : t{f}
    {
    }

    ~joining_thread()
    {
        t.join();
    }

    joining_thread(joining_thread const &) = delete;

    joining_thread& operator=(joining_thread const &) = delete;

private:
    thread t;
};

void foo()
{
    cout << "Hello from foo." << endl;
}

int main()
{
    thread t{foo};
    thread_guard tg{t};

    joining_thread gt{foo};
}
