//
// Created by standa on 4/9/26.
//

#include "Graph.h"

#include <iostream>
#include <stack>
#include <vector>

void Graph::insert(int id) {
    this->vertices.push_back(new Vertex(id));
}

void Graph::insert(int id, vector<int> neighboursIds) {

    Vertex* vertex = new Vertex(id);
    this->vertices.push_back(vertex);

    for (auto neighboursId : neighboursIds) {
        Vertex *neighbour = findVertex(neighboursId);

        if (neighbour != nullptr) {
            vertex->neighbours.push_back(neighbour);
            if (vertex != neighbour){
                neighbour->neighbours.push_back(vertex);
            }
        }
    }
}

Graph::Vertex* Graph::findVertex(int id) {
    for (auto vertex : this->vertices) {
        if (vertex->id == id) {
            return vertex;
        }
    }

    return nullptr;
}


void Graph::DFS_iterative() {
    if (!this->vertices.empty()) {

        stack<Vertex*> stack;

        Vertex* current = this->vertices.front();
        current->color = 1;

        stack.push(current);

        while (!stack.empty()) {
            current = stack.top();
            stack.pop();

            cout << current->id << endl;
            current->color = 0;

            for (auto neighbour: current->neighbours) {
                if (neighbour->color == 2) {
                    stack.push(neighbour);
                    neighbour->color = 1;
                }
            }
        }

    }
}

void Graph::DFS_recursive() {

    if (this->vertices.empty()) {
        return;
    }
    this->DFS_recursive(this->vertices.front());

}

void Graph::DFS_recursive(Vertex* current) {
    if (current->color == 0) {
        return;
    }

    current->color = 0;
    cout << current->id <<endl;

    for (auto neighbour : current->neighbours) {

        if (neighbour->color != 0) {
            neighbour->color = 1;
        }
        DFS_recursive(neighbour);

    }

}
