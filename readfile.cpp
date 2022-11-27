#include "readfile.h"
#include <fstream>
#include <sstream>

using namespace std;

vector<Airport> readfile::FileToAirports(const string& file_name){
    vector<vector<string>> ap = readCSV(file_name);
    vector<Airport> output;
    for(auto a: ap){
        Airport airport = Airport(stoi(a[0]), a[1], a[2], a[3], a[4], stod(a[6]), stod(a[7]));
        output.push_back(airport);
    }
    return output;
}
vector<Route> readfile::FileToRoute(const string& file_name){
    vector<vector<string>> rt = readCSV(file_name);
    vector<Airport> output;
    for(auto r: rt){
        int si;
        try{
            si = stoi(r[3])
        } catch(...){
            si = -1;
        }
        int di;
        try{
            di = stoi(r[5])
        } catch(...){
            di = -1;
        }
        Route route= Route(r[2], si, r[4],di);
        output.push_back(route);
    }
    return output;
}
const vector<vector<string>> readfile::readCSV(const string& file_name) const {
    vector<vector<string>> v;
    ifstream file (file_name);
    string line;
    while (sgetline(file,line))
    {
        stringstream stream_line(line);
        vector<string> line_properties;
        while(stream_line.good())
        {
            string element;
            getline(stream_line, element, ',' );
            line_properties.push_back(element);
        }
        v.push_back(line_properties);
    }
    file.close();
    return v;
}

