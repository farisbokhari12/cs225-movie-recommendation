#include "dijkstra.h"
#include <queue>
#include <map>
#include <chrono>
#include <random>
#include <algorithm>
/**
 * 
 * @param g_ Reference to graph of dataset
 * @param movieID string of movie id passed by user
 * 
 * 
 **/ 
vector<Vertex> dijkstra::findRecommended(const Graph & g_, const Vertex movieID) {
    std::unordered_map<Vertex, int> distance;
    vector<Vertex> recs;
    if (!g_.vertexExists(movieID)) {
        std::cerr<<"Movie does not exist in dataset"<<std::endl;
    }
    //Assign initial distances of all vertices to max int (infinity)
    for(Vertex& v : g_.getVertices()) {
        distance[v] = INT_MAX;
    }
    //assign source vertex distance to 0
    distance[movieID] = 0;
    std::priority_queue<std::pair<double, Vertex>> q;
    q.push(std::make_pair(distance[movieID], movieID));
    //Loop until all vertices are visited
    while(!q.empty()) {
        Vertex u = q.top().second;

        //std::cout << "\r\x1b[2K" << q.size() << " " << u << std::flush;
        q.pop();
        //visit adjacent verteces
        for (Vertex v : g_.getAdjacent(u)) {
            int score = g_.getEdgeScore(u, v);
            int helpfulness = g_.getEdgeHelpfulness(u, v);
            int adj_weight = 1;//3-score/2;
            //Check edge score and helpfulness to give recommendation
            if (score >= 3 && helpfulness >= 0 && distance[v] > distance[u] + adj_weight) {
                distance[v] = distance[u] + adj_weight;
                q.push(std::make_pair(distance[v], v));
            }
        }
    }
    //std::cout << "\r\x1b[2K" << std::flush;
    std::multimap<int, Vertex> orderedVals;
    for (Vertex& v : g_.getVertices()) {
        if (g_.isMovie(v) && distance[v] != INT_MAX && distance[v] != 0) {
            orderedVals.emplace(distance[v], v);
        }
    }
    //store recommendations
    std::cout << "Recommendations: " << std::endl;
    auto it = orderedVals.begin();
    while (recs.size() != 0 && recs.size() < 5 && it != orderedVals.end()) {
        auto next = orderedVals.equal_range(it->first).second;
        for (; it != next; it++) {
            recs.push_back(it->second);
        }
    }
    //print recommendations out
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(recs.begin(),recs.end(),std::default_random_engine(seed));
    int count = 0;
    for (Vertex & r : recs) {
        std::cout << r << std::endl;
        count++;
        if (count == 5) break;
    }
    if (recs.size() == 0) {
        std::cout << "Dataset doesn't have enough reviews for recommendations for this movie." << std::endl;
    }
    return recs;
}