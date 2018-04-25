#include<iostream>
#include<vector>

// This is a data class for returning the results.

using namespace std;
class NewResult {
private:
    double max_rain_amount;
    double ave_rain_amount;
    string month;
public:
    double getMax(){return max_rain_amount;}
    double getAverage(){return ave_rain_amount;}
    string getMonth() {return month;}

    NewResult(double max, string m, double ave){
        max_rain_amount = max;
        ave_rain_amount = ave;
        month = m;
    }
};

// The new Library. This will be the Adaptee
class NewLibrary {
public:
    // Calculates Average and maximum. It accepts two vectors. One for months
    // The other for rainfall amounts.
    NewResult* calculate(vector<string> months, vector<double> rain){
        double max = 0;
        string month = "";
        double avg = 0.0;
        for(int i = 0;i < rain.size();i++){
            avg = avg + rain[i];
            if(rain[i] > max) {
                max = rain[i];
                month = months[i];
            }
        }
        avg = avg/rain.size();
        return new NewResult(max, month, avg);
    }
};

