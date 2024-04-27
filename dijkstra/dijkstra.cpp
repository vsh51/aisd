#include <vector>
#include <set>
#include <iostream>
#include <algorithm>

using std::vector;
using std::set;
using std::pair;
using std::reverse;
using std::cout;

class Graph {
public:
    struct edge {
        int from;
        int to;
        int df = 0;
        int weight;

        edge(int from = 0, int to = 0, int weight = 0) : from(from), to(to), weight(weight) {};
    };

private:
    vector<vector<edge>> G;
    int** adjacency_matrix;
    int n;

public:
    Graph(int** adjacency_list, int vertices) {
        this->n = vertices;

        G.resize(vertices);

        adjacency_matrix = new int*[vertices];
        for (int i = 0; i < vertices; ++i) {
            adjacency_matrix[i] = new int[vertices];
            for (int j = 0; j < vertices; ++j) {
                adjacency_matrix[i][j] = adjacency_list[i][j];
                if (adjacency_list[i][j] != 0) {
                    G[i].push_back(edge(i, j, adjacency_list[i][j]));
                }
            }
        }
    }

    pair<vector<int>, int> dijkstra_algorythm(int v1, int v2) {
        if (v1 < this->n && v2 < this->n) {            
            vector<int> distance(n, __INT32_MAX__);
            set<pair<int, int>> unset_vert;

            distance[v1] = 0;

            for (int i = 0; i < n; ++i) {
                unset_vert.insert({distance[i], i});
            };

            vector<int> way;
            vector<int> previous(n, -1);

            while (!unset_vert.empty()) {
                int v = unset_vert.begin()->second;
                unset_vert.erase(unset_vert.begin());

                for (vector<edge>::iterator e = G[v].begin(); e != G[v].end(); ++e) {
                    if (distance[e->to] > distance[v] + e->weight) {
                        unset_vert.erase({distance[e->to], e->to});
                        distance[e->to] = distance[v] + e->weight;
                        previous[e->to] = v;
                        unset_vert.insert({distance[e->to], e->to});
                    }
                }
            }

            if (previous[v2] == -1) {
                throw "No path";
            } else {
                int current = v2;
                while (current != -1) {
                    way.push_back(current);
                    current = previous[current];
                }

                reverse(way.begin(), way.end());
                
                return pair(way, distance[v2]);
            }
        }
        else {
            throw "Vertex out of range";
        }
    }
};