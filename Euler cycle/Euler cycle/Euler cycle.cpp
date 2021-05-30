

#include <iostream>
using namespace std;
struct Node
{
	int inf;
	Node* next;
};

//============================Stack==============================

void push(Node*& st, int dat)
{  // Загрузка числа в стек

	Node* el = new Node;
	el->inf = dat;
	el->next = st;
	st = el;
}

int pop(Node*& st)
{       // Извлечение из стека

	int value = st->inf;
	Node* temp = st;
	st = st->next;
	delete temp;

	return value;
}

int peek(Node* st)
{     // Получение числа без его извлечения
	return st->inf;
}

//==============================================================

Node** graph;   // Массив списков смежности
const int vertex = 1; // Первая вершина

void add(Node*& list, int data)
{  //Добавление смежной вершины

	if (!list) { list = new Node; list->inf = data; list->next = 0; return; }

	Node* temp = list;
	while (temp->next)temp = temp->next;
	Node* elem = new Node;
	elem->inf = data;
	elem->next = NULL;
	temp->next = elem;
}

void del(Node*& l, int key)
{ // Удаление вершины key из списка

	if (l->inf == key) { Node* tmp = l; l = l->next; delete tmp; }
	else
	{
		Node* tmp = l;
		while (tmp)
		{
			if (tmp->next) // есть следующая вершина
				if (tmp->next->inf == key)
				{  // и она искомая
					Node* tmp2 = tmp->next;
					tmp->next = tmp->next->next;
					delete tmp2;
				}
			tmp = tmp->next;
		}
	}
}

int eiler(Node** gr, int num)
{ // Определение эйлеровости графа

	int count;
	for (int i = 0; i < num; i++)
	{  //проходим все вершины

		count = 0;
		Node* tmp = gr[i];

		while (tmp)
		{       // считаем степень
			count++;
			tmp = tmp->next;
		}
		if (count % 2 == 1)return 0; // степень нечетная
	}
	return 1;   // все степени четные
}

void eiler_path(Node** gr)
{ //Построение цикла

	Node* S = NULL;// Стек для  пройденных вершин
	int v = vertex;// 1я вершина (произвольная)
	int u;

	push(S, v); //сохраняем ее в стек
	while (S)
	{  //пока стек не пуст
		v = peek(S); // текущая вершина
		if (!gr[v]) { // если нет инцидентных ребер
			v = pop(S); cout << v + 1 << "   "; //выводим вершину  (у нас отсчет от 1, поэтому +1)
		}
		else
		{
			u = gr[v]->inf; push(S, u);  //проходим в следующую вершину
			del(gr[v], u); del(gr[u], v); //удаляем пройденное ребро
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	system("CLS");
	cout << "Количество вершин:  "; int n; cin >> n; // Количество вершин
	int zn;// Текущее значение

	graph = new Node * [n];
	for (int i = 0; i < n; i++)graph[i] = NULL;
	for (int i = 0; i < n; i++)   // заполняем массив списков

		for (int j = 0; j < n; j++)
		{
			cin >> zn;
			if (zn) add(graph[i], j);
		}

	cout << "\n\nРЕЗУЛЬТАТ  ";

	if (eiler(graph, n))eiler_path(graph);
	else cout << "Граф не является эйлеровым.";

	cout << endl;
	cin.get();
	cin.get();
	return(0);

}