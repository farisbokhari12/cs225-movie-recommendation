#include "dfs.h"
#include <stack>

bool dfs::isBipartite(Graph & g) {
    bipartite_ = true;

    vector<Vertex> v = g.getVertices(); // get all the vertices

    for (Vertex & vert : v) { // "_" = unvisited || "-" = visited || "=" = color1 || "+" = color2
        g.setVertexLabel(vert, "_."); // "." = placeholder for color
    }
    //g.setVertexLabel(v[0], "_=");

    int components = 0;
    int n = 0;
    int m = 0;

    for (Vertex & i : v) { // iterate through all the vertices
        if (g.getVertexLabel(i)[1] == '.') {
            int n1 = 0;
            components++;
            g.setVertexLabel(i,"_=");
            std::stack<Vertex> stack;
            stack.push(i);
            while (!stack.empty()) {
                Vertex vert = stack.top();
                stack.pop();
                if (g.getVertexLabel(vert)[0]=='-') continue;
                n++;
                if (n % 1000 == 0) {
                    std::cout << "\r" << n << "/" << v.size() << std::flush;
                }
                for (Vertex & j : isBipartite(g,vert)) {
                    stack.push(j);
                }
                if (!bipartite_) return false;
                n1++;
            }
            if (n1 > m) {
                m = n1;
            }
        }
    }

    std::cout << "\r" << components << " connected components" << std::endl;
    std::cout << "Largest component had " << (100*m)/v.size() << "% of the elements" << std::endl;
    //std::cout << n << " ?= " << v.size() << std::endl;

    // n should equal v.size()

    return true;
}

/*
* g = graph
* currV = current vertex in main function
*/
std::vector<Vertex> dfs::isBipartite(Graph & g, Vertex currV) {
    //std::cout << currV << std::endl;
    std::string curr = g.setVertexLabel(currV,g.getVertexLabel(currV).replace(0,1,"-")); // set current vertex to visited
    std::vector<Vertex> toAdd;
    for (Vertex & w : g.getAdjacent(currV)) { // for all the adjacent vertices to currV
        std::string label = g.getVertexLabel(w);
        if (label[0] == '_') { // if w is unvisited
            if (curr[1] == '=') { // get color of parent vertex
                g.setVertexLabel(w, "_+"); // set w to unvisited and second color
            } else {
                g.setVertexLabel(w, "_="); // else set w to unvisited and first color
            }
            //isBipartite(g, w);
            toAdd.push_back(w);
        } else if (g.getVertexLabel(w)[1] == g.getVertexLabel(currV)[1]) { // if adjacent vertex is already...
            bipartite_ = false;                                                          // ...visited and they have the same color
            std::cout << "Bad pair " << w << " " << currV << std::endl;
            break;
        }
    }
    return toAdd;
}

/*
    DFS(G):
        Input: Graph, G
        Output: A labeling of the edges on
            G as discovery and back edges
        foreach (Vertex v : G.vertices()):
            setLabel(v, UNEXPLORED)
        foreach (Edge e : G.edges()):
            setLabel(e, UNEXPLORED)
        foreach (Vertex v : G.vertices()):
            if getLabel(v) == UNEXPLORED:
                DFS(G, v)
    DFS(G, v):
        setLabel(v, VISITED)
        foreach (Vertex w : G.adjacent(v)):
            if getLabel(w) == UNEXPLORED:
                setLabel(v, w, DISCOVERY)
                DFS(G, w)
            elseif getLabel(v, w) == UNEXPLORED:
                setLabel(v, w, BACK)
*/

bool dfs::getBipartite() {
    return bipartite_;
}