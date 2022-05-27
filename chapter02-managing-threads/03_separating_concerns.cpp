#include <iostream>
#include <string>
#include <thread>

using namespace std;

void foo()
{
    string input;

    cout << "enter something:\n";
    cin >> input;

    while (input != "exit") {
        cout << input << '\n';

        cout << "enter something:\n";
        cin >> input;
    }
}

int main()
{
    thread t{foo};
    if (t.joinable())
        t.detach();

    for (int i = 10; i-- > 1;) {
        cout << i << " seconds remaining...\n";
        sleep(1);
    }
    cout << "done." << endl;
}
