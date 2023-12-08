#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <unordered_set>
#include <cmath>

using namespace std;

regex numbers("(\\d+)");

long ltime;
string stime;
long ldist;
string sdist;

int main() {
    ifstream file("input.txt");
    string line;
    smatch match;

    long out = 1;

    getline(file, line);
    while (regex_search(line, match, numbers)) {
        stime += match[0];
        line = match.suffix().str();
    }
    ltime = stol(stime);

    getline(file, line);
    while (regex_search(line, match, numbers)) {
        sdist += match[0];
        line = match.suffix().str();
    }
    ldist = stol(sdist);


    long count = 0;
    for (long hold = 1; hold < ltime; hold++){
        long remaining = ltime - hold;
        long calcDist = hold * remaining;
        if (calcDist > ldist) {
            count++;
        }
    }
    out *= count;



    cout << out << endl;
}   