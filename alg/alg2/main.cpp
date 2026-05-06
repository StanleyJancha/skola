#include <iostream>
#include <vector>

#include "Graph.h"
#include "BSTree.h"

using namespace std;

void insertionSort(int* pole, int N) {
    for (int i = 0; i < N; ++i) {
        int out = pole[i];
        int j = i-1;
        while (j >= 0 && pole[j] > out) {
          pole[j + 1] = pole[j];
            j--;
        };
        pole[j + 1] = out;
    }
}

bool binarySearchIter(int* pole, int N, int value) {

    int l = 0;
    int r = N - 1;

    while (r >= l) {
        int M = (l + r)/2;

        if (value == pole[M]) {
            return true;
        }

        if (value < pole[M]) {
            r = M - 1;
        }
        if (value > pole[M]) {
            l = M + 1;
        }
    }

}

bool binarySearchRec(int* pole, int l, int r, int value) {
    if (r < l) {
        return false;
    }

    int M = (l + r)/2;

    if (value == pole[M]) {
        return true;
    }

    if (value < pole[M]) {
        return binarySearchRec(pole,l,M-1,value);
    }
    if (value > pole[M]) {
        return binarySearchRec(pole,M+1,r,value);
    }
    return false;
}

int partition(int *pole, int l, int r) {
    int pivot = pole[r];
    int last = l;

    for (int i = 0; i < r; ++i) {
        if (pole[i] < pivot) {
            swap(pole[i],pole[last]);
            last++;
        }
    }
    swap(pole[last],pole[r]);
    return last;
}

void quickSort(int * pole , int l, int r) {
    if (r <= l) {
        return;
    }

    int pivotIndex = partition(pole,l,r);

    quickSort(pole,l, pivotIndex - 1);
    quickSort(pole, pivotIndex + 1,r);
}




int main() {

    Graph graph;

    graph.insert(1);


    vector<int> neighbours;

    neighbours.push_back(1);

    graph.insert(2,neighbours);

    neighbours.push_back(2);


    graph.insert(3,neighbours);

    neighbours.clear();

    neighbours.push_back(3);
    graph.insert(4,neighbours);
    graph.insert(5,neighbours);

    graph.insert(6);
    graph.insert(7);

    neighbours.push_back(6);
    neighbours.push_back(7);

    graph.insert(8,neighbours);

    neighbours.clear();
    neighbours.push_back(2);
    neighbours.push_back(8);

    graph.insert(9,neighbours);

    neighbours.clear();
    neighbours.push_back(9);

    graph.insert(10,neighbours);

    graph.DFS_recursive();



    BSTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(1);
    tree.insert(7);
    tree.insert(15);
    tree.insert(25);
    tree.insert(12);


    return 0;
}