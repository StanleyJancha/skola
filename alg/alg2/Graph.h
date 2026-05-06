//
// Created by standa on 4/9/26.
//

#ifndef ALG2_GRAPH_H
#define ALG2_GRAPH_H

using namespace std;
#include <vector>


class Graph {

public:
    void insert(int id);
    void insert(int id, vector<int> neighboursIds);


private:
    class Vertex {
    public:
        int id;
        vector<Vertex*> neighbours;
        Vertex(int id) {
            this->id = id;
        }
        int color = 2; // 0-black, 1-gray, 2-white

    };


    vector<Vertex*> vertices;

    Graph::Vertex* findVertex(int id);
public:
    void DFS_iterative();
    void DFS_recursive();
    void DFS_recursive(Vertex* current);

};


#endif //ALG2_GRAPH_H