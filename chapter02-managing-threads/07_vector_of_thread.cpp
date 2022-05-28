#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void foo(int i) {
    cout << i << ": hello world" << endl;
}

int main() {
    vector<thread> threads;
    for(auto i = 0ul; i < 20; ++i)
        threads.emplace_back(foo, i);

    for (auto & t : threads)
        t.join();
}
