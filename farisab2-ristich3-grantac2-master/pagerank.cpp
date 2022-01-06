#include "pagerank.h"
#include <vector>
#include <unordered_map>
#include <cmath>
#include <chrono>
#include <random>
#include <functional>

std::unordered_map<Vertex,double> pagerank(Graph & g, std::vector<Vertex> & given_map, double damping, double bias) {
    // damping is now probability to stop walk
    // bias is probability to jump to a given
    // this algorithm is basically Algorithm 4 from https://doi.org/10.1137/050643799
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::unordered_map<Vertex,double> ranks_map; // final map to return
    std::vector<Vertex> vertices = g.getVertices(); // list of vertices
    std::unordered_map<Vertex,size_t> rmap; // reverse map from vertex to index
    std::vector<size_t> given; // list of indexes of given vertexes
    size_t N = vertices.size(); // number of vertices
    for (size_t i = 0; i < N; i++) { // generate rmap
        rmap[vertices[i]] = i;
    }
    for (Vertex & i : given_map) { // verify and build given
        if (!g.vertexExists(i)) {
            std::cout << "Vertex " << i << " does not exist" << std::endl;
        } else {
            given.push_back(rmap[i]);
        }
    }
    std::vector<size_t> ranks(N,0); // pageranks, multiplied by some number (to be determined)
    std::vector<std::vector<size_t>> nxt(N,std::vector<size_t>()); // new adjacency list using indexes

    std::cout << "Generating adjacency lists" << std::endl;


    // generates adjacency lists in the obvious way
    for (size_t i = 0; i < N; i++) {
        if (i%1000 == 0) std::cout << "\r" << i << "/" << N << std::flush; // progress indicator
        Vertex u = vertices[i];
        for (Vertex & v : g.getAdjacent(u)) {
            Edge e = g.getEdge(u,v);
            size_t j = rmap[v];
            if ( g.isMovie(u) ) {
                if (e.getHelpfulness() >= 0) nxt[i].push_back(j);
            } else {
                if (e.getScore() >= 4) nxt[i].push_back(j);
            }
        }
    }

    std::cout << "\rCalculating pageranks" << std::endl;

    int M = 10; // number of iterations (since we only care about the highest rated movies, we don't need this to be too high)
    int numVisited = 0; // number of nodes visited (at least N*M but probably more)

    auto rand = std::bind(std::uniform_real_distribution<double>(0,1),generator); // function to generate random number between 0 and 1

    // generates N*M runs, starting from each vertex M times
    for (size_t i = 0; i < N; i++) {
        if (i%1000 == 0) std::cout << "\r" << i << "/" << N << std::flush;
        for (int _ = 0; _ < M; _++) {
            // do a random walk
            size_t v = i;
            do { // we definitely want to visit the node at least once
                numVisited++;
                ranks[v]++;
                auto nx = nxt[v];
                if (nx.size() == 0) break; // if the node doesn't lead anywhere, the walk ends
                if (rand() < bias) { // jump to a random given node
                    v = given[std::uniform_int_distribution<size_t>(0,given.size()-1)(generator)];
                } else { // jump to a random node according to the adjacency list
                    v = nx[std::uniform_int_distribution<size_t>(0,nx.size()-1)(generator)];
                }
            } while (rand() < damping); // there is probability 1-damping the walk ends
        }
    }

    std::cout << "\rRecommendations:                      " << std::endl;

    double visited = numVisited; // otherwise I would have to cast it in line, which I don't need to do multiple times

    for (size_t i = 0; i < N; i++) {
        ranks_map[vertices[i]] = ranks[i]/visited; // stores the actual pageranks in ranks_map
    }

    return ranks_map;
}

void printRecommendations(Graph & g, std::vector<Vertex> & given, int n) {
    std::unordered_map<Vertex, double> ranks = pagerank(g, given, 0.95, 0.3);
    std::vector<Vertex> vertices = g.getVertices();
    std::sort(vertices.begin(),vertices.end(),
        [&](Vertex const &a, Vertex const &b) {
            return ranks[a] > ranks[b];
        }); // sort vertices by rank
    // print n recommendations
    int count = 0;
    for (Vertex & v : vertices) {
        if (std::find(given.begin(),given.end(),v) == given.end() && g.isMovie(v)) {
            count++;
            std::cout << "https://amazon.com/dp/" << v << "/ " << ranks[v] << std::endl;
        }
        if (count == n) return;
    }
}