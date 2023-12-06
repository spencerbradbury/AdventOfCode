#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <unordered_set>
#include <cmath>

using namespace std;

regex numbers("(\\d+)");
regex map_nums("(\\d+)\\s(\\d+)\\s(\\d+)");

enum input_state {SEED, SEED_TO_SOIL, SOIL_TO_FERT, FERT_TO_WATER, WATER_TO_LIGHT, LIGHT_TO_TEMP, TEMP_TO_HUMID, HUMID_TO_LOC};

vector<long> source;
vector<long> dest;

int main() {
    ifstream file("input.txt");
    string line;
    input_state state = SEED;

    while (getline(file, line)) {
        smatch match;

        if (line == ""){
            state = (input_state)((int)state + 1);
            for (int i = 0; i < source.size(); i++){
                if (dest[i] == 0){
                    dest[i] = source[i];
                }
            }
            source = dest;
            dest = vector<long>(source.size(), 0);
        }
        else if (state == SEED){
            while (regex_search(line, match, numbers)) {
                dest.push_back(stol(match[1]));
                line = match.suffix().str();
            }
        }
        else if (regex_search(line, match, map_nums)){
            for (int i = 0; i < source.size(); i++){
                if (source[i] >= stol(match[2]) && source[i] < stol(match[2]) + stol(match[3])){
                    dest[i] = source[i] - stol(match[2]) + stol(match[1]);
                }
            }
        }
    }  

    long min = INT64_MAX;
    for (long seed : dest) {
        min = min < seed ? min : seed;
    }

    cout << min << endl;
    return min;
}   