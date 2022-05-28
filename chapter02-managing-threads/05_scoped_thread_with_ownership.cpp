#include <iostream>
#include <thread>

using namespace std;


class scoped_thread_t {
public:
    scoped_thread_t(thread t) : t_{move(t)}
    {
        if (!t_.joinable())
            throw logic_error("no thread");
    }

    ~scoped_thread_t()
    {
        t_.join();
    }

    scoped_thread_t(scoped_thread_t const &) = delete;

    scoped_thread_t operator=(scoped_thread_t const &) = delete;

private:
    thread t_;
};

void foo()
{
    cout << "hello world" << endl;
}

int main() {
    thread t{foo};
    scoped_thread_t scoped_thread{move(t)};
    jthread jt{foo};
}
