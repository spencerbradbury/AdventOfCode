#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <unordered_set>
#include <cmath>

using namespace std;

regex seed_nums("(\\d+)\\s+(\\d+)");
regex map_nums("(\\d+)\\s(\\d+)\\s(\\d+)");

enum input_state {SEED, SEED_TO_SOIL, SOIL_TO_FERT, FERT_TO_WATER, WATER_TO_LIGHT, LIGHT_TO_TEMP, TEMP_TO_HUMID, HUMID_TO_LOC};

// pair<start, length> of seeds
vector<pair<long,long>> source;
vector<pair<long,long>> dest;

int main() {
    ifstream file("input.txt");
    string line;
    input_state state = SEED;

    while (getline(file, line)) {
        smatch match;

        if (line == ""){
            state = (input_state)((int)state + 1);

            // Add all remaining pairs from source to dest
            for (int i = 0; i < source.size(); i++){
                if (source[i] != pair(long(-1),long(-1))){
                    dest.push_back(source[i]);
                }
            }

            source = dest;
            dest.clear();
        }
        else if (state == SEED){
            while (regex_search(line, match, seed_nums)) {
                dest.push_back(pair(stol(match[1]), stol(match[2])));
                line = match.suffix().str();
            }
        }
        else if (regex_search(line, match, map_nums)){
            for (int i = 0; i < source.size(); i++){
                if (source[i].first + source[i].second > stol(match[2]) && source[i].first < stol(match[2]) + stol(match[3])){
                    //Four cases:
                    // 1. seed range is fully covered by map range
                    if (source[i].first >= stol(match[2]) && source[i].first + source[i].second <= stol(match[2]) + stol(match[3])){
                        dest.push_back(pair(source[i].first - stol(match[2]) + stol(match[1]), source[i].second));
                        source[i].first = -1;
                        source[i].second = -1;
                    }
                    // 2. seed range does not start in map range, but extends into and ends in map range
                    else if (source[i].first < stol(match[2]) && source[i].first + source[i].second <= stol(match[2]) + stol(match[3])){
                        long split = source[i].first + source[i].second - stol(match[2]);
                        dest.push_back(pair(stol(match[1]), split));
                        source[i].second -= split;
                    }
                    // 3. seed range starts in map range, but extends out of map range
                    else if (source[i].first >= stol(match[2]) && source[i].first + source[i].second > stol(match[2]) + stol(match[3])){
                        long split = stol(match[2]) + stol(match[3]) - source[i].first;
                        dest.push_back(pair(source[i].first - stol(match[2]) + stol(match[1]), split));
                        source[i].first += split;
                        source[i].second -= split;
                    }
                    // 4. seed range begins before map range and ends after map range
                    else if (source[i].first < stol(match[2]) && source[i].first + source[i].second > stol(match[2]) + stol(match[3])){
                        long split1 = stol(match[2]) - source[i].first;
                        long split2 = source[i].first + source[i].second - (stol(match[2]) + stol(match[3]));
                        dest.push_back(pair(stol(match[1]), split1));
                        source[i].second = split1;
                        source.push_back(pair(stol(match[2]) + stol(match[3]), split2));
                    }
                }
            }

        }
    }  

    for (int i = 0; i < source.size(); i++){
        if (source[i] != pair(long(-1),long(-1))){
            dest.push_back(source[i]);
        }
    }

    long min = INT64_MAX;
    // cout << dest << endl;
    for (pair<long,long> seeds : dest) {
        if(seeds.first < min) {
            cout << "old min: " << min << " | ";
            min = seeds.first;
            cout << "new min: " << min << "\n";
        }

        // min = seeds.first < min ? seeds.first : min;
    }
    cout << "min: " << endl;
    cout << min << endl;
    return min;
}   