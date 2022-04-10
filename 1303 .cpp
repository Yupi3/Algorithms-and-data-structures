#include<iostream>
using namespace std;

int otrezki[2][100000];

void stroim_kuchu(int n, int vershina)
{
    //отмечаем родительский элемент, как максиамльный
    int maximum = vershina;
    int l = 2 * vershina + 1;
    int r = 2 * vershina + 2;

    //проверяем дочерние элменты отмечая наибольший, как максимум
    if (l < n && (otrezki[0][l] > otrezki[0][maximum] || (otrezki[0][l] == otrezki[0][maximum] && otrezki[1][l] > otrezki[0][maximum])))
        maximum = l;
    if (r < n && (otrezki[0][r] > otrezki[0][maximum] || (otrezki[0][r] == otrezki[0][maximum] && otrezki[1][r] > otrezki[0][maximum])))
        maximum = r;

    //перестраиваем кучу, если родительский элемент не являлся максимальным
    if (maximum != vershina)
    {
        //меняем местами максиамльный и родительский элементы
        int buff = otrezki[0][vershina];
        otrezki[0][vershina] = otrezki[0][maximum];
        otrezki[0][maximum] = buff;

        buff = otrezki[1][vershina];
        otrezki[1][vershina] = otrezki[1][maximum];
        otrezki[1][maximum] = buff;

        //перестриваем поддерево с корневым элементом, который оказался не максиамльным 
        stroim_kuchu(n, maximum);
    }
}

// сортировка кучей
void sortirovka(int n)
{
    /*строим кучу, вызывая рекурсивну функцию от родительских вершин дерева*/
    for (int i = n / 2 - 1; i >= 0; i--)
        stroim_kuchu(n, i);

    // выполняем сортировку на построенной куче
    int buff;
    for (int i = n - 1; i >= 0; i--)
    {
        // Перемещаем наибольший элемент, хранящийся в корне, в конец массива
        buff = otrezki[0][0];
        otrezki[0][0] = otrezki[0][i];
        otrezki[0][i] = buff;

        buff = otrezki[1][0];
        otrezki[1][0] = otrezki[1][i];
        otrezki[1][i] = buff;

        //перестраиваем кучу на оставшихся элементах
        stroim_kuchu(i, 0);
    }
}

int main()
{
	//вводим границу области покрытия
	int m;
	cin >> m;

	//вводим границы отрезков
	int n = -1;
	do 
	{
		n++;
		cin >> otrezki[0][n] >> otrezki[1][n];
	} while (otrezki[0][n] != 0 || otrezki[1][n] != 0);

    //сортируем кучей, чтобы гарантировано отсортировать за nlogn
    sortirovka(n);
    
    /*будем идти по отрезкам, выбирая элемент с максимальной правой границей,
    покрывающий текущую левую границу l
    если подходящего элемента нет - выводим "No solution"
    если мы нашли подходящий элемент, покрывающий границу m,
    поиск закончен, выводим ответ*/
    int k = 0, l = 0;
    int otvet[2][5000];
    int maximalnyi_l = -1, maximalnyi_r = -1;

    for (int i = 0; i < n; i++)
    {
        //проверяем остались ли ещё отрезки покрывающие левую границу
        if (otrezki[0][i] <= l)
        {
            //проверяем правую границу
            if (otrezki[1][i] > maximalnyi_r)
            {
                maximalnyi_l = otrezki[0][i];
                maximalnyi_r = otrezki[1][i];
            }
        }
        else
        {
            //проверяем, удалось ли найти подходящий отрезок
            if (maximalnyi_r > -1)
            {
                //кладём выбраный отрезок в ответ
                otvet[0][k] = maximalnyi_l;
                otvet[1][k] = maximalnyi_r;
                k++;

                //обновляем левую границу
                l = maximalnyi_r;

                //обнуляем хранимый отрезок
                maximalnyi_l = -1;
                maximalnyi_r = -1;

                //проверяем удалось ли покрыть границу m
                if (l >= m)
                    break;

                //возвращаем i тк мы не проверили текущий отрезок
                i--;
            }

            //нам не удалось найти подходящий отрезок
            else 
                break;
        }
    }

    /*проверим что мы успели положить найденный отрезок
    в ответ до окончания цикла*/
    if (maximalnyi_r > -1)
    {
        otvet[0][k] = maximalnyi_l;
        otvet[1][k] = maximalnyi_r;
        k++;
    }

    //проверяем удаось ли покрыть (0, m) и выводим ответ
    if (otvet[1][k - 1] >= m)
    {
        cout << k << endl;
        for (int i = 0; i < k; i++)
            cout << otvet[0][i] << ' ' << otvet[1][i] << endl;
    }
    else
        cout << "No solution" << endl;

	return 0;
}