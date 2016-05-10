/*
File: data.cpp

This module parses a text file into a Graph structure used in this project.
*/

#include "data.h"

Parser::Parser(){}
Parser::~Parser(){}

Graph * Parser::parse_graph(std::string filename)
{
  std::ifstream fs;
  fs.open(filename);
  int n, m, v1, v2, w;
  fs >> n >> m;
  std::cout <<"Nodes: " << n << " Edges: " << m << std::endl;
	Graph * G = new Graph(n, m);
	for (int i = 0; i < m; i++)
	{
		fs >> v1 >> v2 >> w;
		#ifdef DEBUG
			std::cout<< (v1--) << " " << (v2--) << " " << w << std::endl;
		#endif
		G->add_edge(v1, v2, w);
	}

	return G;
}

void Parser::test_parser(std::string filename)
{
	Graph * G = Parser::parse_graph(filename);
	G->print();
}

int main()
{
	Parser ps;
	ps.test_parser(TEST_FILENAME);
}