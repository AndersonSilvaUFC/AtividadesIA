#include <bits/stdc++.h>
#include "graph.h"
using namespace std;

string cidades[] = {"Arad", "Timisoara", "Zerind", "Oradea", "Lugoj", "Mehadia", "Drobeta", "Sibiu",
						"Rimnicu Vilcea", "Craiova", "Fagaras", "Pitesti", "Giurgiu", "Bucharest", "Neamt",
						"Urziceni", "Iasi", "Vaslui", "Hirsova", "Hirsova"};

struct Node{
	int value;
	int custo_atual;
	Node* parent;
	list<Node*> filhos;
};

void printaSolucao(Graph *g, vector<int> l){
	int custo = 0;
	int i;
	for(i = 0; i<l.size()-1; i++){
		custo += g->weight(l.at(i),l.at(i+1));

		cout << cidades[l.at(i)] << " -> ";

	}
	cout << cidades[l.at(i)] << ". Custo total: " << custo << endl;
}

vector<int> transforma(Node* node){
	vector<int> ans = vector<int>();
	while(node != nullptr){
		ans.push_back(node->value);
		node = node->parent;
	}
	reverse(ans.begin(), ans.end());
	return ans;
}

vector<int> buscaCustoUniforme(Graph *g, int origem, int destino){
	queue<Node*> q = queue<Node*>();

	Node* atual= new Node();
	atual->parent = nullptr;
	atual->value = origem;
	atual->custo_atual = 0;
	q.push(atual);
	while(!q.empty()){
		atual = q.front();
		q.pop();

		if(atual->value == destino)
			return transforma(atual);

		for(int i : g->neighbors(atual->value)){
			Node* filho = new Node();
			filho->parent = atual;
			filho->value = i;
			filho->custo_atual += g->weight(atual->value, filho->value); 
			if(g->getMark(i) != 1){
				atual->filhos.push_back(filho);
				q.push(filho);
				g->setMark(i,1);
			}else if(q.front()->value == filho->value && q.front()->custo_atual > filho->custo_atual){
				//cout << "hehe" << endl;
				q.pop();
				q.push(filho);
				atual->filhos.push_back(filho);
			}
		}
	}
	return vector<int>();
}

int indexOf(string cidades[], int n, string cidade){
	for(int i=0; i<n; i++){
		if(cidades[i] == cidade)
			return i;
	}
	return -1;
}

int main(int argc, char *argv[]){
	int N = 25;
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

	
	vector<int> solucao = buscaCustoUniforme(grafo,indexOf(cidades,20, argv[1]),indexOf(cidades,20, "Bucharest"));
	printaSolucao(grafo,solucao);

	return 0;
}