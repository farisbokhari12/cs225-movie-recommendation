#include "graph.h"

const Vertex Graph::InvalidVertex = "_CS225INVALIDVERTEX";
const int Graph::InvalidWeight = INT_MIN;
const Edge Graph::InvalidEdge = Edge(Graph::InvalidVertex, Graph::InvalidVertex, Graph::InvalidWeight, Graph::InvalidWeight);

Graph::Graph()
{
}

vector<Vertex> Graph::getAdjacent(Vertex source) const 
{
    auto lookup = adjacency_list.find(source);

    if(lookup == adjacency_list.end())
        return vector<Vertex>();

    else
    {
        vector<Vertex> vertex_list;
        unordered_map <Vertex, Edge> & map = adjacency_list[source];
        for (auto it = map.begin(); it != map.end(); it++)
        {
            vertex_list.push_back(it->first);
        }
        return vertex_list;
    }
}


Vertex Graph::getStartingVertex() const
{
    return adjacency_list.begin()->first;
}

vector<Vertex> Graph::getVertices() const
{
    vector<Vertex> ret;

    for(auto it = adjacency_list.begin(); it != adjacency_list.end(); it++)
    {
        ret.push_back(it->first);
    }

    return ret;
}

Edge Graph::getEdge(Vertex source , Vertex destination) const
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return Edge();
    Edge ret = adjacency_list[source][destination];
    return ret;
}

vector<Edge> Graph::getEdges() const
{
    if (adjacency_list.empty())
        return vector<Edge>();

    vector<Edge> ret;
    set<pair<Vertex, Vertex>> seen;

    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); it++)
    {
        Vertex source = it->first;
        for (auto its = adjacency_list[source].begin(); its != adjacency_list[source].end(); its++)
        {
            Vertex destination = its->first;
            if(seen.find(make_pair(source, destination)) == seen.end())
            {
                //this pair is never added to seen
                ret.push_back(its->second);
                seen.insert(make_pair(source,destination));
                seen.insert(make_pair(destination, source));
            }
        }
    }

    return ret;
}

bool Graph::vertexExists(Vertex v) const
{
    return assertVertexExists(v, "");
}

bool Graph::edgeExists(Vertex source, Vertex destination) const
{
    return assertEdgeExists(source, destination, "");
}

double Graph::getEdgeScore(Vertex source, Vertex destination) const
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidWeight;
    return adjacency_list[source][destination].getScore();
}

double Graph::getEdgeHelpfulness(Vertex source, Vertex destination) const
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidWeight;
    return adjacency_list[source][destination].getHelpfulness();
}

void Graph::insertVertex(Vertex v)
{
    // will overwrite if old stuff was there
    removeVertex(v);
    // make it empty again
    adjacency_list[v] = unordered_map<Vertex, Edge>();
    vertexLabels[v] = "";
}


Vertex Graph::removeVertex(Vertex v)
{

    if (adjacency_list.find(v) != adjacency_list.end())
    {
        for (auto it = adjacency_list[v].begin(); it != adjacency_list[v].end(); it++)
        {
            Vertex u = it->first;
            adjacency_list[u].erase(v); 
        }
        adjacency_list.erase(v);
        vertexLabels.erase(v);
        return v;
        
        adjacency_list.erase(v);
        vertexLabels.erase(v);
        for(auto it2 = adjacency_list.begin(); it2 != adjacency_list.end(); it2++)
        {
            Vertex u = it2->first;
            if (it2->second.find(v)!=it2->second.end())
            {
                it2->second.erase(v);
            }
        }
        return v;
    }

    return InvalidVertex;
}

bool Graph::insertEdge(Vertex source, Vertex destination)
{
    if(adjacency_list.find(source)!= adjacency_list.end() 
    && adjacency_list[source].find(destination)!= adjacency_list[source].end())
    {
        //edge already exists
        return false;
    }

    if(adjacency_list.find(source)==adjacency_list.end())
    {
        adjacency_list[source] = unordered_map<Vertex, Edge>();
    }
        //source vertex exists
    adjacency_list[source][destination] = Edge(source, destination);

    if(adjacency_list.find(destination)== adjacency_list.end())
    {
        adjacency_list[destination] = unordered_map<Vertex, Edge>();
    }
    adjacency_list[destination][source] = Edge(source, destination);
    
    return true;
}

Edge Graph::removeEdge(Vertex source, Vertex destination)
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    adjacency_list[source].erase(destination);
    // if undirected, remove the corresponding edge
    adjacency_list[destination].erase(source);
    return e;
}

Edge Graph::setEdgeValues(Vertex source, Vertex destination, int score, int helpfulness)
{
    if (assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    // std::cout << "setting weight: " << weight << std::endl;
    Edge new_edge(source, destination, score, helpfulness);
    adjacency_list[source][destination] = new_edge;

    Edge new_edge_reverse(destination,source, score, helpfulness);
    adjacency_list[destination][source] = new_edge_reverse;

    return new_edge;
}

string Graph::setVertexLabel(Vertex v, string label) {
    if (adjacency_list.find(v) != adjacency_list.end())
    {
        vertexLabels[v] = label;
        return label;
    }
    return InvalidVertex;
}

string Graph::getVertexLabel(Vertex v) {
    if (adjacency_list.find(v) != adjacency_list.end())
    {
        if (vertexLabels.find(v) != vertexLabels.end())
            return vertexLabels[v];
    }
    return InvalidVertex;
}

bool Graph::assertVertexExists(Vertex v, string functionName) const
{
    if (adjacency_list.find(v) == adjacency_list.end())
    {
        if (functionName != "")
            error(functionName + " called on nonexistent vertices");
        return false;
    }
    return true;
}

bool Graph::assertEdgeExists(Vertex source, Vertex destination, string functionName) const
{
    if(assertVertexExists(source,functionName) == false)
        return false;
    if(adjacency_list[source].find(destination)== adjacency_list[source].end())
    {
        if (functionName != "")
            error(functionName + " called on nonexistent edge " + source + " -> " + destination);
        return false;
    }

    if (assertVertexExists(destination,functionName) == false)
        return false;
    if(adjacency_list[destination].find(source)== adjacency_list[destination].end())
    {
        if (functionName != "")
            error(functionName + " called on nonexistent edge " + destination + " -> " + source);
        return false;
    }
    return true;
}

void Graph::clear()
{
    adjacency_list.clear();
}

bool Graph::isMovie(Vertex v) const {
    return v.length()==10;
}

/**
 * Prints a graph error and quits the program.
 * The program is exited with a segfault to provide a stack trace.
 * @param message - the error message that is printed
 */
void Graph::error(string message) const
{
    cerr << "\033[1;31m[Graph Error]\033[0m " + message << endl;
}

/**
 * Prints the graph to stdout.
 */
void Graph::print() const
{
    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); ++it) 
    {
        cout << it->first << vertexLabels.find(it->first)->second << endl;
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) 
        {
            std::stringstream ss;
            ss << it2->first; 
            string vertexColumn = "    => " + ss.str();
            vertexColumn += " " ;
            cout << std::left << std::setw(26) << vertexColumn;
            cout << "score = " << it2->second.getScore();
            cout << " " << it2->second.getHelpfulness();
            cout << "/" << it2->second.getScore();
            cout << endl;
        }
        cout << endl;
    }
}

void Graph::printVertexLabels() const {
    // for (auto it = vertexLabels.begin(); it != vertexLabels.end(); ++it) {
    //     cout << it->first;
    //         std::stringstream ss;
    //         ss << it->first; 
    //         string vertexColumn = "    => " + ss.str();
    //         vertexColumn += " " ;
    //         cout << std::left << std::setw(26) << vertexColumn;
    //         cout << "score = " << it2->second.getScore();
    //         cout << " " << it2->second.getHelpfulness();
    //         cout << "/" << it2->second.getScore();
    //     cout << endl;
    // }
}