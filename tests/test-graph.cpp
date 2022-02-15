#include "../DataReader.h"
#include "../Graph.h"
#include "catch.hpp"

#include <iostream>
#include <string>
#include <vector>

Graph g_default = Graph();
Graph g_int = Graph(5);
Graph g_file = Graph("tests/small_graph.txt");

TEST_CASE("Graph::bfsTraversal all nodes default constructor #1", "[part=2][valgrind]") {

    vector<DataObject> bfs = g_default.bfsTraversal(0);

    REQUIRE(bfs.size() == 4999);
}

TEST_CASE("Graph::bfsTraversal all nodes default constructor #2", "[part=2][valgrind]") {

    vector<DataObject> bfs = g_default.bfsTraversal("Terraforming Mars");

    REQUIRE(bfs.size() == 4999);
}

TEST_CASE("Graph::bfsTraversal int #1", "[part=2][valgrind]") {

    vector<DataObject> bfs = g_int.bfsTraversal(0);

    REQUIRE(bfs.size() == 5);
    REQUIRE(bfs[0].rank == 1);
    REQUIRE(bfs[1].rank == 2);
    REQUIRE(bfs[2].rank == 4);
    REQUIRE(bfs[3].rank == 5);
    REQUIRE(bfs[4].rank == 3);
}

TEST_CASE("Graph::bfsTraversal int #2", "[part=2][valgrind]") {

    vector<DataObject> bfs = g_int.bfsTraversal("Terraforming Mars");

    REQUIRE(bfs.size() == 5);
    REQUIRE(bfs[0].rank == 4);
    REQUIRE(bfs[1].rank == 1);
    REQUIRE(bfs[2].rank == 2);
    REQUIRE(bfs[3].rank == 3);
    REQUIRE(bfs[4].rank == 5);
}

TEST_CASE("Graph::bfsTraversal file #1", "[part=2][valgrind]") {

    vector<DataObject> bfs = g_file.bfsTraversal(0);

    REQUIRE(bfs.size() == 8);
    REQUIRE(bfs[0].rank == 1);
    REQUIRE(bfs[1].rank == 2);
    REQUIRE(bfs[2].rank == 4);
    REQUIRE(bfs[3].rank == 3);
    REQUIRE(bfs[4].rank == 6);
    REQUIRE(bfs[5].rank == 5);
    REQUIRE(bfs[6].rank == 7);
    REQUIRE(bfs[7].rank == 8);
}

TEST_CASE("Graph::bfsTraversal file #2", "[part=2][valgrind]") {

    vector<DataObject> bfs = g_file.bfsTraversal("Terraforming Mars");

    REQUIRE(bfs.size() == 8);
    REQUIRE(bfs[0].rank == 4);
    REQUIRE(bfs[1].rank == 1);
    REQUIRE(bfs[2].rank == 6);
    REQUIRE(bfs[3].rank == 2);
    REQUIRE(bfs[4].rank == 3);
    REQUIRE(bfs[5].rank == 5);
    REQUIRE(bfs[6].rank == 7);
    REQUIRE(bfs[7].rank == 8);
}

TEST_CASE("Graph::getEdge int", "[part=2][valgrind]") {

    REQUIRE(g_int.getEdge(1, 4) == 0.25);
    REQUIRE(g_int.getEdge(1, 3) == 0.125);
    REQUIRE(g_int.getEdge(2, 4) == 0);
}

TEST_CASE("Graph::getEdge file", "[part=2][valgrind]") {

    REQUIRE(g_file.getEdge(0, 1) == 21);
    REQUIRE(g_file.getEdge(1, 3) == 0);
    REQUIRE(g_file.getEdge(2, 4) == 63);
    REQUIRE(g_file.getEdge(8, 9) == -1);
}

TEST_CASE("Graph::degreeCentrality int", "[part=2][valgrind]") {

    vector<DataObject> degCent = g_int.degreeCentrality();

    REQUIRE(degCent[4].rank == 3);
}

TEST_CASE("Graph::degreeCentrality file", "[part=2][valgrind]") {

    vector<DataObject> degCent = g_file.degreeCentrality();

    REQUIRE(degCent[2].rank == 3);
    REQUIRE(degCent[3].rank == 2);
}

TEST_CASE("Graph::eigenvectorCentrality file", "[part=2][valgrind]") {

    vector<double> eigen = g_file.eigenVector(20);
    
    REQUIRE(eigen.size() == 8);
    REQUIRE((abs(eigen[0] - 0.0000124808)/0.0000124808) < 0.05);
    REQUIRE((abs(eigen[1] - 0.000135821)/0.000135821) < 0.05);
    REQUIRE((abs(eigen[2] - 0.00813067)/0.00813067) < 0.05);
    REQUIRE((abs(eigen[3] - 0.000268997)/0.000268997) < 0.05);
    REQUIRE((abs(eigen[4] - 0.471023)/0.471023) < 0.05);
    REQUIRE((abs(eigen[5] - 0.01276)/0.01276) < 0.05);
    REQUIRE((abs(eigen[6] - 0.00997096)/0.00997096) < 0.05);
    REQUIRE((abs(eigen[7] - 0.497698)/0.497698) < 0.05);
}

TEST_CASE("Graph::dijkstrasShortestPath int #1", "[part=2][valgrind]") {

    vector<DataObject> shortPath = g_int.dijkstrasShortestPath(2, 3);

    REQUIRE(shortPath.size() == 2);
    REQUIRE(shortPath[0].rank == 3);
    REQUIRE(shortPath[1].rank == 4);
}

vector<DataObject> shortPathInt = g_int.dijkstrasShortestPath(3, 4);

TEST_CASE("Graph::dijkstrasShortestPath int #2", "[part=2][valgrind]") {

    REQUIRE(shortPathInt.size() == 3);
    REQUIRE(shortPathInt[0].rank == 4);
    REQUIRE(shortPathInt[1].rank == 2);
    REQUIRE(shortPathInt[2].rank == 5);
}

TEST_CASE("Graph::dijkstrasShortestPath file #1", "[part=2][valgrind]") {

    vector<DataObject> shortPath = g_file.dijkstrasShortestPath(0, 1);

    REQUIRE(shortPath.size() == 2);
    REQUIRE(shortPath[0].rank == 1);
    REQUIRE(shortPath[1].rank == 2);
}

vector<DataObject> shortPathFile = g_file.dijkstrasShortestPath(1, 6);

TEST_CASE("Graph::dijkstrasShortestPath file #2", "[part=2][valgrind]") {

    REQUIRE(shortPathFile.size() == 4);
    REQUIRE(shortPathFile[0].rank == 2);
    REQUIRE(shortPathFile[1].rank == 3);
    REQUIRE(shortPathFile[2].rank == 6);
    REQUIRE(shortPathFile[3].rank == 7);
}

TEST_CASE("Graph::getPathLength int", "[part=2][valgrind]") {

    REQUIRE(g_int.getPathLength(shortPathInt) == 0.375);
}

TEST_CASE("Graph::getPathLength file", "[part=2][valgrind]") {

    REQUIRE(g_file.getPathLength(shortPathFile) == 167);
}