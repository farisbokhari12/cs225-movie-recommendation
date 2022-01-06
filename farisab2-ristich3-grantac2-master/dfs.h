#pragma once

#include <cmath>
#include <stack>
#include <vector>
#include <algorithm>

#include "graph.h"
#include "edge.h"

using namespace std;

class dfs {
    public:
        /*
        * Use dfs to confirm if the graph is bipartite or not
        */
        bool isBipartite(Graph & g); // main function
        std::vector<Vertex> isBipartite(Graph & g, Vertex v); // helper function
        bool getBipartite(); // idk why i wrote this, but its here lol

    private:
        bool bipartite_;
};