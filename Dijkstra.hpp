#ifndef DIJKSTRA_HPP_
#define DIJKSTRA_HPP_

#include <iostream>
#include <stdlib.h>
#include <limits.h>
using namespace std;


class Dijkstra {
	int **matrixGraph;  //the adjacency graph matrix
	int numOfCities;  // total number of cities, read in from 
	// the map file and given a value in readFile()
	int start;  //this is the start city, typed in when
	//the Interface method is run
	int end;  // this is the end city, typed in when the 
	//Interface method is run
	string *Cities;  // the array of cities
	bool *visited;  //an array of cities - set to true if the
	// city has been visited, originally all set to false
	int *distances;  // the distance needed to get to each city 
	// from the start city so far
	int *prev;  // an array - for each city, it is set to the
	// best previous city for the shortest path
	int infinity = 100000;
	bool empty;
public:
	Dijkstra(string fname);  // constructor with map file name
	void runDijkstra();  // starts the program 
	void Interface();  
	void setDistances(int lv);  // calculates the current shortest distance
	int minDistance();  // finds the next minimumdistance
	void printMatrix();  // prints matrix
	void printInfoSoFar();  // prints each of the arrays 
	// (visited, prev, and distance)
	void printPath();  // prints the shortest path when found -
	void readFile(string s);  // reads in the Map files and 
	// initializes all the array fields and the numOfCities 
	// field.
};



#endif /* DIJKSTRA_HPP_ */
