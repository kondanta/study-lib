#include "lib.h"
#include <iostream>
#include <map>
#include <vector>

using namespace std;
// This is a data class for returning the result of maximum rainfall
class Result {
private:
  string month;
  double rain_amount;

public:
  string getMaxMonth() { return month; }
  double getRainfall() { return rain_amount; }

  Result(string mon, double ann) {
    month = mon;
    rain_amount = ann;
  }
};

// This is the Target Interface. It has two methods to calculate
// average and maximum rain fall.
class Library {
public:
  virtual ~Library() = default;
  // Calculates average. It accepts a map data structure.
  // It contains month and rainfall amount pairs.
  virtual double calculate_average(map<string, int> m) {
    double avg = 0.0;
    map<string, int>::iterator it;
    for (it = m.begin(); it != m.end(); it++) {
      avg += it->second;
    }
    return avg / m.size();
  }
  // Calculates Maximum. It accepts a map data structure.
  // It contains month and rainfall amount pairs.
  virtual Result *calculate_max(map<string, int> m) {
    double max = 0.0;
    string maxMonth;
    map<string, int>::iterator it;
    for (it = m.begin(); it != m.end(); it++) {
      if (it->second > max) {
        maxMonth = it->first;
        max = it->second;
      }
    }
    return new Result(maxMonth, max);
  }
};

class NewLibAdapter : public Library, public NewLibrary {
public:
  // Generates the vectors.
  void fillTheVector(map<string, int> m) {
    for (map<string, int>::iterator i = m.begin(); i != m.end(); ++i) {
      keys.push_back(i->first);
      values.push_back(i->second);
    }
  }
  Result *calculate_max(map<string, int> adaptee) {
    NewResult *res;
    fillTheVector(adaptee);
    res = calculate(keys, values);
    return new Result(res->getMonth(), res->getMax());
  }

  double calculate_average(map<string, int> adaptee) {
    double avg;
    NewResult *res;
    fillTheVector(adaptee);
    res = calculate(keys, values);
    avg = res->getAverage();
    return avg;
  }

private:
  vector<string> keys;
  vector<double> values;
};

int main() {
  Result *result;
  Library lib;
  NewLibAdapter adaptor;

  map<string, int> hashmap;
  hashmap["March"] = 112;
  hashmap["April"] = 115;
  hashmap["May"] = 116;
  result = lib.calculate_max(hashmap);
  cout << "Max rainfall occured on: " << result->getMaxMonth() << endl;
  cout << "Average rainfall on this year (mm):"
       << lib.calculate_average(hashmap) << endl;
  // adaptor interface
  result = adaptor.calculate_max(hashmap);
  cout << "Max: " << result->getMaxMonth() << endl;
  cout << adaptor.calculate_average(hashmap);
}
