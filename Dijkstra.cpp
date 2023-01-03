#include "Dijkstra.hpp"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

Dijkstra::Dijkstra(string fname) {
	readFile(fname);
	Interface();
    	runDijkstra();
    	printPath();
}

void Dijkstra::runDijkstra(){
	empty = true;
	for (int i = 0; i < numOfCities; i++){
		distances[i] = infinity;
		prev[i] = start;
	}
	prev[start] = -1;
	distances[start] = 0;
	visited[start] = true;
	for (int i = 0; i < numOfCities; i++){
		distances[i] = matrixGraph[start][i];
	}
	printInfoSoFar();
	for (int i = 0; i < numOfCities; i++){
		if (visited[i] == false) empty = false;
	}
	while (!empty){
		int u = minDistance();
		visited[u] = true;
		setDistances(u);
		if (distances[u] == infinity) {
			break;
		}
		for (int v = 0; v < numOfCities; v++){
			int alt = distances[u] + matrixGraph[u][v] + 1;
			if (alt < distances[v]){
				distances[v] = alt;
				prev[v] = u;
				--distances[v];
			}
		}
		printInfoSoFar();
		empty = true;
		for (int i = 0; i < numOfCities; i++){
			if (visited[i] == false) empty = false;
		}
	}

}

void Dijkstra::setDistances(int latestVert) {
	int *tmp = new int[numOfCities];
	tmp = distances;
	distances = matrixGraph[latestVert];
	int min = minDistance();
	distances = tmp;

	for (int i = 0; i < numOfCities; i++){
		int alt = distances[i] + matrixGraph[i][min] + 1;
		if (alt < distances[min]){
			distances[min] = alt - 1;
			prev[min] = latestVert;
		}
	}
}

int Dijkstra::minDistance( ) {
	int min = infinity, index = 0;
	for (int v = 0; v < numOfCities; v++){
		if (visited[v] == false && distances[v] <= min && distances[v] != infinity){
			min = distances[v]; index = v;
		}
	}
	return index;
}



void Dijkstra::printPath() {
	int *out = new int[numOfCities];
	int index = end, size = 0;
	while(prev[index] != -1){
		out[size] = index;
		index = prev[index];
		size++;
	}
	out[size] = start;
	for (int i = size; i >= 0; i--){
		if (i == 0) cout << Cities[out[i]] << endl;
		else cout << Cities[out[i]] << "->";
	}
}

// A utility function to print the constructed distance array
void Dijkstra::printMatrix() {
	cout <<"********************************************" << endl << "Adjacency Matrix (of Cities and Distances):"<<endl;
	for (int i = 0; i< numOfCities;i++) {
		for (int j = 0; j < numOfCities; j++) {
			cout << matrixGraph[i][j] << "\t";
		}
		cout << endl;
	}
	cout <<"********************************************" << endl;
}

//Another utility method to print out the different arrays so far
void Dijkstra::printInfoSoFar() {
	cout <<"\t";
	for (int i = 0; i < numOfCities; i++) {
		cout << "\t"<<i;
	}
	cout << endl;
	cout << "Dist:\t";
	for (int i = 0; i < numOfCities; i++) {
		cout << "\t"<<distances[i];
	}
	cout << endl;
	cout << "Prev:\t";
	for (int i = 0; i < numOfCities; i++) {
		cout << "\t"<<prev[i];
	}
	cout << endl;
	cout << "Visited:";
	for (int i = 0; i < numOfCities; i++) {
		cout << "\t"<<visited[i];
	}
	cout << endl;
	cout << endl;
}





/*************************************************************/
/* This is the user interface that allows you to choose your 
/* start and end city you're traveling through.
/*************************************************************/
void Dijkstra::Interface() {
	cout << "Choose from the following: "<<endl;
	for (int i = 0; i < numOfCities; i++) {
		cout << "\t" << i << ": " << Cities[i] << endl;
	}
	cout << endl;
	cout << "Choose your starting city (with the city's corresponding number"<<endl;
	cin >> start;
	cout << "Choose your end destination (with the city's corresponding number"<< endl;
	cin >> end;
}

/*************************************************************/
/* This method reads in the different Map files and initializes 
/* all your arrays along with the adjacency matrix.  It
/* initializes the following:
/*
/* numOfCities: the number of cities in the adjacency matrix
/*
/* Cities: an array filled with the list of cities - the index in 
/* the array is the number corresponding with each city (which 
/* can be utilized when printing out the path
/* 
/* visited: set to false for all cities (indices) to start
/*
/* prev: set to -1 (aka no previous city) for each index to start
/*
/* distance: set to a really large number for all indices to 
/* start
/*
/* matrixGraph: adjacency matrix that holds the 
/* distance from each city to each city.  It is initialized in 
/* here with values read in from the different Map***.txt files
/*
/*************************************************************/
void Dijkstra::readFile(string fn) {
	ifstream file(fn.c_str());
	int numcities;
	file>>numcities;
	numOfCities = numcities;
	Cities = new string[numOfCities];
	visited = new bool[numOfCities];
	prev = new int[numOfCities];
	distances = new int[numOfCities];
	matrixGraph = new int*[numOfCities];
	for (int i = 0; i < numOfCities; i++) {
		matrixGraph[i] = new int[numOfCities];
        distances[i] = 100000;
    	visited[i] = false;
    	prev[i] = -1;
	}
	string abbr;
	string city;
	string abbrCity;
	for (int i = 0; i < numOfCities; i++) {
		file >> abbr;
		file >> city;
		abbrCity = abbr + " "+city;
		Cities[i] = abbrCity;
	}
	for (int ct = 0; ct < numOfCities; ct++)  {
		file >> abbr;
		file>>city;
		for (int i = 0; i < numOfCities; i++) {
			int x;
			file >> x;
			if (x == -1) {
				matrixGraph[ct][i] = 100000;
			}
			else matrixGraph[ct][i] = x;
		}
	}
    printMatrix();
	return;
}







