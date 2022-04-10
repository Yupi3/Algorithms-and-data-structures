#include <iostream>

using namespace std;

int main() {
    unsigned long long n, a = 0;
    unsigned long long k = 1;
    cin >> n;
    if (n == 0)
        cout << 10;
    else if (n == 1)
        cout << 1;
    else {
        for (int i = 9; i > 1; i = i - 1)
        {
            while (n % i == 0) {
                a = i * k + a;
                n = n / i;
                k = k * 10;
            }
        }
        if (n == 1)
            cout << a;
        else
            cout << "-1";
    }
}

