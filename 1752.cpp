
#include <iostream>
#include <vector>
#include <utility>
using namespace std;
#define POG 20001

int positions[POG];
int puti[POG];
pair<int, int> glubina[POG];
vector<int> roditel[POG];
vector<int> rebenok[POG];
pair<int, int> gl_reb[POG];
int predki[POG];
int cn = 0;

int max(int a, int b)
{
	return (a < b) ? b : a;
}

vector<int>::iterator find(vector<int>::iterator first, vector<int>::iterator last, int value) {

	for (; first != last; ++first) {
		if (*first == value) {
			return first;
		}
	}
	return last;
}

// глубина для каждого узла
void dfs(int u) {
	gl_reb[u].first = 0;
	gl_reb[u].second = 0;
	int n = roditel[u][0];
	for (int i = 0; n && i < roditel[n].size(); i++) {
		n = roditel[n][i];
		roditel[u].push_back(n);
	}
	if (roditel[u][0])
		rebenok[u].erase(find(rebenok[u].begin(), rebenok[u].end(), roditel[u][0])); //удаление соседей и нахождение глубины
	//нахождение самого глубокого детя
	for (int i = 0; i < rebenok[u].size(); i++) {
		int c = rebenok[u][i];
		glubina[c].first = glubina[u].first + 1;
		roditel[c].push_back(u);
		dfs(c);
		if (glubina[c].second > glubina[gl_reb[u].second].second) {
			if (glubina[c].second > glubina[gl_reb[u].first].second) {
				gl_reb[u].second = gl_reb[u].first;
				gl_reb[u].first = c;
			}
			else
				gl_reb[u].second = c;
		}
	}
	glubina[u].second = max(glubina[u].first, max(glubina[gl_reb[u].second].second, glubina[gl_reb[u].first].second));
}

//находим массив глубин родителей
void dfs_2(int u) {
	// The longest path from our parent to a child
	if (roditel[u][0] && gl_reb[roditel[u][0]].first == u) {
		positions[u] = positions[roditel[u][0]] + 1;
		puti[positions[u]] = u;
	}
	else {  // создадим новый массив и добавим пути
		positions[u] = cn;
		puti[positions[u]] = u;
		cn += glubina[u].second - glubina[u].first + 1;
	}
	if (roditel[u][0]) { //узлы предков
		int ni;
		if (gl_reb[roditel[u][0]].first == u)
			ni = gl_reb[roditel[u][0]].second;
		else
			ni = gl_reb[roditel[u][0]].first;
		// Если кандидат подходит  и это самый длинный путь то назначаем его иначе сохраняем родителя
		if (predki[roditel[u][0]] != 0 && (glubina[ni].second - glubina[ni].first < glubina[predki[roditel[u][0]]].second + glubina[u].first - 2 * glubina[predki[roditel[u][0]]].first) || ni == 0)
			predki[u] = predki[roditel[u][0]];
		else
			predki[u] = ni;
	}
	for (int i = 0; i < rebenok[u].size(); i++) dfs_2(rebenok[u][i]);
}


int answer(int u, int d) { //Поиск узлов ниже и выше нас
	if (d > glubina[u].second - glubina[u].first) {
		if (d < glubina[u].first) {
			for (int i = 0; ; i++) {
				if (d == 0)
					break;
				if (d % 2 == 1)
					u = roditel[u][i];
				d /= 2;
			}
			return u;
		}
		else { //проверим предков
			if (predki[u] == 0)
				return 0;
			else {
				if (predki[u] != 0 && d <= glubina[u].first - glubina[predki[u]].first + glubina[predki[u]].second - glubina[predki[u]].first + 2)
					return puti[d - glubina[u].first + glubina[predki[u]].first - 2 + positions[predki[u]]];
				else
					return 0;
			}
		}
	}
	else
		return puti[positions[u] + d];
}


int main() {

	int N, m, u, v;
	cin >> N >> m;
	for (int i = 1; i < N; i++) {
		cin >> u >> v;
		rebenok[u].push_back(v);
		rebenok[v].push_back(u);
	}

	roditel[1].push_back(0);
	predki[1] = 0;
	positions[1] = cn;
	glubina[1].first = 1;

	dfs(1);
	dfs_2(1);


	int distance;
	vector<int> a;

	for (int i = 0; i < m; i++) {
		cin >> u >> distance;
		a.push_back(answer(u, distance));
	}

	for (int i = 0; i < a.size(); i++)
		cout << a[i] << '\n';
	return 0;
}
