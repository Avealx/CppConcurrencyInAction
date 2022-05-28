#include <concepts>
#include <iostream>
#include <thread>

using namespace std;

class jthread_t {
public:

    jthread_t() noexcept = default;

    template<invocable F, typename... Args>
    explicit jthread_t(F&& f, Args&&... args) : t_{ forward<F>(f), forward<Args>(args)... } {}

    explicit jthread_t(thread&& t) noexcept : t_{ move(t) } {}

    jthread_t(jthread_t&& other) noexcept : t_{ move(other.t_) } {}

    jthread_t(jthread_t const&) = delete;

    jthread_t& operator=(jthread_t&& other) {
        if(joinable()) join();

        t_ = move(other.t_);
        return *this;
    }

    jthread_t operator=(jthread_t const &) = delete;

    ~jthread_t() { if(joinable()) join(); }

    void swap(jthread_t & other) noexcept { using std::swap; swap(t_, other.t_); }

    thread::id get_id() const noexcept { return t_.get_id(); }

    bool joinable() { return t_.joinable(); }
    void join()     { t_.join(); }
    void detach()   { t_.detach(); }

    thread      & as_thread()       noexcept { return t_; }
    thread const& as_thread() const noexcept { return t_; }

private:
    thread t_;
};

void foo()
{
    cout << "Hello world" << endl;
}

int main()
{
    jthread_t jt1(foo);
    jthread_t jt2(move(jt1));
}
