/**
 * @file edge.h
 * Definition and (minimal) implementation of an edge class.
 */

#pragma once

#include <string>
#include <limits.h>

using std::string;

typedef string Vertex;

/**
 * Represents an edge in a graph; used by the Graph class.
 *
 * @author Sean Massung
 * @date Spring 2012
 */
class Edge
{
  public:
    Vertex source; /**< The source of the edge **/
    Vertex dest; /**< The destination of the edge **/

    /**
     * Parameter constructor for unweighted graphs.
     * @param u - one vertex the edge is connected to
     * @param v - the other vertex it is connected to
     */
    Edge(Vertex u, Vertex v)
        : source(u), dest(v), score(-1), helpfulness(0)
    { /* nothing */
    }

    /**
     * Parameter constructor for weighted graphs.
     * @param u - one vertex the edge is connected to
     * @param v - the other vertex it is connected to
     * @param w - the weight of the edge
     */
    Edge(Vertex u, Vertex v, int s, int h)
        : source(u), dest(v), score(s), helpfulness(h)
    { /* nothing */
    }

    /**
     * Default constructor.
     */
    Edge() : source(""), dest(""), score(-1), helpfulness(0)
    { /* nothing */
    }

    /**
     * Compares two Edges.
     * operator< is defined so Edges can be sorted with std::sort.
     * @param other - the edge to compare with
     * @return whether the current edge is less than the parameter
     */
    bool operator<(const Edge& other) const
    {
        return score < other.score; // is this even necessary
    }

    /**
     * Gets edge score.
     */
    int getScore() const
    {
        return this->score;
    }

    /**
     * Gets edge helpfulness votes
     */
    int getHelpfulness() const
    {
        return this->helpfulness;
    }

    /**
     * Compares two edges' source and dest.
     * @param other - the edge to compare with
     */
    bool operator==(Edge& other) const
    {
        if (this->source != other.source)
            return false;
        if (this->dest != other.dest)
            return false;
        return true;
    }
private:
    int score;
    int helpfulness;

};
