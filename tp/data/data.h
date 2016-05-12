/*
File: data.h

This file contains the definitions for the module Data, which parses a file to
our Graph structure.
*/
#ifndef DATA_H
#define DATA_H
#include "../graph/graph.h"
#include <string>
#include <iostream>
#include <fstream>

class Parser
{
public:
	Parser();
	~Parser();
	
	Graph * parse_graph(std::string filename);
	void test_parser(std::string filename);
};


#endif