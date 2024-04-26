#include <gtest/gtest.h>
#include <sstream>
#include "dijkstra.cpp"
using namespace std;

TEST(Dijkstra, Test0v4) {

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
    vector<int> result = G.dijkstra_algorythm(0, 4).first;
    vector<int> expected = vector<int>({0, 2, 1, 4});
    for (int i = 0; i < result.size(); ++i) {
        ASSERT_EQ(result[i], expected[i]);
    };
}

TEST(Dijkstra, Test2v4) {

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
    vector<int> result = G.dijkstra_algorythm(2, 4).first;
    vector<int> expected = vector<int>({2, 1, 4});
    for (int i = 0; i < result.size(); ++i) {
        ASSERT_EQ(result[i], expected[i]);
    };
}

TEST(Dijkstra, Test2v3) {

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
    vector<int> result = G.dijkstra_algorythm(2, 3).first;
    vector<int> expected = vector<int>({2, 1, 3});
    for (int i = 0; i < result.size(); ++i) {
        ASSERT_EQ(result[i], expected[i]);
    };
}

TEST(Dijkstra, Test0v3) {

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
    vector<int> result = G.dijkstra_algorythm(0, 3).first;
    vector<int> expected = vector<int>({0, 2, 1, 3});
    for (int i = 0; i < result.size(); ++i) {
        ASSERT_EQ(result[i], expected[i]);
    };
}

TEST(Dijkstra, length_test_0v1) {
    
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
        int result = G.dijkstra_algorythm(0, 1).second;
        int expected = 3;
        ASSERT_EQ(result, expected);
}

TEST(Dijkstra, length_test_0v4) {
    
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
        int result = G.dijkstra_algorythm(0, 4).second;
        int expected = 5;
        ASSERT_EQ(result, expected);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
};