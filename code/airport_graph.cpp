#include "airport_graph.h"
#include <cmath> 
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <fstream>


using namespace std;

Graph::Graph(){}


Graph::Graph(string & airportFile, string & routesFile) {
    insertAllVertices(airportFile);
    insertAllEdge(routesFile);
}


void Graph::insertVertex(int ver, Airport air) {
    vertices[ver] = air;
}


void Graph::insertAllVertices(string & fileName){
    fstream file;
    file.open(fileName, ios::in);
    if (file.is_open()) {   
        string curr;
        while (getline(file, curr)) { 
            int elem = 1;
            for (unsigned i = 0; i < curr.size(); ++i) {
                if (curr[i] == ',')
                    elem++;
            }
            if (elem == 14) {
                Airport air(curr);
                insertVertex(air.getID(), air);
            }
        }
        file.close(); 
    }
}


vector<string> Graph::_createEdge(string & line) {
    string currString = "";
    vector<string> flightVector;

    int elem = 1;
    for (size_t i = 0; i < line.size(); ++i) {
        if (line[i] == '\\')
            return flightVector;
        if (line[i] == ',')
            elem++;
    }
    if (elem != 9) {
        return flightVector;
    }
    for (size_t i = 0; i < line.size(); ++i) {
        if (line[i] == ',') {
            flightVector.push_back(currString);
            currString = "";
        }
        else {
            currString += line[i];
        }
    }
    return flightVector;
}


Flight Graph::createEdge(vector<string> flightVector) {
    int source = stoi(flightVector[3], NULL);
    int dest = stoi(flightVector[5], NULL);
    //before caculating weight, gotta check if source and destination airports are both inserted
    //to avoid inserting an element into the map by using [] operator
    if(vertices.find(source) != vertices.end() && vertices.find(dest) != vertices.end()){
        //if an edge to the same destination is not found in the list of adjacent airports
        //the find function returns the key of the desired element or the end iterator if the element is not found
        //only inserts when the flight does not exist in the adjacency list of the airport
        double weight = calcWeight(source, dest);
        return Flight(source, dest, weight);
    }
    //if either airport is not inserted, return default constructed flight
    return Flight();
}


void Graph::insertEdge(Flight f) {       
    int source = f.getSourceId();
    int dest = f.getDestId();
    //if an edge to the same destination is not found in the list of adjacent airports
    //the find function returns the key of the desired element or the end iterator if the element is not found
    //only inserts when the flight does not exist in the adjacency list of the airport
    if (vertices[source].m.find(dest) == vertices[source].m.end())   
        (vertices[source].m)[dest] = f;
}


void Graph::insertAllEdge(string & fileName) {
    fstream file;
    file.open(fileName, ios::in);
    if (file.is_open()) {   
        string curr;
        while(getline(file, curr)){ 
            vector<string> currVect = _createEdge(curr);
            
            if(currVect != vector<string>()){
                Flight f = createEdge(currVect);
                Flight defaultF = Flight();
                if(!(f == defaultF))
                    insertEdge(f);
            }
        }
        file.close(); 
    }
}


//for testing: iterate though the unordered_map to see all inserted airports
unordered_map<int, Airport> Graph::getVertices() {
    return vertices;
}


//for testing: iterate though the unordered_map to see inserted flights
unordered_map<int, Flight> Graph::adjVertWithWeight(int airportID) {
    auto it = vertices.find(airportID);
    if (it != vertices.end()) {
        Airport& ap = vertices[airportID];
        return ap.m;
    }
    return unordered_map<int, Flight> ();
}


string Graph::getAPName(int ID) {
    auto it = vertices.find(ID);
    if (it != vertices.end()) {
        return vertices[ID].getName();
    }
    return string();
}

//traversal graph to populate adj matrix for pagerank
void Graph::adjMatrix(PageRank *obj) {
    //determine and set the dimention
    int size = vertices.size();
    obj->adjVec.resize(size, vector<double>(size));
    obj->nameList.resize(size);
    obj->num = size;

    //initialization
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            obj->adjVec[i][j] = 0.0;
        }        
    }
    //populate 
    int x = 0;
    for (auto it = vertices.begin(); it != vertices.end(); ++it) {
        if (it->second.getID() != 0) {
             obj->nameList[x] = (it->second.getID());
        }
        x++;     
    }

    //check every flight of every airport
    //put the weight into the adj matrix according to the order of the name
    x = 0;
    for (auto it = vertices.begin(); it != vertices.end(); ++it) {
        if(x != size){
            if(it->second.getID() != 0){
                 //check the flights of the current vertices/airport
                for(auto flight = it->second.m.begin(); flight != it->second.m.end(); ++flight){
                    int y = 0;
                //find out the proper place for the weight of the current flight according to the name
                    for (auto temp = obj->nameList.begin(); temp != obj->nameList.end(); ++temp) {
                        if (*temp == flight->second.getDestId()) break;
                            y++;
                        } 
                        if(y != size){
                            obj->adjVec[y][x] = flight->second.getWeight();
                        }
                    }
                x++;
            } 
        }
    }
}


double Graph::radianConvert(double degree) {
    // M_PI is the constant of pi accurate to 1e-30
    return ((M_PI) / 180 * degree);
}
 

double Graph::calcWeight(int fromID, int toID) {
    double lat1 = radianConvert(vertices[fromID].getLatitude());
    double lon1 = radianConvert(vertices[fromID].getLongitude());
    double lat2 = radianConvert(vertices[toID].getLatitude());
    double lon2 = radianConvert(vertices[toID].getLongitude());

    double lonDiff = lon2 - lon1;
    double latDiff = lat2 - lat1;
    
    //using Haversine Formula, radious of earth is 6378.137 KM
    long double ans = pow(sin(latDiff / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(lonDiff / 2), 2);
    ans = 2 * asin(sqrt(ans)) * 6378.137;
    // ans = 2 * asin(sqrt(ans)) * 6371;
    return ans; 
}