#pragma once

#include <cmath>
#include <stack>
#include <vector>
#include <algorithm>

#include "graph.h"
#include "edge.h"


class dijkstra {
    public:

    vector<Vertex> findRecommended(const Graph & g, const Vertex movieID);
    /*
    * The plan for the constructor is to input a graph (that's already made) and a product ID (provided by the user)
    * Find the shortest path between a movie and review given by a reviewer that has a rating of higher than 4 and a helpfulness of higher than 20
    * Find another edge from that reviewer to a movie that has a rating and helpfulness of similar values.
    * 
    * 
    */
    
};