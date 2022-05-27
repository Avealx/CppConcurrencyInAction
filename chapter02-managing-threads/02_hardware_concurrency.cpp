#include <iostream>
#include <thread>
using namespace std;

int main()
{
    cout << "number of threads supported by hardware: " << thread::hardware_concurrency() << endl;
}
