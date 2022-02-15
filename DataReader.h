#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>


using namespace std;

/** 
 * A struct that contains all the data of a certain game
 * 
 * Member names correspond to what data is being held
 * 
 */
struct DataObject{

    DataObject() : rank(-1) {}
    int rank;
    string name;
    int min_players;
    int max_players;
    int avg_time;
    int min_time;
    int max_time;
    int year;
    double avg_rating;
    int age;
    vector<string> mechanics;
    vector<string> categories;
};

class DataReader{

    public:

        /**
         * Default constructork, it is empty
         */ 
        DataReader(){}

        /**
         * Constructor that will build a full data reader from a given file
         * 
         * @param fileName Name of the file to be read
         */ 
        DataReader(string fileName);

        /**
         * Constructor that will build data reader from first n objects in file
         * 
         * @param fileName Name of file to be read
         * @param n Number of objects to read
         */ 
        DataReader(string fileName, int n);

        /**
         * Get object at a certain index
         * 
         * @param index the index of the object to return
         * 
         * @return the dataobject at the index
         */
        DataObject getObject(int index);

        /**
         * Get object at a certain index
         * 
         * @param name the name of the object to return
         * 
         * @return the dataobject with the name
         */
        DataObject getObject(string name);


        /**
         * Get object at a certain index
         * 
         * @param index the index of the object to return
         * 
         * @return the dataobject at the index
         */
        DataObject operator[](int i);

        /**
         * Get object at a certain index
         * 
         * @param name the name of the object to return
         * 
         * @return the dataobject with the name
         */
        DataObject operator[](string n);

        /** 
         * Gets the size of the dataset
         * 
         * @return the number of elements in the dataset
         */
        int size();

        /**
         * Get index of object with certain name
         * 
         * @param name the name of the object index to return
         * 
         * @return the index of the object with the name
         */
        int getObjectIndex(string n);

    private:
        vector<DataObject> csvData;

};