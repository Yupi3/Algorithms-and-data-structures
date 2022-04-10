#include <iostream>
using namespace std;

int n, k;
int kabeli[10000];

/*бинарный поиск по ответу
за logn подбираем длину кабеля такую, что
она лежит в диапазоне заданом условием задачи,
при проверке мы получаем нужно кол-во кабелей*/

int proverka(int dlina)
{
	//суммируем частное деления отрезков на выбраную длину
	int sum = 0;
	for (int i = 0; i < n; i++)
		sum += kabeli[i] / dlina;
	return sum;
}
int bin_poisk(int l, int r)
{
	//возвращаем результат бинпоиска
	if (l + 1 == r)
		return l;
	else
	{
		//берём середину даиапазона
		int m = (l + r) / 2;

		//проверяем соотношение кол-ва искомых кабелей и возможных кабелей данной длины
		if (proverka(m) < k)

			//если кабелей недобор, значит длина слишком большая, заменям r
			return bin_poisk(l, m);
		else

			//если кабелей слишком много или как раз, заменяем l
			return bin_poisk(m, r);
	}
}

int main()
{
	cin >> n >> k;
	double kabel;

	//вводим длины кабелей, переводим в целочисленные для удобства
	for (int i = 0; i < n; i++)
	{
		cin >> kabel;
		kabeli[i] = kabel * 100;
	}

	//считаем ответ бинпоиском
	int otvet = bin_poisk(0, 10000001);

	//выводим ответ с точностью до 2 знаков
	cout << otvet / 100 << '.';
	if (otvet % 100 < 10)
		cout << '0';
	cout << otvet % 100;

	return 0;
}