#pragma once
#include <iostream>
#include <vector>

using namespace std;

class readfile {
    public:
    class Airport {
        public:
        Airport(int id, string name, string city, string country, string code, double latitude, double longitude){
            int id_ = id;
            string name_ = name;
            string city_ = city;
            string country_ = country;
            string code_ = code; 
            double latitude_ = latitude; 
            double longitude_ = longitude;
        }
        int id_;
        string name_;
        string city_;
        string country_;
        string code_; 
        double latitude_; 
        double longitude_;
    }
    vector<Airport> FileToAirports(const string& file_name);

    class Route {
        public:
        Route(string source_code, int source_id, string destination_code, int destination_id){
            string source_code_ = source_code;
            int source_id_ = source_id;
            string destination_code_ = destination_code;
            int destination_id_ = destination_id;
        }
 
        string source_code_;
        int source_id_;
        string destination_code_;
        int destination_id_;
    }
    vector<Route> FileToRoute(const string& file_name);

    private:
        const vector<vector<string>> readCSV(const :string& file_name) const;
};