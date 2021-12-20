#include <bits/stdc++.h>
#include "graph.h"
using namespace std;

string cidades[] = {"Arad", "Timisoara", "Zerind", "Oradea", "Lugoj", "Mehadia", "Drobeta", "Sibiu",
						"Rimnicu Vilcea", "Craiova", "Fagaras", "Pitesti", "Giurgiu", "Bucharest", "Neamt",
						"Urziceni", "Iasi", "Vaslui", "Hirsova", "Hirsova"};

struct Node{
	int value;
	int cost;
	Node* parent;
	list<Node*> sons; //Filhos na árvore de busca, a borda é a fila
};

void printaSolucao(Graph *g, Node* node){
	int custo = node->cost;

	vector<int> ans = vector<int>();
	while(node != nullptr){
		ans.push_back(node->value);
		node = node->parent;
	}
	reverse(ans.begin(), ans.end());

	int i;
	for(i = 0; i<ans.size()-1; i++){
		cout << cidades[ans.at(i)] << " -> ";
	}
	cout << cidades[ans.at(i)] << ". Custo total: " << custo << endl;
}

bool isNotInBorda(int value,queue<Node*> borda){
	while(!borda.empty()){
		if(value == borda.front()->value)
			return false;
		borda.pop();
	}
	return true;
}

void bfs(Graph *g, int origem, int destino){
	queue<Node*> borda = queue<Node*>();
	unordered_map<int,bool> exploreds;
	for(int i=0; i<g->n(); i++)
		exploreds[i] = false;

	Node* atual= new Node();
	atual->value = origem;
	atual->cost = 0;
	atual->parent = nullptr;
	borda.push(atual);

	while(!borda.empty()){
		atual = borda.front();
		exploreds[atual->value]= true;
		borda.pop();

		for(int i : g->neighbors(atual->value)){
			Node* filho = new Node();
			filho->value = i;
			filho->cost = atual->cost + g->weight(atual->value, filho->value);
			filho->parent = atual;
			atual->sons.push_back(filho);
			if(!exploreds[filho->value] && isNotInBorda(filho->value,borda)){
				if(filho->value == destino){
					printaSolucao(g,filho);
					return;	
				}
				borda.push(filho);
			}
		}
	}
}

int indexOf(string cidades[], int n, string cidade){
	for(int i=0; i<n; i++){
		if(cidades[i] == cidade)
			return i;
	}
	return -1;
}

int main(int argc, char *argv[]){
	int N = 20;
	Graph *grafo;
	grafo = new Graph( N );

	grafo->addEdge(0,2,75);
	grafo->addEdge(2,0,75);

	grafo->addEdge(0,1,118);
	grafo->addEdge(1,0,118);

	grafo->addEdge(0,7,140);
	grafo->addEdge(7,0,140);

	grafo->addEdge(1,4,111);
	grafo->addEdge(4,1,111);

	grafo->addEdge(2,3,71);
	grafo->addEdge(3,2,71);

	grafo->addEdge(3,7,151);
	grafo->addEdge(7,3,151);

	grafo->addEdge(4,5,70);
	grafo->addEdge(5,4,70);

	grafo->addEdge(5,6,75);
	grafo->addEdge(6,5,75);

	grafo->addEdge(6,9,120);
	grafo->addEdge(9,6,120);

	grafo->addEdge(7,8,80);
	grafo->addEdge(8,7,80);

	grafo->addEdge(7,10,99);
	grafo->addEdge(10,7,99);

	grafo->addEdge(8,9,146);
	grafo->addEdge(9,8,146);

	grafo->addEdge(8,11,97);
	grafo->addEdge(11,8,97);

	grafo->addEdge(9,11,138);
	grafo->addEdge(11,9,138);

	grafo->addEdge(10,13,211);
	grafo->addEdge(13,10,211);

	grafo->addEdge(11,13,101);
	grafo->addEdge(13,11,101);

	grafo->addEdge(12,13,90);
	grafo->addEdge(13,12,90);

	grafo->addEdge(13,15,85);
	grafo->addEdge(15,13,85);

	grafo->addEdge(14,16,87);
	grafo->addEdge(16,14,87);

	grafo->addEdge(15,17,142);
	grafo->addEdge(17,15,142);

	grafo->addEdge(15,18,98);
	grafo->addEdge(18,15,98);

	grafo->addEdge(16,17,92);
	grafo->addEdge(17,16,92);

	grafo->addEdge(18,19,86);
	grafo->addEdge(19,18,86);

	
	bfs(grafo,indexOf(cidades,20, argv[1]),indexOf(cidades,20, "Bucharest"));

	return 0;
}