#include <random>
#include <ctime>
#include <stdio.h>
#include <list>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#define FILEOUT "test.txt"
#define SIZE 10
#define DENSITY 4
#define MAXWEIGHT 500
//This macro is used to generate edges from A to B and from B to A, instead of
//only edges from A to B. Set true if you want the graph to be directed.
#define EDGES(d_) (d_ ? 1 : (i+1))
#define DIRECTED false

void genGraph(std::string filename, int size, int density);

int main(int argc, char** argv)
{
  int size, density;
  std::string fileout;
  if (argc < 4)
  {
    std::cout<< "Default parameters used.\n"
    << "Usage: <FILEOUT> <NUM_NODES> <DENSITY>\n"
    << "<FILEOUT> : Name/dir of the output file\n"
    << "<NUM_NODES> : Number of nodes\n"
    << "<DENSITY> : Density is a number from 0 to 4 that defines the density of"
    << "the graph. Usually 0 -> low density, 4 -> high density.\n\n";
    size = SIZE;
    density = DENSITY;
    fileout = FILEOUT;
  }
  else
  {
    fileout = argv[1];
    size = std::atoi(argv[2]);
    density = std::atoi(argv[3]);
  }

  genGraph(fileout, size, density);

  return 0;
}

void genGraph(std::string filename, int size, int density)
{
  int weight, m=0;
  double p = density*0.25;
  double prob;
  std::srand(std::time(0));
  std::ofstream of;
  of.open(filename);
  //Set the macro DIRECTED if you want the graph to be directed, so there will be
  //edges from J to I as well. If not, J will start from I.
  for (int i = 0; i<size; i++)
    for (int j = EDGES(DIRECTED); j < size; j++)
    {
      prob = ((double) std::rand() / (RAND_MAX));
      if (p >= prob || i == 0) //Guarantees a connected graph
      {
        m++;
        weight = (std::rand()%MAXWEIGHT);
        of  << i+1 << " "
            << j+1 << " "
            << weight
            << std::endl;
      }
    }

    of.seekp(0);
    of << size << " " << m << std::endl;


    return;
}