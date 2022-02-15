#include "Graph.h"

int main( int argc, char** argv ){

    if(argc > 4 || argc == 2){
        cout << "Invalid input" << endl;
    }

    if(argc == 1){
        cout << "PROJECT DEMO" << endl;
    }

    if(argc != 1){

        if(argc == 3){
            string g1(argv[1]);
            string g2(argv[2]);
            Graph g;
            vector<DataObject> dijk = g.dijkstrasShortestPath(g1, g2);
            if(dijk.size() == 0) return 0;
            cout << "Shortest path between " << g1 << " and " << g2 << endl;
            cout << "(";
            for(unsigned i = 0; i < dijk.size(); i++){
                if(i!=dijk.size()-1)
                cout<< dijk[i].name << ", ";
                else
                cout<< dijk[i].name << ")" << endl;
            }

        }else if(argc == 4){
            int n = atoi(argv[1]);
            string g1(argv[2]);
            string g2(argv[3]);
            Graph g(n);
            vector<DataObject> dijk = g.dijkstrasShortestPath(g1, g2);
            if(dijk.size() == 0) return 0;
            cout << "Shortest path between " << g1 << " and " << g2 << endl;
            cout << "(";
            for(unsigned i = 0; i < dijk.size(); i++){
                if(i!=dijk.size()-1)
                cout<< dijk[i].name << ", ";
                else
                cout<< dijk[i].name << ")" << endl;
            }
        }else{
            cout << "Invalid input" << endl;
        }

        return 0;
    }

    ifstream infile;
    infile.open("graph_5000.txt");
    bool fullGraphExists = false;
    if(infile){
        fullGraphExists = true;
    }
    infile.close();

    cout << "Loading graph of full dataset (4999 elemenets)" << endl;

    Graph g = fullGraphExists ? Graph("graph_5000.txt") : Graph();

    DataReader dataReader("data/bgg_db_1806.csv");

    if(!fullGraphExists){
        cout << "Saving graph (in case you run this demo again, loading will be sped up (may take up to a minute)" << endl;
        g.saveGraph("graph_5000.txt");
        cout << "Graph saved" << endl;
    }

    cout << "----------------------------------------------" << endl;
    cout << "Perform a BFS starting at game Terra Mystica" << endl;

    std::vector<DataObject> bfs = g.bfsTraversal("Terra Mystica");

    cout << "BFS complete, printing first 20 elements of traversal" << endl;

    for(int i = 0; i < 20; i++){
        std::cout << bfs[i].name << std::endl;
    }

    cout << "Size of BFS was " << bfs.size() << ", which is all of the elements" << endl;

    cout << "----------------------------------------------" << endl;
    cout << "Perform some shortest path searches" << endl;
    
    vector<DataObject> dijk = g.dijkstrasShortestPath(213, 392);
    cout << "Shortest path between " << dataReader[213].name << " and " << dataReader[392].name << endl;
    cout << "(";
    for(unsigned i = 0; i < dijk.size(); i++){
        if(i!=dijk.size()-1)
        cout<< dijk[i].name << ", ";
        else
        cout<< dijk[i].name << ")" << endl;
    }
    cout << endl;

    dijk = g.dijkstrasShortestPath(1274, 3192);
    cout << "Shortest path between " << dataReader[1274].name << " and " << dataReader[3192].name << endl;
    cout << "(";
    for(unsigned i = 0; i < dijk.size(); i++){
        if(i!=dijk.size()-1)
        cout<< dijk[i].name << ", ";
        else
        cout<< dijk[i].name << ")" << endl;
    }
    cout << endl;

    dijk = g.dijkstrasShortestPath("Kanagawa", "Loopin' Chewie");
    cout << "Shortest path between " << "Kanagawa" << " and " << "Loopin' Chewie" << endl;
    cout << "(";
    for(unsigned i = 0; i < dijk.size(); i++){
        if(i!=dijk.size()-1)
        cout<< dijk[i].name << ", ";
        else
        cout<< dijk[i].name << ")" << endl;
    }
    cout << endl;

    dijk = g.dijkstrasShortestPath("Anachrony", "Commands & Colors: Ancients");
    cout << "Shortest path between " << "Anachrony" << " and " << "Commands & Colors: Ancients" << endl;
    cout << "(";
    for(unsigned i = 0; i < dijk.size(); i++){
        if(i!=dijk.size()-1)
        cout<< dijk[i].name << ", ";
        else
        cout<< dijk[i].name << ")" << endl;
    }
    cout << endl;

    //all hail the seventh continent....

    cout << "----------------------------------------------" << endl;
    cout << "Perform degree centrality ranking" << endl;
    vector<DataObject> dc = g.degreeCentrality();
    
    for(int i = 0; (size_t)i < 20; i++){
        cout << "#" << i+1 << ": " << dc[i].name << endl;
    }

    cout << "----------------------------------------------" << endl;
    cout << "Perform eigenvector centrality ranking" << endl;
    vector<DataObject> ec = g.eigenvectorCentrality();
    
    for(int i = 0; (size_t)i < 20; i++){
        cout << "#" << i+1 << ": " << ec[i].name << endl;
    }

    return 0;
}