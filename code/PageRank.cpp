#include <iostream>
#include <vector>
#include <numeric>
#include <math.h>
#include "PageRank.h"


void PageRank::makeA(int num, double damping) {
    this -> num = num;
    //resize adj matrix
    //A.resize(num,vector<double>(num));

    //use damping factor to generate the require extra factor
    double d_factor = (1 - damping) / num;

    //adjust adj matrix according to pagerank alg
    for (int i = 0; i < num; i++) {
        double sum = 0;
        for (int j = 0; j < num; j++) {
            sum += adjVec[j][i];
        }     
        if (sum == 0) {
            //double z = 1/this->num;
            for(int j = 0; j < num; j++){
                adjVec[j][i] = 1.0/num;
            }              
        } else {
            for(int j = 0; j < num; j++){
                adjVec[j][i] = (adjVec[j][i]/sum) * damping + d_factor;
            }             
        }
    }
}


vector<double> PageRank::rank(vector<double> initial, int time, bool normalize) {
    vector<double> temp = initial;
    vector<double> temp2 = initial;
    for (int t = 0; t < time; t++){
        for (int i = 0; i < num; i++){
            //initialization
            temp2[i] = 0;
            for (int j = 0; j < num; j++){
                temp2[i] += adjVec[i][j] * temp[j];

                if (normalize) {
                    double sum = 0;
                    //perform norm 2 normalize
                    for (std::vector<double>::iterator it = temp2.begin(); it != temp2.end(); ++it) {
                        sum += (*it)*(*it);
                    }

                    for (int n = 0; n < num; n++) {
                        temp2[n] = temp2[n] / sqrt(sum);
                    }
                }
            }     
        }
        temp = temp2;
    }
    prResult = temp;
    return temp;
}



vector<int> PageRank::topAirport(int num){
    vector<int> airport;
    vector<double> largest;
    airport.resize(num);
    largest.resize(num);

    int position = 0;

    //figure out the index of the important airport in the pagerank result vector
    for (int i = 0; i < num; i++){
        double max = 0;
        for (auto it = prResult.begin(); it != prResult.end(); ++it){
            if (*it > max) {
                bool flag = true;
                //check if the current airport is already on the list of the important airport
                for (auto temp = largest.begin(); temp != largest.end(); ++temp) {
                    if (*temp == *it) {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    max = *it;
                }
            }
        }
        largest[position] = (max);
        position++;
    }

    position = 0;
    //using the index and the name_list to find out the relating airport id
    for (int i = 0; i < num; i++){
        int count = 0;
        for (auto it = prResult.begin(); it != prResult.end(); ++it){
            if (largest[i] == *it) {
                airport[position] = (nameList[count]);
                position++;
            }
            count++;
        }
    }

    // cout<< "top"; 
    // cout<< " " << num << " "; 
    // cout<<"important airport\n"; 
    // for(int i = 0; i < num; i++){
    //     cout<<airport[i];
    //     cout<<"\n";
    // }
    return airport;
}


vector<double> PageRank::initialVector() {
    vector<double> initial;
    initial.resize(num);
    for (int i = 0; i < num; i++) {
        initial[i] = rand();
    }
    return initial;
}


void PageRank::printAdjMatrix() {
    // cout<<"adj matrix"<<endl;
    // cout<<"      ";
    // for(int i = 0; i < this->num; i++){
    //     cout<<this->name_list[i];
    //     cout<<"           ";
    // }
    // cout<<"\n";
    // for(int i = 0; i < this->num; i++){
    //     cout<<this->name_list[i];
    //     cout<<"  ";
    //     for(int j = 0; j < this->num; j++){
    //         cout<<this->A[i][j];
    //         cout<<"  ";
    //     } 
    //     cout<<"\n";
    // }
    // cout<<"\n";

    cout<<"    Adjcent Matrix"<<endl;
    cout<<"        ";
    for(int i = 0; i < num; i++){
        cout << nameList[i] << "           ";
    }
    cout << "\n";
    for(int i = 0; i < num; i++){
        cout << nameList[i] << "  ";
        for(int j = 0; j < num; j++){
            cout << adjVec[i][j] << "  ";
        } 
        cout << "\n";
    }
    cout << "\n";
}


void PageRank::printResult(){
    // cout<<"page rank result\n"; 
    // cout<<" ID      value\n"; 
    // for(int i = 0; i < this->num; i++){
    //     cout<<this->name_list[i];
    //     cout<<" ";
    //     cout<<this->pr_result[i];
    //     cout<<"\n";
    // }
    // cout<<"\n";

    cout<<"Page Rank Result\n"; 
    cout<<" ID----Value\n"; 
    for(int i = 0; i < num; i++){
        cout<<nameList[i];
        cout<<"---";
        cout<<prResult[i];
        cout<<"\n";
    }
    cout<<"\n";
}