#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

int main() {
	int n;
	double a, b, d, a1; //a это a0 ,b это аn+1,d это насколько изменилось значение с, a1- искомое значение 
	d = 0;
	cin >> n;
	cin >> a >> b;
	vector <double> c(n); // создадим массив чисел ci
	for (int i = 0; i < n; i++) {
		cin >> c [i];
	}
	//
	for (int i = 0; i < n; i++) {
	d = d + (n - i) * c [i];
	}
	a1 = (n * a + b - 2 * d) / (n + 1);
	//чтобы корректно записать значение с запятой
	cout << fixed << setprecision(2) << a1;
}
