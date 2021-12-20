#include <bits/stdc++.h>
#include "graph.h"
using namespace std;

string cidades[] = {"Arad", "Timisoara", "Zerind", "Oradea", "Lugoj", "Mehadia", "Drobeta", "Sibiu",
						"Rimnicu Vilcea", "Craiova", "Fagaras", "Pitesti", "Giurgiu", "Bucharest", "Neamt",
						"Urziceni", "Iasi", "Vaslui", "Hirsova", "Eforie"};

struct Node{
	int value;
	int cost;
	Node* parent;
	list<Node*> sons; //Filhos na árvore de busca, a borda é a fila de prioridade
};

struct compare{
	bool operator()(const pair<Node*, int> &p1, const pair<Node*, int> &p2){
		return p1.second > p2.second;
	}
};

void printaSolucao(Node* node){
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

bool isNotInBorda(int value,priority_queue<pair<Node*,int>, vector<pair<Node*,int>>, compare> borda){
	while(!borda.empty()){
		if(value == borda.top().first->value)
			return false;
		borda.pop();
	}
	return true;
}

bool isInBordaGreater(int value, int cost,priority_queue<pair<Node*,int>, vector<pair<Node*,int>>, compare> borda ){
	while(!borda.empty()){
		if(value == borda.top().first->value){
			if(borda.top().first->cost > cost){
				return true;
			}
		}
		borda.pop();
	}
	return false;
}

void substitui(Node* filho, priority_queue<pair<Node*,int>, vector<pair<Node*,int>>, compare> &borda ){
	vector<pair<Node*,int>> aux;
	while(!borda.empty()){
		aux.push_back(borda.top());
		if(filho->value == borda.top().first->value){
			if(borda.top().first->cost > filho->cost){
				borda.pop();
				borda.push(make_pair(filho,filho->cost));
				break;
			}
		}
		borda.pop();
	}
	for(auto e : aux){
		borda.push(e);
	}
}

int indexOf(string cidades[], int n, string cidade){
	for(int i=0; i<n; i++){
		if(cidades[i] == cidade)
			return i;
	}
	return -1;
}

void buscaAEstrela(Graph *g, int origem, int destino, vector<int> h){
	priority_queue<pair<Node*,int>, vector<pair<Node*,int>>, compare> borda;
	unordered_map<int,bool> exploreds;
	for(int i=0; i<g->n(); i++)
		exploreds[i] = false;

	Node* atual= new Node();
	atual->value = origem;
	atual->cost = 0; 
	atual->parent = nullptr;

	borda.push(make_pair(atual, h[atual->value]+atual->cost));
	while(!borda.empty()){
		atual = borda.top().first;
		borda.pop();

		if(atual->value == destino){
			printaSolucao(atual);
			return;
		}
			
		exploreds[atual->value] = true;
		for(int i : g->neighbors(atual->value)){
			Node *filho = new Node();
			filho->parent = atual;
			filho->value = i;
			filho->cost = atual->cost + g->weight(atual->value, filho->value); 

			if(!exploreds[filho->value] && isNotInBorda(filho->value,borda)){
				atual->sons.push_back(filho);
				borda.push(make_pair(filho, h[filho->value]+filho->cost));
			}else if(isInBordaGreater(filho->value,filho->cost,borda)){
				substitui(filho,borda);
			}
		}
	}
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
	
	int h_aux[] = {366,329,374,380,244,241,242,253,193,160,176,100,77,0,234,80,226,199,151,161};
	vector<int> h;
	for(int x : h_aux){
		h.push_back(x);
	}
	
	buscaAEstrela(grafo,indexOf(cidades,20, argv[1]),indexOf(cidades,20, "Bucharest"),h);

	return 0;
}