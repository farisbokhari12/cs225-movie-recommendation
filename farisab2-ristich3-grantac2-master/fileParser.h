#pragma once

#include <string>
#include <iostream>
#include "graph.h"
#include "dijkstra.h"

Graph * parse_file(const std::string &file);

void parse_review(std::istream & text, Graph * graph);