#include <iostream>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int* a = new int[n]; // массив значений
    int* b = new int[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    bool flag = true; // добавим флаг состояния
    int z = 0;
    int x = 0;
    int c = 0;
    while (flag and z < n)
        if (c > 0 and b[c - 1] == a[z]) // с 16 по 24 проверяем на читерство
        {
            c = c - 1;
            z = z + 1;
        }
        else if (x < n) {
            b[c] = ++x;
            c = c + 1;
        }
        else {
            flag = false; // Да, он читер!
        }
    if (flag) {
        cout << "Not a proof";
    }
    else {
        cout << "Cheater";
    }
}
