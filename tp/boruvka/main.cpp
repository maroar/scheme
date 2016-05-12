#include <string>
#include "boruvka.h"
#include "../data/data.h"
#include "../graph/graph.h"
#define TEST_FILENAME "same_weight.txt"

int main(int argc, char ** argv)
{
	std::string filename = TEST_FILENAME;
	if (argc > 1)
	{
		filename = argv[1];
	}
	Graph * G;
	Parser ps;
	G = ps.parse_graph(filename);
	G->sort_edges();
	//G->print();

	Boruvka bo;
	bo.getMST(G);	
}