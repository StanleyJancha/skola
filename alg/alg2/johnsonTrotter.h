//
// Created by standa on 4/30/26.
//

#ifndef ALG2_JOHNSONTROTTER_H
#define ALG2_JOHNSONTROTTER_H
#include <iostream>
#include <vector>

using namespace std;

class johnsonTrotter {

private:
    enum {LEFT,RIGHT};
    class ArrowedInt {
        bool dir = LEFT;
        int value;

        ArrowedInt(int value) {
            this->value = value;
        }
    };

protected:
    vector<ArrowedInt*> arr;
    int N;
public:
    johnsonTrotter(int N) {
        this->N = N;
    }

    void print() {
        for (ArrowedInt * arroewdInt: arr) {
            cout << arroewdInt.valie << "\t";
        }
    }

    bool isMobile(int pos) {
        if (pos == 0 && arr[pos]->dir == LEFT) {
            return false;
        }
        if (pos == N - 1 && arr[pos]->dir == RIGHT) {
            return false;
        }
        if (arr[pos]->dir == LEFT && arr[pos -1]->value < arr[pos]->value)
            return true;
        if (arr[pos]->dir == RIGHT && arr[pos +1]->value < arr[pos]->value)
            return true;

        return false;
    }

    ArrowedInt* getHighestMobile(int & pos) {
        int maxIndex = -1;

        for (int i = 0; i < arr.size(); ++i) {
            if (isMobile(i) && (maxIndex == -1 || arr[i]->value < arr[maxIndex]->value)) {
                maxIndex = i;
            }
        }
        pos = maxIndex;
        if (maxIndex == -1) {
            return nullptr;
        }
        return arr[maxIndex];
    }

    void swapWithNeighbour(int pos) {
        swap(arr[pos],arr[pos]->dir ? arr[pos + 1]: arr[pos -1]);
    }
    void toggleArrows(ArrowedInt* k) {
        for (auto arrowdInt : arr) {
            if (arrowdInt->value > k->value) {
                arrowdInt->dir = !arrowdInt->dir;
            }
        }
    }

    void run() {
        for (int i = 0; i <= N; ++i) {
            arr.push_back(new ArrowedInt(i));
        }
        int pos = -1;
        ArrowedInt* k = getHighestMobile(pos);

        while (k != nullptr) {
            swapWithNeighbour(pos);
            toggleArrows(k);

            printf();

            k = getHighestMobile();
        }
    }
};


#endif //ALG2_JOHNSONTROTTER_H