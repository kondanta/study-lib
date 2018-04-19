#include<iostream>
#include<vector>
#include<map>
#include "newlib.h"

using namespace std;
// This is a data class for returning the result of maximum rainfall
class Result {
private:
    string month;
    double rain_amount;
public:
    string getMaxMonth(){return month;}
    double getRainfall(){return rain_amount;}

    Result(string mon, double ann){
        month = mon;
        rain_amount =ann;
    }
};

// This is the Target Interface. It has two methods to calculate
// average and maximum rain fall.
class Library {
public:
    // Calculates average. It accepts a map data structure.
    // It contains month and rainfall amount pairs.
    virtual double calculate_average(map<string,int> m){
        double avg = 0.0;
        map<string, int>::iterator it;
        for(it=m.begin(); it!=m.end(); it++){
            avg+=it->second;
        }
        return avg/m.size();
    }

    // Calculates Maximum. It accepts a map data structure.
    // It contains month and rainfall amount pairs.
    virtual Result* calculate_max(map<string,int> m){
        double max = 0.0;
        string maxMonth;
        map<string, int>::iterator it;
        for(it=m.begin(); it!=m.end(); it++){
            if(it->second > max) {
                maxMonth = it->first;
                max = it->second;
            }
        }
        return new Result(maxMonth,max);
    }
};

class Adapto : public Library, private NewLibrary{
public:
    double calculate_average(map<string,int> m) override {
        map<string, int>::iterator it;
        vector<double> rain;
        vector<string> months;
        for(it=m.begin(); it!=m.end(); it++){
            months.push_back(it->first);
            rain.push_back(it->second);
        }
        NewResult* res = NewLibrary::calculate(months,rain);
        return res->getAverage();
    }

    Result* calculate_max(map<string,int> m) override {
        map<string, int>::iterator it;
        vector<double> rain;
        vector<string> months;
        for(it=m.begin(); it!=m.end(); it++){
            months.push_back(it->first);
            rain.push_back(it->second);
        }
        NewResult* resnew = NewLibrary::calculate(months,rain);
        Result* resold = new Result(resnew->getMonth(),resnew->getMax());
        return resold;

    }

};



int main() {
    Result* result;
    auto *adapt = new Adapto();
    map<string,int> hashmap;
    hashmap["March"] = 112;
    hashmap["April"] = 115;
    hashmap["May"] = 116;
    result = adapt->calculate_max(hashmap);
    cout<<"Max rainfall occurred on: " << result-> getMaxMonth()<<endl; // Should be May
    cout<<"Average rainfall on this year (mm): "<<adapt->calculate_average(hashmap)<<endl; // Should be 114.333...
}