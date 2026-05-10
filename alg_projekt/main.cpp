#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>

#include "FreeTree.h"

using namespace std;


int main() {

    string testFolderPath = "../testy";

    vector<string> testFilesPaths;

    for (const auto& entry : filesystem::directory_iterator(testFolderPath)) {
        if (entry.exists() && !entry.is_directory()) {
            testFilesPaths.push_back(entry.path().string());
        }
    }

    for (auto test_file_path: testFilesPaths) {
        FreeTree ftree;

        if (!ftree.loadEdgesFromFile(test_file_path)) {
            printf("Error when loading from file\n");
            return -1;
        };

        printf("Tree source %s\n",test_file_path.c_str());
        ftree.printTree();

        // Soluction num 1. Complexity O(V^2) V - nubmer of vericies
        // pair<int,int> vertexWithLowestDepth = ftree.findRootWithMinimalHeights_legacy(&ftree);
        //
        // printf("Vertex with lowest depth is %d, it's depth is %d\n",vertexWithLowestDepth.first, vertexWithLowestDepth.second);

        // Solution 2
        vector<int> optimalRoots = ftree.findRootsWithMinimalHeights();
        cout << "Optimal root" << ( (optimalRoots.size() == 1)? " is:":"s are:") << endl;
        for (auto optimal_root: optimalRoots) {
            printf("%d\n",optimal_root);
        }
    }


    return 0;
}
