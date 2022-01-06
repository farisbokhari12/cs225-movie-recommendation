#include "../catch/catch.hpp"
#include "../graph.h"
#include "../dijkstra.h"
#include "../dfs.h"
#include <string>
using namespace std;

TEST_CASE("DFS non-bipartite graph test", "[weight=10]")
{
  Graph t;
  t.insertVertex("user1");
  t.insertVertex("user2");
  t.insertVertex("user3");
  t.insertVertex("movie1");
  t.insertVertex("movie2");
  t.insertVertex("movie3");
  t.insertEdge("user1", "movie1");
  t.insertEdge("user2", "movie2");
  t.insertEdge("user3", "movie3");
  t.insertEdge("user1", "movie2");
  t.insertEdge("user1", "user2");
  dfs d;
  bool actual = d.isBipartite(t);
  bool expected = false;
  REQUIRE(expected == actual);
}

TEST_CASE("DFS bipartite graph test", "[weight=10]")
{
  Graph f;
  f.insertVertex("user1");
  f.insertVertex("user2");
  f.insertVertex("user3");
  f.insertVertex("movie1");
  f.insertVertex("movie2");
  f.insertVertex("movie3");
  f.insertEdge("user1", "movie1");
  f.insertEdge("user2", "movie2");
  f.insertEdge("user3", "movie3");
  f.insertEdge("user1", "user2");
  dfs r;
  bool actual = r.isBipartite(f);
  bool expected = true;
  REQUIRE(expected == actual);
}

TEST_CASE("Dijkstra Small Test", "[weight=10]")
{
  Graph g;
  Vertex e = "user1";
  Vertex a = "user2";
  Vertex b = "movie00001";
  Vertex c = "movie00002";

  g.insertVertex(e);

  g.insertVertex(a);
  // g->insertVertex("user3");
  // g->insertVertex("user4");
  g.insertVertex(b);
  g.insertVertex(c);
  // g->insertVertex("movie3");
  // g->insertVertex("movie4");
  g.insertEdge(e, b);

  g.insertEdge(e, c);
  g.insertEdge(a, c);
  g.setEdgeValues(e, b, 4, 2);
  g.setEdgeValues(e, c, 5, 5);
  g.setEdgeValues(a, c, 1, 2);
	vector<Vertex> recs;
  dijkstra d;
  vector<Vertex> v = d.findRecommended(g, "movie00001");
  recs.push_back(c);
  REQUIRE(recs[0] == v[0]);
}
TEST_CASE("Dijkstra Large Test", "[Weight=10]") {
  Graph g;
  g.insertVertex("user1");
  g.insertVertex("user2");
  g.insertVertex("user3");
  g.insertVertex("user4");
  g.insertVertex("user5");
  g.insertVertex("movie00001");
  g.insertVertex("movie00002");
  g.insertVertex("movie00003");
  g.insertVertex("movie00004");
  g.insertVertex("movie00005");
  g.insertEdge("user1", "movie00001");
  g.insertEdge("user1", "movie00002");
  g.insertEdge("user2", "movie00002");
  g.insertEdge("user2", "movie00003");
  g.insertEdge("user3", "movie00003");
  g.insertEdge("user3", "movie00004");
  g.insertEdge("user4", "movie00004");
  g.insertEdge("user4", "movie00005");
  g.insertEdge("user5", "movie00005");
  g.setEdgeValues("user1", "movie00001", 4, 5);
  g.setEdgeValues("user1", "movie00002", 3, 7);
  g.setEdgeValues("user2", "movie00002", 4, 2);
  g.setEdgeValues("user2", "movie00003", 5, 1);
  g.setEdgeValues("user3", "movie00003", 2, 1);
  g.setEdgeValues("user3", "movie00004", 2, 0);
  g.setEdgeValues("user4", "movie00004", 1, 10);
  g.setEdgeValues("user4", "movie00005", 2, 5);
  g.setEdgeValues("user5", "movie00005", 2, 0);
	vector<Vertex> recs;
  dijkstra d;
  vector<Vertex> v = d.findRecommended(g, "movie00001");
  recs.push_back("movie00003");
  recs.push_back("movie00002");
  
  REQUIRE(recs == v);
}