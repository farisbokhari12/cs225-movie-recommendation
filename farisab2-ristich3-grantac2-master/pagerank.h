#include "graph.h"
#include <vector>

/**
 * Calculates pageranks...
 * actual ranks sum to number of vertices
 */
std::unordered_map<Vertex,double> pagerank(Graph & g, std::vector<Vertex> & given, double damping, double bias);

void printRecommendations(Graph & g, std::vector<Vertex> & given, int n);

/*

Case 1: occurs with probability d
  Basically at a movie you have equal probability to move to users of positive helpfulness
  at a user you have equal probability to move to movies rated 3 or higher
  if in either case nothing satisfies, then there is an equal probability to go to any vertex

Case 2: occurs with probability b*(1-d)
  Jump to one of the given vertices with equal probability

Case 3: occurs with probability (1-b)*(1-d)
  Jump to a random vertex with equal probabilitys

*/