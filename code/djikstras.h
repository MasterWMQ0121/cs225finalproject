#pragma once
#include "airport_graph.h"
#include "Flight.h"
#include "Airport.h"

#include <vector>
#include <map>
#include <queue>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class Djikstras {
    public:

        /** Implementation of Djikstra's Algorithm
         * @param g Graph of connecting airport 
         * @param StartAirport Starting airport
         * @param DestAirport Destination
        **/
        Djikstras(Graph g, string StartAirport, string DestAirport);
        
        //Getter: geting the shortest distance from starting airport to destination
        double getShortestDistance() const;
        
        //Getter: geting all airports along the path
        vector<string> getPathVertices() const;

        /** This function finds all neighbor airports of the given airport
         * @param Source Name of the airport
         * Return a vector with the name of neighboring airport and distance 
        **/
        vector<pair<int, double>> getAdjacent(string Source);


        /** Helper function that check whether the given vertex exists
         * @param node Name of the airport
        **/
        bool vertexExists(string node);

    private:
        map<string, double> distances;
        unordered_map<string, string> previous_nodes;
        priority_queue<pair<double, string>, vector<pair<double, string>>,greater<pair<double, string>> > Q;
        unordered_map <string, bool> visited; 
        double path;
        unordered_map<string, unordered_map<int, Flight> > adjacency_list;
        vector<string> path_vertices;
};