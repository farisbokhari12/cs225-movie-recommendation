#include <iostream>
#include <vector>
#include "fileParser.h"
#include "dijkstra.h"
#include "dfs.h"
#include "pagerank.h"

int main(int argc, const char *argv[])
{
	if (argc == 1)
	{
		std::cout << "Please enter a file name" << std::endl;
		return 0;
	}
	std::cout << "Filename: " << argv[1] << std::endl;
	std::string pr_or_dijk;
	Graph *g = parse_file(argv[1]);

	if (g == NULL)
		return 0;
	
	dfs d;
	std::cout << "Checking that graph is bipartite..." << std::endl;
	if (d.isBipartite(*g))
	{
		std::cout << "\rGraph is bipartite                  " << std::endl << std::endl;
		std::cout << "CS225 Movie Recommender" << std::endl;
		std::cout << "=======================" << std::endl;
		std::cout << "Please select which algorithm you would like to run: [PR or DIJK]" << std::endl;
		std::cin >> pr_or_dijk;
		if (pr_or_dijk == "PR")
		{
			std::string v;
			std::string yn;
			bool is_entered = false;
			std::vector<Vertex> base;
			int count = 0;
			while (!is_entered)
			{
				std::cout << "Please enter product ID" << std::endl;
				std::cin >> v;
				base.push_back(v);
				if (count >= 1)
				{
					std::cout << "Have you entered all your liked movies? [Y or N]" << std::endl;
					std::cin >> yn;
					if (yn == "Y")
					{
						is_entered = true;
					}
					else if (yn == "N")
					{
						continue;
					}
				}
				count++;
			}
			printRecommendations(*g, base, 10);
		}
		else if (pr_or_dijk == "DIJK")
		{
			std::string v;
			std::cout << "Please enter product ID" << std::endl;
			std::cin >> v;
			dijkstra d;
			d.findRecommended(*g, v);
		}
	}
	else
	{
		std::cout << "\rGraph is not bipartite, Please enter proper dataset" << std::endl;
	}

	delete g;
	return 0;
}