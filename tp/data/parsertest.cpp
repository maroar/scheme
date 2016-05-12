#include "data.h"
#define DEBUG false
#define TEST_FILENAME "test.txt"

int main()
{
	Parser ps;
	Graph * G;
	G = ps.parse_graph(TEST_FILENAME);
}