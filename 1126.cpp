#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int m;
    int x;

    cin >> m;
    int n = 25000;
    vector <int> a(n);
    for (int i = 0; i < 25000; i++) {
        cin >> a[i];
        if (a[i] != -1) {
             x = x + 1;
        }
        else {
            break;
        }
    }
    int d = 0;
    int b = x - m + 1;
    vector <int> c(n);
    for (int i = 0; i < b; i++) {
        d = 0;
        for (int j = (m + i - 1); j >= i; j = j - 1) {
            if (a[j] >= d) {
                d = a[j];
                c[i] = d;
            }
        }
    }
    for (int i = 0; i < b; i++) {
        std::cout << c[i] << std::endl;
    }
}