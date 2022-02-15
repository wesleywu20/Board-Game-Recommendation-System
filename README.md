# Board Game Recommendation System
Final project for CS225 Fall 2021 by aspal2, iansong2, wwu70, and ipendem2.
## Description
This final project takes a data set of board games to create algorithm-generated recommendations for games to play based upon which ones are most similar to the board games that the user inputs. It uses parameters such as number of players, average play time, and mechanics to determine which board games are similar, and creates a graph with board games as vertices and weighted edges based upon their calculated similarity.

## Installing
1. Clone and pull the repo
```
git clone https://github-dev.cs.illinois.edu/cs225-fa21/aspal2-iansong2-wwu70-ipendem2.git
git pull
```
2. You're good to go!
## Running the tests
```
make test
./test
```
Running tests for the Data Reader:
```
./test [part=1]
```
And if you would like to check for memory leaks in the Data Reader tests:
```
valgrind ./test [part=1]
```
Running tests for the Graph:
* Graph Base Functions
* BFS
* Dijkstra's Shortest Path Algorithm
* Eigenvector Centrality Algorithm
```
./test [part=2]
```
And if you would like to check for memory leaks in the Graph tests:
```
valgrind ./test [part=2]
```
## Running the program
1. Running the Demo Program

Running main without any arguments will run a demo program showcasing all of the functionality of the project.
```
make
./main
```
2. Running Dijkstra's Shortest Path Algorithm

This version of main will take 2 arguments, each one being a name of a board game. (***IMPORTANT:*** Do not put spaces in between words of board game titles. Ex: "Arkham Horror" -> "ArkhamHorror")
```
make
./main [name of boardgame 1] [name of boardgame 2]
```
3. Running Dijkstra's Shortest Path Algorithm with a certain size subset of the data

This version of main will take 3 arguments, the first one is assumed to be an integer representing what size of the graph the algorithm should be ran over, the next two arguments being the names of the board games. (***IMPORTANT:*** Do not put spaces in between words of board game titles. Ex: "Arkham Horror" -> "ArkhamHorror")
```
make
./main [# size of data] [name of boardgame 1] [name of boardgame 2]
```
## Included Files:
DataReader.h

DataReader.cpp

Graph.h

Graph.cpp

main.cpp

graph.txt - output of full graph adjacency matrix

data/bgg_db_1806.csv - data set for boardgames taken from https://www.kaggle.com/mrpantherson/board-game-data?select=bgg_db_1806.csv

tests/catch.hpp

tests/catchmain.cpp

tests/small_graph.txt - small adjacency matrix used for testing algorithms

tests/test-datareader.cpp - data reader tests

tests/test-graph.cpp - graph tests

## Acknowledgements
https://www.kaggle.com/mrpantherson/board-game-data?select=bgg_db_1806.csv

https://courses.engr.illinois.edu/cs225/fa2021/
