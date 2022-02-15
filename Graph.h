#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cmath>
#include <set>
#include <queue>

#include "DataReader.h"

using namespace std;

class Graph{

    public:

        /** 
         * Constructs graph from base dataset
         * Uses all the nodes by default
         */ 
        Graph();


        /** 
         * Constructs graph from base dataset
         * Uses n nodes
         * 
         * @param n number of nodes to create
         */ 
        Graph(int n);

        /** 
         * Creates a graph by loading it from the file specified
         * 
         * @param filename name of the file to load
         */
        Graph(string filename); 

        /** 
         * saves the graph to specified file
         * 
         * @param filename the name of the file to save to
         */
        void saveGraph(string filename);

        /** 
         * prints the adjacency matrix to console, mostly a method for debugging
         */
        void printMatrix();


        /**
         * performs a breadth-first traversal on the graph given a starting node
         * 
         * @param i the index of the starting node of the traversal
         * 
         * @return a vector containing the indices of elements of the graph in the order of the traversal
         */ 
        vector<DataObject> bfsTraversal(int i);

        /**
         * performs a breadth-first traversal on the graph given a starting node given by name
         * 
         * @param n the name of the starting node of the traversal
         * 
         * @return a vector containing the indices of elements of the graph in the order of the traversal
         */ 
        vector<DataObject> bfsTraversal(string n);

        /**
         * Uses Dijkstra's algorithm to compute the shortest path between any start and end node given
         * 
         * @param start the index of the start node
         * 
         * @param end the index of the end node
         * 
         * @return vector<DataObject> a vector of DataObjects in the order of the shortest path
         */
        vector<DataObject> dijkstrasShortestPath(int start, int end);

        /**
         * Uses Dijkstra's algorithm to compute the shortest path between any start and end node given
         * 
         * @param start the name of the start node
         * 
         * @param end the name of the end node
         * 
         * @return vector<DataObject> a vector of DataObjects in the order of the shortest path
         */
        vector<DataObject> dijkstrasShortestPath(string start, string end);


        /**
         * returns the edge weight between two vertices (0 means no edge)
         * 
         * @param v1 the first vertex
         * 
         * @param v2 the second vertex
         * 
         * @return the weight between these two vertices (0 for no edge between them)
         */
        double getEdge(int v1, int v2);


        /**
         * prints the adjacent vertices of any given vertex
         * 
         * @param i the vertex to print the neighbors of
         */
        void printAdjVertices(int i);

        /**
         * prints the nearest neighbor to a certain vertex
         * 
         * @param i the neighbor to print the nearest neighbor of
         */
        void printNearestVertex(int i);

        /** 
         * Determines the degree centrality of any node
         * 
         * @param i the node to calculate the degree centrality of
         * 
         * @return the degree of this vertex
         */ 
        double degreeCentrality(int i);

        /** 
         * Ranks all the DataObjects by order of their degree centrality and returns the vector
         * 
         * @return a vector of all the games in the graph, ranked by degree centrality
         */ 
        vector<DataObject> degreeCentrality();

        /** 
         * finds the dominant eigenvector of the adjacency matrix of the graph, which can be
         * ranked to find the eigenvector centrality
         * 
         * @param num_iters the number of iterations of eigenvector computation to do
         * 
         * @return the dominant eigenvector of the graph
         */ 
        vector<double> eigenVector(int num_iters);

        /** 
         * Ranks all the DataObjects by order of their eigenvector centrality and returns the vector
         * 
         * @return a vector of all the games in the graph, ranked by eigenvector centrality
         */ 
        vector<DataObject> eigenvectorCentrality();


        /**
         * Returns the length of a path given by a vector of vertices
         * 
         * @param vertices the path of vertices to calculate the length of, assumes that the path is valid
         *  
         * @return the length of the path generated
         */
        double getPathLength(vector<DataObject> vertices);

    private:

        /** 
         * counts number of strings in both lists
         * 
         * @param first the first vector of strings
         * @param second the second vector of strings 
         * 
         * @return the number of overlaps
         */ 
        int numOverlaps(vector<string> first, vector<string> second);

        /** 
         * generates a list of all the vertices adjacent to the one specified
         * 
         * @param i the index of the vertex to find the vertices adjacent to
         * 
         * @return a vector of indices of vertices that this is adjacent to
         */
        vector<int> getAdjacentVertices(int i);

        DataReader data; // stored to reference games

        vector<vector<double>> adjMatrix;
};