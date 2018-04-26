#include <iostream>
#include <vector>
// This is a data class for returning the results.
using namespace std;
class NewResult {
private:
  double max_rain_amount;
  double ave_rain_amount;
  string month;

public:
  double getMax() { return max_rain_amount; }
  double getAverage() { return ave_rain_amount; }
  string getMonth() { return month; }

  NewResult(double max, string m, double ave) {
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
  NewResult *calculate(vector<string> months, vector<double> rain) {
    double max = 0;
    string month = "";
    double avg = 0.0;
    for (int i = 0; i < rain.size(); i++) {
      avg = avg + rain[i];
      if (rain[i] > max) {
        max = rain[i];
        month = months[i];
      }
    }
    avg = avg / rain.size();
    return new NewResult(max, month, avg);
  }
};
// The following is just for demonstrating how to use the Library. You do not
// need it in your solution
int Main() {

  vector<string> months;
  vector<double> rain;

  months.push_back("March");
  rain.push_back(110);
  months.push_back("April");
  rain.push_back(115);
  months.push_back("May");
  rain.push_back(111);

  NewLibrary lib;
  NewResult *res = lib.calculate(months, rain);
  cout << "Max rainfall occured on: " << res->getMonth() << endl;
  cout << "Average rainfall on this year (mm): " << res->getAverage() << endl;
}
