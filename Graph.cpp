#include "Graph.h"

/** 
 * Constructs graph from base dataset
 * Uses all the nodes by default
 */ 
Graph::Graph(){
    data = DataReader("data/bgg_db_1806.csv");

    int n = data.size();
    adjMatrix = vector<vector<double>>(n,(vector<double>(n,0))); // initialize matrix to be all 0s, disconnected

    int progBarWidth = 50;
    
    for(int i = 0; i < n; i++){

        cout << "[";
        double prog = (i+0.0)/n;

        int progPos = prog * progBarWidth;

        for(int k = 0; k < progBarWidth; k++){
            if(k <= progPos) cout << "*";
            else cout << " ";
        }
        cout << "]" << (int)(prog * 100) << " %" << "\r";
        cout.flush();

        for(int j = i+1; j < n; j++){
            double weight = 0;

            // do the weight

            DataObject elem1 = data[i];
            DataObject elem2 = data[j];

            int overlap = numOverlaps(elem1.categories, elem2.categories) + numOverlaps(elem1.mechanics, elem2.mechanics);

            if(overlap == 0){
                adjMatrix[i][j] = 0;
                adjMatrix[j][i] = 0;
                continue;
            }

            int timeDiff = abs(elem1.avg_time - elem2.avg_time); 

            weight = (1 /(overlap* pow(2,timeDiff/60.0)));

            adjMatrix[i][j] = weight;
            adjMatrix[j][i] = weight;
        }
    }
    cout << "[**************************************************]100 %" << endl;
}


/** 
 * Constructs graph from base dataset
 * Uses n nodes
 * 
 * @param n number of nodes to create
 */ 
Graph::Graph(int n){
    data = DataReader("data/bgg_db_1806.csv", n);
    adjMatrix = vector<vector<double>>(n,(vector<double>(n,0))); // initialize matrix to be all 0s, disconnected
    
    int progBarWidth = 50;

    for(int i = 0; i < n; i++){

        cout << "[";
        double prog = (i+0.0)/n;

        int progPos = prog * progBarWidth;

        for(int k = 0; k < progBarWidth; k++){
            if(k <= progPos) cout << "*";
            else cout << " ";
        }
        cout << "]" << (int)(prog * 100) << " %" << "\r";
        cout.flush();

        for(int j = i+1; j < n; j++){
            double weight = 0;

            // do the weight

            DataObject elem1 = data[i];
            DataObject elem2 = data[j];

            int overlap = numOverlaps(elem1.categories, elem2.categories) + numOverlaps(elem1.mechanics, elem2.mechanics);

            if(overlap == 0){
                adjMatrix[i][j] = 0;
                adjMatrix[j][i] = 0;
                continue;
            }

            int timeDiff = abs( elem1.avg_time - elem2.avg_time); 

            weight = (1 /(overlap* pow(2,timeDiff/60.0)));

            adjMatrix[i][j] = weight;
            adjMatrix[j][i] = weight;
        }
    }
    cout << "[**************************************************]100 %" << endl;
}

/** 
 * Creates a graph by loading it from the file specified
 * 
 * @param filename name of the file to load
 */
Graph::Graph(string filename){
    
    ifstream file(filename);

    string line;

    if(!file.is_open()){
        file.close(); return;
    }

    getline(file, line);

    int n = stoi(line);

    data = DataReader("data/bgg_db_1806.csv", n);
    adjMatrix = vector<vector<double>>(n,(vector<double>(n,0))); // initialize matrix to be all 0s, disconnected

    int progBarWidth = 50;

    int i = 0;
    while(getline(file, line)){

        cout << "[";
        double prog = (i+0.0)/n;

        int progPos = prog * progBarWidth;

        for(int k = 0; k < progBarWidth; k++){
            if(k <= progPos) cout << "*";
            else cout << " ";
        }
        cout << "]" << (int) (prog * 100) << " %" << "\r";
        cout.flush();

        stringstream ss(line);
        int j = 0;
        string dat;
        
        while(getline(ss, dat, ' ') && j < n){
            double val = stod(dat);
            adjMatrix[i][j] = val;
            adjMatrix[j][i] = val;
            j++;
        }
        i++;
    }
    cout << "[**************************************************]100 %" << endl;

    file.close();
}

/** 
 * saves the graph to specified file
 * 
 * @param filename the name of the file to save to
 */
void Graph::saveGraph(string filename){
    
    ofstream outputfile(filename);
    outputfile << data.size() << endl;
    for(size_t i = 0; i < adjMatrix.size(); i++){
        for(size_t j = 0; j < adjMatrix[i].size(); j++){
            outputfile << adjMatrix[i][j];
            if(j!=adjMatrix[i].size()-1){
                outputfile << " ";
            }
        }
        if(i!=adjMatrix.size()-1){
            outputfile << endl;
        }
    }
    outputfile.close();

}

/** 
 * prints the adjacency matrix to console, mostly a method for debugging
 */
void Graph::printMatrix(){
    for(size_t i = 0; i < adjMatrix.size(); i++){
        for(size_t j = 0; j < adjMatrix[i].size(); j++){
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

/** 
 * generates a list of all the vertices adjacent to the one specified
 * 
 * @param i the index of the vertex to find the vertices adjacent to
 * 
 * @return a vector of indices of vertices that this is adjacent to
 */
vector<int> Graph::getAdjacentVertices(int i){
    vector<int> result;

    for(int j = 0; j < (int) adjMatrix[i].size(); j++){
        if(adjMatrix[i][j]!=0){
            result.push_back(j);
        }
    }


    return result;
}

/**
 * performs a breadth-first traversal on the graph given a starting node
 * 
 * @param i the index of the starting node of the traversal
 * 
 * @return a vector containing the indices of elements of the graph in the order of the traversal
 */ 
vector<DataObject> Graph::bfsTraversal(int i){
    vector<DataObject> result;

    set<int> visited;

    queue<int> tovisit;

    tovisit.push(i);

    visited.insert(i);
    while(!tovisit.empty()){
        int curr = tovisit.front(); 
        tovisit.pop();
        result.push_back(data[curr]);
        vector<int> neighbors = getAdjacentVertices(curr);
        for(unsigned j = 0; j < neighbors.size(); j++){
            if(visited.find(neighbors[j])==visited.end()){
                tovisit.push(neighbors[j]);
                visited.insert(neighbors[j]);
            }
        }
    }

    return result;
}

/**
 * performs a breadth-first traversal on the graph given a starting node given by name
 * 
 * @param n the name of the starting node of the traversal
 * 
 * @return a vector containing the indices of elements of the graph in the order of the traversal
 */ 
vector<DataObject> Graph::bfsTraversal(string n){
    int i = data.getObjectIndex(n);
    return bfsTraversal(i);
}

/**
 * helper struct to turn priority queue of pairs to a minheap by the second value of the pair
 */
struct comparison {
    template<typename T, typename U>
    bool operator()(T const & lhs, U const & rhs) const{
        return(lhs.second>=rhs.second);
    }
};

/**
 * helper function for debugging, prints the contents of a priority queue
 * 
 * @param q 
 */
void printpq(priority_queue<pair<int,double>, vector<pair<int,double>>, comparison> q){
    while(!q.empty()){
        pair<int,double> t = q.top();
        q.pop();
        cout<< "(" << t.first << " , " << t.second << ") ";
    }
    cout << endl;
}

/**
 * Uses Dijkstra's algorithm to compute the shortest path between any start and end node given
 * 
 * @param start the index of the start node
 * 
 * @param end the index of the end node
 * 
 * @return vector<DataObject> a vector of DataObjects in the order of the shortest path
 */
vector<DataObject> Graph::dijkstrasShortestPath(int start, int end){
    vector<DataObject> result;
    vector<double> distances;
    vector<int> previous;
    priority_queue<pair<int,double>, vector<pair<int,double>>, comparison> queue; //first is node, second is iterative distance
    vector<bool> visited;
    for(unsigned i = 0; i < adjMatrix.size(); i++){
        //initialize the vectors
        if((int)i == start){
            distances.push_back(0);
        }else{
            distances.push_back(INFINITY);
        }
        visited.push_back(false);
        previous.push_back(-1);
    }
    //cout << "vectors were initalized ";
    queue.push(pair<int,double>(start, 0));
    //cout << start  << endl;
    while(!queue.empty() && queue.top().first != end){
        pair<int,double> current = queue.top();
        //printpq(queue);
        queue.pop();
        int curNode = current.first;
        if(!visited[curNode]){
            for(unsigned n = 0; n < adjMatrix[curNode].size(); n++){
                if(adjMatrix[curNode][n]!=0 && !visited[n]){ //distance from node to itself is 0
                    double distanceFromCur = adjMatrix[curNode][n] + distances[curNode];
                    if(distanceFromCur < distances[n]){
                        distances[n] = distanceFromCur;
                        previous[n] = curNode;
                        queue.push(pair<int,double>(n, distances[n]));
                    }
                }
            }
            visited[curNode] = true;
        }
    }
    if(queue.empty()){
        cout << "unable to find path" << endl;
        return result;
    }
    while(end!=start){
        result.insert(result.begin(), data[end]);
        end = previous[end];
    }
    result.insert(result.begin(), data[start]);

    return result;
}

/**
 * Uses Dijkstra's algorithm to compute the shortest path between any start and end node given
 * 
 * @param start the name of the start node
 * 
 * @param end the name of the end node
 * 
 * @return vector<DataObject> a vector of DataObjects in the order of the shortest path
 */
vector<DataObject> Graph::dijkstrasShortestPath(string start, string end){

    int g1 = data.getObjectIndex(start);
    int g2 = data.getObjectIndex(end);

    if(g1 == -1 || g2 == -1){
        cout << "One or more game names invalid" << endl;
        vector<DataObject> result;
        return result;
    }

    return dijkstrasShortestPath(g1, g2);

}

/**
 * Returns the length of a path given by a vector of vertices
 * 
 * @param vertices the path of vertices to calculate the length of, assumes that the path is valid
 *  
 * @return the length of the path generated
 */
double Graph::getPathLength(vector<DataObject> vertices){
    double result = 0;
    for(size_t i = 0; i < vertices.size()-1; i++){
        int v1 = vertices[i].rank-1;
        int v2 = vertices[i+1].rank-1;
        //cout << "(" << v1 << "," << v2 << ")" <<endl;
        //if(adjMatrix[v1][v2] == 0) return -1; // if the path breaks, return -1 for length (invalid)
        result += adjMatrix[v1][v2];
    }
    return result;
}

/** 
 * Determines the degree centrality of any node
 * 
 * @param i the node to calculate the degree centrality of
 * 
 * @return the degree of this vertex
 */ 
double Graph::degreeCentrality(int i){
    return getAdjacentVertices(i).size();
}

/** 
 * Ranks all the DataObjects by order of their degree centrality and returns the vector
 * 
 * @return a vector of all the games in the graph, ranked by degree centrality
 */ 
vector<DataObject> Graph::degreeCentrality(){
    vector <DataObject> result;
    priority_queue<pair<int,double>, vector<pair<int,double>>, comparison> degRank;
    for(size_t i = 0; i < adjMatrix.size(); i++){
        degRank.push(pair<int,double>((int)i, degreeCentrality(i)));
    }

    for(size_t i = 0; i < adjMatrix.size(); i++){
        result.push_back(data[degRank.top().first]);
        degRank.pop();
    }

    reverse(result.begin(), result.end());
    return result;
}

/** 
 * finds the dominant eigenvector of the adjacency matrix of the graph, which can be
 * ranked to find the eigenvector centrality
 * 
 * @param num_iters the number of iterations of eigenvector computation to do
 * 
 * @return the dominant eigenvector of the graph
 */ 
vector<double> Graph::eigenVector(int num_iters){
    vector<double> result(adjMatrix.size(), 1); // input vector of all 1s
    for(int k = 0; k < num_iters; k++){
        cout << "Computing eigenvector ... Pass # (" << (k+1) << "/" << num_iters << ")" << "\r";
        cout.flush();
        vector<double> vec(result.size(), 0);
        for(size_t i = 0; i < adjMatrix.size(); i++){
            vector<int> neighbors = getAdjacentVertices(i);
            for (size_t j = 0; j < neighbors.size(); j++){
                double weight = 1/adjMatrix[i][neighbors[j]];
                vec[neighbors[j]] += weight * result[i];
            }
        }
        result = vec;
    }
    cout << endl << "Eigenvector loaded" << endl;

    double sum = 0;

    for (size_t i = 0; i < result.size(); i++)
    {
        sum += result[i];
    }

    for (size_t i = 0; i < result.size(); i++)
    {
        result[i]/=sum;
    }
    
    return result;
}

/** 
 * Ranks all the DataObjects by order of their eigenvector centrality and returns the vector
 * 
 * @return a vector of all the games in the graph, ranked by eigenvector centrality
 */ 
vector<DataObject> Graph::eigenvectorCentrality(){
    vector <DataObject> result;
    vector <double> eigenvec = eigenVector(12);
    priority_queue<pair<int,double>, vector<pair<int,double>>, comparison> degRank;
    for(size_t i = 0; i < adjMatrix.size(); i++){
        degRank.push(pair<int,double>((int)i, eigenvec[i]));
    }

    for(size_t i = 0; i < adjMatrix.size(); i++){
        result.push_back(data[degRank.top().first]);
        degRank.pop();
    }

    reverse(result.begin(), result.end());
    return result;
}

/** 
 * counts number of strings in both lists
 * 
 * @param first the first vector of strings
 * @param second the second vector of strings 
 * 
 * @return the number of overlaps
 */ 
int Graph::numOverlaps(vector<string> first, vector<string> second){
    
    int counter = 0;

    for(size_t i = 0; i < first.size(); i++){
        if(find(second.begin(), second.end(), first[i])!=second.end()){
            counter++;
        }
    }

    return counter;
}

/**
 * returns the edge weight between two vertices (0 means no edge)
 * 
 * @param v1 the first vertex
 * 
 * @param v2 the second vertex
 * 
 * @return the weight between these two vertices (0 for no edge between them)
 */
double Graph::getEdge(int v1, int v2){
    if(v1 < (int)adjMatrix.size() && v2 < (int)adjMatrix.size()){
        return adjMatrix[v1][v2];
    }
    return -1;
}

/**
 * prints the adjacent vertices of any given vertex
 * this method was used mostly for testing
 * 
 * @param i the vertex to print the neighbors of
 */
void Graph::printAdjVertices(int i){
    vector<int> result = getAdjacentVertices(i);
    cout << "( ";
    for(unsigned x = 0; x < result.size(); x++){
        if(x!=result.size()-1){
            cout<< result[x] << ", ";
        }else{
            cout << result[x] << ")" << endl;
        }
    }
    cout << result.size() << endl;
}

/**
 * prints the nearest neighbor to a certain vertex
 * this method was used mostly for testing
 * 
 * @param i the neighbor to print the nearest neighbor of
 */
void Graph::printNearestVertex(int i){
    int smallest = -1;
    for(unsigned j = 0; j < adjMatrix[i].size(); j++){
        if(adjMatrix[i][j]!=0){
            if(smallest == -1 || adjMatrix[i][j]<adjMatrix[i][smallest]){
                smallest = j;
            }
        }
    }
    cout << "Closest to " << data[i].name << " is " << data[smallest].name << ", distance = " << adjMatrix[i][smallest] << endl;
}