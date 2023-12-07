#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <unordered_set>
#include <cmath>

using namespace std;

regex numbers("(\\d+)");

vector<int> times;
vector<int> dists;

int main() {
    ifstream file("input.txt");
    string line;
    smatch match;

    int out = 1;

    getline(file, line);
    while (regex_search(line, match, numbers)) {
        times.push_back(stoi(match[0]));
        line = match.suffix().str();
    }

    getline(file, line);
    while (regex_search(line, match, numbers)) {
        dists.push_back(stoi(match[0]));
        line = match.suffix().str();
    }

    for (int i = 0; i < times.size(); i++) {
        int count = 0;
        int total = times[i];
        cout << times[i] << " " << dists[i] << endl;
        for (int hold = 1; hold < times[i]; hold++){
            int remaining = total - hold;
            int calcDist = hold * remaining;
            if (calcDist > dists[i]) {
                count++;
            }
        }
        out *= count;
    }


    cout << out << endl;
}   