#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <list>
#include <vector>

using namespace std;

class Graph {
    private:
        int N;
        int M;
        int *mark;
        vector< list<pair<int, int>> > edges;

        void checkVertex(int v);
    
    public: 
        Graph(int n);
       ~Graph();

        int n();
        int m();

        list<int> neighbors(int v); 

        list<pair<int, int>> incidentEdges(int v);


        void setEdgeWeight(int v1, int v2, int wgt);

        void addEdge(int v1, int v2, int weight);

        void delEdge(int v1, int v2);

        bool isEdge(int v1, int v2);


        int weight(int v1, int v2);

        int getMark(int v);
        void setMark(int v, int value);
        void resetMarks();
};

#endif