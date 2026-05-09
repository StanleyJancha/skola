//
// Created by ovast on 5/9/2026.
//

#ifndef ALG_PROJEKT_FREETREE_H
#define ALG_PROJEKT_FREETREE_H
#include <cstdio>
#include <fstream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

/**
 *@class FreeTree
 *@brief Třída reprezentující graf, který nemá směr a není cyklický
*/
class FreeTree {
    /** * @brief datová struktura na principu klíč:hodnota, do které ukládáme vertexy (body) a jejich příslušné neighbour (sousední) vertexy
     */
    std::unordered_map<int, std::vector<int>> vertexNeighbours;

private:
    /** * @brief Vrátí počet sousedních prvků vertexu poslaného jao parameter
     */
    size_t getVertexDegree(int vertex) {
        auto vertexFind = vertexNeighbours.find(vertex);
        if (vertexFind == vertexNeighbours.end()) {
            return -1;
        }
        return (*vertexFind).second.size();
    }


    int getMaxDepth(int vertex, set<int>& visitedVertexes) {
        visitedVertexes.insert(vertex);
        int maxSubBranchDepth = 0;

        for (auto neighbourVertex: this->vertexNeighbours[vertex]) {
            if (!visitedVertexes.contains(neighbourVertex)) {

                //printf("Vertex %d neighbour %d\n",vertex,neighbourVertex);
                int currBranchDepth = getMaxDepth(neighbourVertex,visitedVertexes);

                if (currBranchDepth > maxSubBranchDepth) {
                    maxSubBranchDepth = currBranchDepth;
                }
            }
        }
        return maxSubBranchDepth + 1;
    }
public:
    /** * @brief Přidá do stromu nové vertexy podle hrany*/
    void addEdge(int u, int v) {
        vertexNeighbours[u].push_back(v);
        vertexNeighbours[v].push_back(u);
    }
    /** * @brief První pokus vytvoření algoritmu. Funguje, ale komplexita je O(V^2) a najde pouzde jeden optimální kořen, i když jsou tam dva
     *     @returns pair<int,int> - vrací pár dvou číselných hodnot. První značí vertex a druhé maximální hloubku tohoto vertexu*/
    pair<int,int> findRootWithMinimalHeights_legacy(FreeTree *ftree) {
        pair<int,int> vertexWithLowestDepth = {-1,20000}; // <vertex, depth>
        for (auto const& [vertex, neighbours]: ftree->vertex_neighbours()) {
            set<int> visited;

            int currentMaxDepth = ftree->getMaxDepth(vertex, visited);
            if (currentMaxDepth < vertexWithLowestDepth.second) {
                vertexWithLowestDepth = {vertex, currentMaxDepth};
            }
        }
        return vertexWithLowestDepth;
    }
    /** * @brief Algoritmus pro nalezení optimalních kořenů free tree (volného stromu). Využívá se principu postupného odtraňování koncových vertexů.
     *      @returns vector<int> - Množina nejoptimálnějších vertexů v ohledu na nejmenší výšku stromu
             */
    vector<int> findRootsWithMinimalHeights() {
        unordered_map<int,int> vertexesWithDegrees; // pair pro <vertex, kolik ma neighbours>
        vector<int> endVertices;
        int remainingVertices = this->vertex_neighbours().size();

        for (auto const& [vertex, neighbors] : this->vertex_neighbours()) { // prvotni ziskani degree u kazdeho vertexu
            vertexesWithDegrees[vertex] = neighbors.size();
            if (vertexesWithDegrees[vertex] <= 1) { // pokud je vertex koncovy, tak ho pridame do endVertices, aby jsme meli, kde zacit odstrihavani
                endVertices.push_back(vertex);
            }
        }

        while (vertexesWithDegrees.size() > 2) {
            remainingVertices -= endVertices.size(); // odceteme pocet verticies, ktere v tomhle cyklu odstrihneme
            vector<int> newEndVertices;

            for (auto end_vertex: endVertices) {
                auto x = this->vertex_neighbours()[end_vertex];
                for (auto neigbhour: x) {
                    if (vertexesWithDegrees.contains(neigbhour)) {
                        vertexesWithDegrees[neigbhour] -= 1;

                        if (vertexesWithDegrees[neigbhour] <= 1) {
                            newEndVertices.push_back(neigbhour);
                        }
                    }
                }
                vertexesWithDegrees.erase(end_vertex);
            }
            endVertices = newEndVertices;

        }
        return endVertices;
    }
    /** * @brief Getter pro vertexNeighbours
    */
    unordered_map<int, std::vector<int>> vertex_neighbours() const {
        return vertexNeighbours;
    }
    /** * @brief Vypíše všechny vertexy a jejich neighbor vertexy
    */

    void printTree() {
        for (pair<const int, vector<int>> vertex: vertexNeighbours) {
            printf("Vertex: %d\n",vertex.first);
            for (int neigbhourVertex: vertex.second) {
                printf("\t%d\n",neigbhourVertex);
            }
        }
    }
    /** * @brief Ze souboru načte dvojce čísel, které reprezentují hrany. Ty potom vloží do instance, na které se tato metoda zavolá
            @returns bool podle toho, jeslti se podařilo přečíst dataq ze souboru a načíst je
    */
    bool loadEdgesFromFile(string filePath) {

        ifstream  inputFile(filePath);

        if (!inputFile.is_open()) {
            return -1;
        }

        string text;
        while (getline (inputFile, text)) {
            int v1 = stoi(text.substr(0,text.find(' ')));
            int v2 = stoi(text.substr(text.find(' ')));
            this->addEdge(v1,v2);

        }

        inputFile.close();
        return true;
    }


};


#endif //ALG_PROJEKT_FREETREE_H