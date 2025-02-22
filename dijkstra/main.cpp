#include <iostream>
#include "dijkstra.cpp"
using namespace std;

int main() {
    int** gp = new int*[5];
    for (int i = 0; i < 5; ++i) {
        gp[i] = new int[5];
    }

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            gp[i][j] = 0;
        }
    }

    gp[0][1] = 4; gp[1][0] = 4;
    gp[0][2] = 2; gp[2][0] = 2;
    gp[2][1] = 1; gp[1][2] = 1;
    gp[1][3] = 1; gp[3][1] = 1;
    gp[1][4] = 2; gp[4][1] = 2;
    gp[3][4] = 5; gp[4][3] = 5;

    Graph G(gp, 5);

    vector<int> res = G.dijkstra_algorythm(0, 4).first;

    cout << "Shortest path from 0 to 4: ";
    for (int i = 0; i < res.size(); ++i) {
        cout << res[i] << " ";
    };
    cout << "\b, with path length: " << G.dijkstra_algorythm(0, 4).second << "\n\n";
}