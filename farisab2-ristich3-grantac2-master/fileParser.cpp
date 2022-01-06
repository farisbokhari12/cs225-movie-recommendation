#include "fileParser.h"
#include "dijkstra.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <string>

Graph * parse_file(const std::string &file) {
    Graph* graph = new Graph();
    std::ifstream text(file);
    text.seekg(0,std::ios_base::end);
    auto n = text.tellg()/1000000;
    text.seekg(0);
    if (!text.is_open()) {
        std::cout << "File couldn't open!" << std::endl;
        return NULL;
    }
    int i = 0;
    while (!text.eof()) {
        parse_review(text,graph);
        i++;
        if (i == 1000) {
            i = 0;
            std::cout << "\r" << text.tellg()/1000000 << "/" << n << " MB" << std::flush;
        }
    }
    std::cout << "\rFinished reading text" << std::endl;
    text.close();
    return graph;
}

void parse_review(std::istream & text, Graph * graph) {
    std::string product;
    std::string user;
    int helpful;
    int votes;
    int score;
    std::string line;
    std::string firstword;
    int r = 0;
    while (std::getline(text,line) && line.length()) {
        r++;
        std::istringstream iss(line);
        iss >> firstword;
        if (firstword == "product/productId:") {
            iss >> product;
        } else if (firstword == "review/userId:") {
            iss >> user;
        } else if (firstword == "review/helpfulness:") {
            iss >> firstword; // uh
            sscanf(firstword.c_str(),"%d/%d",&helpful,&votes);
        } else if (firstword == "review/score:") {
            iss >> firstword;
            sscanf(firstword.c_str(),"%d.0",&score);
        }
    }
    if (r < 4) return;
    if (!graph->vertexExists(product)) graph->insertVertex(product);
    if (!graph->vertexExists(user)) graph->insertVertex(user);
    graph->insertEdge(user,product);
    //double rating = (double)score/10;
    //double helpfulscore = (double) helpful*2-votes + rating;
    graph->setEdgeValues(user,product,score,helpful*2-votes);
}