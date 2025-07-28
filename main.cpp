#include <iostream>
#include <fstream>
#include <cmath>
#include <map>
#include <vector>
#include <string>
#include "json.hpp" 

using namespace std;
using json = nlohmann::json;

using ll = long long;


ll baseToDecimal(const string &value, int base) {
    ll result = 0;
    for (char ch : value) {
        int digit;
        if (isdigit(ch)) digit = ch - '0';
        else digit = tolower(ch) - 'a' + 10;
        result = result * base + digit;
    }
    return result;
}


ll lagrangeInterpolationAtZero(const vector<pair<ll, ll>> &points) {
    ll result = 0;
    int k = points.size();

    for (int i = 0; i < k; ++i) {
        ll xi = points[i].first;
        ll yi = points[i].second;

        double numerator = 1, denominator = 1;

        for (int j = 0; j < k; ++j) {
            if (i == j) continue;
            numerator *= -points[j].first;
            denominator *= (xi - points[j].first);
        }

        result += (ll)(yi * (numerator / denominator));
    }

    return result;
}

vector<pair<ll, ll>> extractPoints(const json &data) {
    vector<pair<ll, ll>> points;

    for (auto &el : data.items()) {
        if (el.key() == "keys") continue;

        int x = stoi(el.key());
        int base = stoi(el.value()["base"].get<string>());
        string val = el.value()["value"];

        ll y = baseToDecimal(val, base);
        points.emplace_back(x, y);
    }

    return points;
}

int main() {
    
    vector<string> filenames = { "testcase1.json", "testcase2.json" };

    for (auto &filename : filenames) {
        ifstream infile(filename);
        if (!infile.is_open()) {
            cerr << "Failed to open " << filename << endl;
            continue;
        }

        json input;
        infile >> input;

        int k = input["keys"]["k"];
        vector<pair<ll, ll>> allPoints = extractPoints(input);

        vector<pair<ll, ll>> selectedPoints(allPoints.begin(), allPoints.begin() + k);

        ll secret = lagrangeInterpolationAtZero(selectedPoints);

        cout << "Secret from " << filename << ": " << secret << endl;
    }

    return 0;
}