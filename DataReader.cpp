#include "DataReader.h"

/**
 * Constructor that will build a full data reader from a given file
 * 
 * @param fileName Name of the file to be read
 */ 
DataReader::DataReader(string fileName){
    
    ifstream myFile(fileName);
    string line;
    string data;

    if(!myFile.good()){
        myFile.close();
        return;
    }

    getline(myFile, line); // throw out first line

    while(getline(myFile, line)){
        stringstream ss(line);
        int counter = 0;
        DataObject databoi;
        
        while(getline(ss, data, ',')){
            //cout << counter << ": " << data << endl;
            
            if (counter == 0){
                databoi.rank = stoi(data);
            }
            else if(counter == 3){
                string app = "";
                string junk = "";
                if(data[0] == '\"'){
                    data.erase(0,1);
                    getline(ss,app,'\"'); // get the rest of the string
                    app = "," + app; // append missed comma
                    getline(ss, junk, ','); // throw out the junk comma
                }
                databoi.name = data + app;
            }
            else if(counter == 4){
                databoi.min_players = stoi(data);
            }
            else if(counter == 5){
                databoi.max_players = stoi(data);
            }
            else if(counter == 6){
                databoi.avg_time = stoi(data);
            }
            else if(counter == 7){
                databoi.min_time = stoi(data);
            }
            else if(counter == 8){
                databoi.max_time = stoi(data);
            }
            else if(counter == 9){
                databoi.year = stoi(data);
            }
            else if(counter == 10){
                databoi.avg_rating = stod(data);
            }
            else if(counter == 14){
                databoi.age = stoi(data);
            }
            else if(counter == 15){ // mechanics
                if(data[0]=='\"'){
                    string app = "";
                    string junk = "";
                    getline(ss,app,'\"'); // get the rest of the string
                    app = "," + app; // append missed comma
                    getline(ss, junk, ','); // throw out the junk comma
                    string vecline = data + app;
                    vecline.erase(0,1);
                    stringstream vecss(vecline);
                    while(getline(vecss, app, ',')){
                        if(app[0]==' '){
                            app.erase(0,1);
                        }
                        databoi.mechanics.push_back(app);
                    }
                }else{
                    databoi.mechanics.push_back(data);
                }
            }
            else if(counter == 17){
                if(data[0]=='\"'){
                    string app = "";
                    string junk = "";
                    getline(ss,app,'\"'); // get the rest of the string
                    app = "," + app; // append missed comma
                    getline(ss, junk, ','); // throw out the junk comma
                    string vecline = data + app;
                    vecline.erase(0,1);
                    stringstream vecss(vecline);
                    while(getline(vecss, app, ',')){
                        if(app[0]==' '){
                            app.erase(0,1);
                        }
                        databoi.categories.push_back(app);
                    }
                }else{
                    databoi.categories.push_back(data);
                }
            }
            
            
            counter++;
        }
        csvData.push_back(databoi);
    }

    myFile.close();

}

/**
 * Constructor that will build data reader from first n objects in file
 * 
 * @param fileName Name of file to be read
 * @param n Number of objects to read
 */ 
DataReader::DataReader(string fileName, int n){
    ifstream myFile(fileName);
    string line;
    string data;

    if(!myFile.good()){
        myFile.close();
        return;
    }

    getline(myFile, line); // throw out first line

    while(getline(myFile, line) && n > 0){
        n--;
        stringstream ss(line);
        int counter = 0;
        DataObject databoi;
        
        while(getline(ss, data, ',')){
            //cout << counter << ": " << data << endl;
            
            if (counter == 0){
                databoi.rank = stoi(data);
            }
            else if(counter == 3){
                string app = "";
                string junk = "";
                if(data[0] == '\"'){
                    data.erase(0,1);
                    getline(ss,app,'\"'); // get the rest of the string
                    app = "," + app; // append missed comma
                    getline(ss, junk, ','); // throw out the junk comma
                }
                databoi.name = data + app;
            }
            else if(counter == 4){
                databoi.min_players = stoi(data);
            }
            else if(counter == 5){
                databoi.max_players = stoi(data);
            }
            else if(counter == 6){
                databoi.avg_time = stoi(data);
            }
            else if(counter == 7){
                databoi.min_time = stoi(data);
            }
            else if(counter == 8){
                databoi.max_time = stoi(data);
            }
            else if(counter == 9){
                databoi.year = stoi(data);
            }
            else if(counter == 10){
                databoi.avg_rating = stod(data);
            }
            else if(counter == 14){
                databoi.age = stoi(data);
            }
            else if(counter == 15){ // mechanics
                if(data[0]=='\"'){
                    string app = "";
                    string junk = "";
                    getline(ss,app,'\"'); // get the rest of the string
                    app = "," + app; // append missed comma
                    getline(ss, junk, ','); // throw out the junk comma
                    string vecline = data + app;
                    vecline.erase(0,1);
                    stringstream vecss(vecline);
                    while(getline(vecss, app, ',')){
                        if(app[0]==' '){
                            app.erase(0,1);
                        }
                        databoi.mechanics.push_back(app);
                    }
                }else{
                    databoi.mechanics.push_back(data);
                }
            }
            else if(counter == 17){
                if(data[0]=='\"'){
                    string app = "";
                    string junk = "";
                    getline(ss,app,'\"'); // get the rest of the string
                    app = "," + app; // append missed comma
                    getline(ss, junk, ','); // throw out the junk comma
                    string vecline = data + app;
                    vecline.erase(0,1);
                    stringstream vecss(vecline);
                    while(getline(vecss, app, ',')){
                        if(app[0]==' '){
                            app.erase(0,1);
                        }
                        databoi.categories.push_back(app);
                    }
                }else{
                    databoi.categories.push_back(data);
                }
            }
            
            
            counter++;
        }
        csvData.push_back(databoi);
    }

    myFile.close();
}   

/**
 * Get object at a certain index
 * 
 * @param index the index of the object to return
 * 
 * @return the dataobject at the index
 */
DataObject DataReader::getObject(int index){
    if (index >= size()) {
        return DataObject();
    }
    return csvData[index];
}

/**
 * Get object at a certain index
 * 
 * @param name the name of the object to return
 * 
 * @return the dataobject with the name
 */
DataObject DataReader::getObject(string name){
    for (char & c: name) c = toupper(c); // convert to uppercase
    for(unsigned i = 0 ; i < csvData.size(); i++){
        string s = csvData[i].name;
        for (char & c: s) c = toupper(c);
        if(s == name){
            return csvData[i];
        }
    }
    return DataObject();
}


/**
 * Get object at a certain index
 * 
 * @param index the index of the object to return
 * 
 * @return the dataobject at the index
 */
DataObject DataReader::operator[](int i){
    return getObject(i);
}

/**
 * Get object with certain name
 * 
 * @param name the name of the object to return
 * 
 * @return the dataobject with the name
 */
DataObject DataReader::operator[](string n){
    return getObject(n);
}


/**
 * Get index of object with certain name
 * 
 * @param name the name of the object index to return
 * 
 * @return the index of the object with the name
 */
int DataReader::getObjectIndex(string n){
    n.erase(remove(n.begin(), n.end(), ' '), n.end());
    for (char & c: n) c = toupper(c);
    for(int i = 0; i < (int)csvData.size(); i++){
        string s = csvData[i].name;
        s.erase(remove(s.begin(), s.end(), ' '), s.end());
        for (auto & c: s) c = toupper(c);
        if(s == n){
            return i;
        }
    }
    return -1;
}

/** 
 * Gets the size of the dataset
 * 
 * @return the number of elements in the dataset
 */
int DataReader::size(){
    return csvData.size();
}