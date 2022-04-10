
#include <iostream>
#include <vector>

using namespace std;
#define POG 500001
vector<pair<int, int>> vertexes[POG];
int massiv[POG][20], vvod_k[POG], vuhod_k[POG], glubina[POG], rus[POG];
int k;
int logg;

void DFS(int v, int d) { //ПОИСК В ГЛУБИНУ ГРАФА
	glubina[v] = d;
	vvod_k[v] = k++; //Находим родителей вершины
	massiv[v][0] = rus[v];
	for (int i = 1; i <= logg; i++)
		massiv[v][i] = massiv[massiv[v][i - 1]][i - 1];
	for (int i = 0; i < vertexes[v].size(); i++) {
		int next = vertexes[v][i].first;
		if (next != rus[v]) {
			rus[next] = v;
			DFS(next, d + vertexes[v][i].second);
		}
	}
	vuhod_k[v] = k++; 
}

int find_lca(int a, int b) { //метод бинарного подъёма чтобы найти индекс предка
	if (vvod_k[a] <= vvod_k[b] && vuhod_k[a] >= vuhod_k[b])
		return a;
	else
		if (vvod_k[b] <= vvod_k[a] && vuhod_k[b] >= vuhod_k[a])
			return b;
	for (int i = logg; i >= 0; i--) {
		if (!(vvod_k[massiv[a][i]] <= vvod_k[b] && vuhod_k[massiv[a][i]] >= vuhod_k[b]))
			a = massiv[a][i];
	}
	return massiv[a][0];
}

int main() {
	int n, m;
	std::cin >> n;
	logg = 1; //log2(n)
	while (true) {
		if ((1 << logg) > n)
			break;
		logg++;
	}
	for (int i = 0; i < n - 1; i++) {
		int u, v, w;
		std::cin >> u >> v >> w;
		vertexes[u].push_back(std::make_pair(v, w));
		vertexes[v].push_back(std::make_pair(u, w));
	}
	rus[0] = 0; //первая вершина родителя
	DFS(0, 0); //выполняем поиск в глубину
	cin >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		cout << glubina[u] + glubina[v] - 2 * glubina[find_lca(u, v)] << '\n'; //находим расстояние;Mission  passed
	}
	return 0;
}
