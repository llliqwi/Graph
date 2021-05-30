#include <iostream>
#include <vector>
using namespace std;
vector<vector<int>> graph;
vector<int> used, path;
int flag, n, m;
// поиск в глубину для каждой вершины
void dfs(int v) {
    if (flag == 1) return; // если уже нашли цикл, то останавливаемся
    else {
        used[v] = 1; // посещаем вершину 
        path.push_back(v); // добавляем ее в порядок обхода графа
        for (int i = 0; i < graph[v].size(); i++) {
            int to = graph[v][i];// следующая вершина графа
            if (used[to] == 1) { // если мы ее посетили, но не вышли из нее, значит мы нашли цикл
                path.push_back(to); // добавляем следующую вершину в порядок обхода графа
                flag = 1; // ставим индикатор, что мы нашли цикл и останавливаемся
                return;
            }
            else {
                dfs(to); // если не посетили, то посещаем 
            }
            if (flag == 1) return; // если нашли цикл, то останавливаемся 
        }
        used[v] = 2; // если не нашли цикл, то выходим из вершины 
        path.pop_back();
    }
}
// проверяем вершины на наличие цикла 
void checkNodes() {
    for (int i = 1; i <= n; i++) {
        if (used[i] == 0) { // если не посещали вершину, то посещаем ее 
            dfs(i);
            if (flag == 1) return; // если нашли цикл, то останавливаемся
        }
    }
}
int main() {
    int v1, v2;
    cin >> n >> m; // считываем количество вершин и ребер 
    graph.resize(n + 1);
    used.resize(n + 1, 0);
    for (int i = 0; i < m; i++) {
        cin >> v1 >> v2; // считываем ребра и заполняем граф
        graph[v1].push_back(v2);
    }
    checkNodes();  // проверяем вершины на наличие цикла
    if (flag == 1) { // если цикл найден
        int i = path.size() - 2; // последняя вершина цикла   
        int to = path.back(); // вершина в которой зациклились 
        while (path[i] != to) { // получаем индекс вершины в которой зациклились
            i--;
        }
        cout << "YES" << endl;
        while (i < path.size() - 1) { // выводим сам цикл
            cout << path[i] << " ";
            i++;
        }
        cout << endl;
    }
    else cout << "NO" << endl;
}