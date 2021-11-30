#include "graph.h"
#include <string>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

Graph::Graph(int n){
    if( n <= 0 ) throw std::runtime_error("Tamanho invalido");

    N = n;
    M = 0;

    mark = new int[n];
    for(int i = 0; i<n; i++)
        mark[i] = 0;

    edges = vector<list<pair<int, int>>>(n);
}

Graph::~Graph() {
    delete[] mark;
    edges.clear();
} 

void Graph::checkVertex(int v) {
    if(v < 0 || v > N-1 ) 
        throw std::runtime_error("Intervalo de valor de vertice invalido");
}

int Graph::n(){
    return this->N;
}

int Graph::m(){
    return this->M;
}

list<int> Graph::neighbors(int v){
    checkVertex(v);
    list<int> lst = list<int>();
    if(v >= 0 && v < N){

        for(pair<int, int> p : edges[v])
            lst.push_back(p.first);
        
        return lst;
    }
    return lst;
} 

list<pair<int, int>> Graph::incidentEdges(int v){
    checkVertex(v);
    list<pair<int, int>> lst = list<pair<int, int>>();
    if(v >= 0 && v < N){
        return edges[v];
    }else{
        return lst;
    }
}

void Graph::setEdgeWeight(int v1, int v2, int wgt){
    checkVertex(v1);
    checkVertex(v2);
    if( wgt <= 0 ) throw std::runtime_error("Peso negativo ou igual a zero");

    if(!isEdge(v1,v2)){
        M++;
        edges[v1].push_back(pair<int,int>(v2, wgt));
    }else{
        for(pair<int, int> p : edges[v1]){
            if(p.first == v2){
                p.second = wgt;
            }
        }
    }
}

void Graph::addEdge(int v1, int v2, int weight){
    checkVertex(v1);
    checkVertex(v2);
    setEdgeWeight(v1, v2, weight);
}

bool Graph::isEdge(int v1, int v2){
    checkVertex(v1);
    checkVertex(v2);
    for(pair<int, int> p : edges[v1]){
        if(p.first == v2){
            return true;
        }
    }
    return false;
}

int Graph::weight(int v1, int v2){
    checkVertex(v1);
    checkVertex(v2);
    for(pair<int, int> p : edges[v1]){
        if(p.first == v2){
            return p.second;
        }
    }
    return 0;
}

int Graph::getMark(int v){
    checkVertex(v);
    return mark[v];
}

void Graph::setMark(int v, int value){
    checkVertex(v);
    mark[v] = value;
}

void Graph::resetMarks(){
    for(int i=0; i<N; i++)
        mark[i] = 0;
}