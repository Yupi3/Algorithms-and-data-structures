#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n, q;
	scanf( " % d", n);
	vector <int> a(n); // создадим массив чисел ci
	for (int i = 0; i < n; i++) {
		scanf("%s", a[i]);
	}
	scanf(" % d", q);;
	vector <int> l(q);
	vector <int> r(q);
	vector <int> x(q);
	vector <int> d(q, 0);
	for (int i = 0; i < q; i++) {
		cin >> l[i] >> r[i] >> x[i];
	}
	for (int i = 0; i < q; i++) {
		for (int j = l[i] - 1; j < r[i]; j++) {
			if (x[i] == a[j]) {
				d[i] = 1;
			}
		}
	}
	for (int i = 0; i < q; i++) {
		printf("%s", d[i]);
	}
}