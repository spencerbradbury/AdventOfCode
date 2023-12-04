#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

typedef struct {
    int value;
    int row;
    int start;
    int end;
    bool counted = false;
} engine_part;

typedef struct {
    int ratio = 1;
    int row;
    int col;
    int adjacent_nums = 0;
} engine_gear;

vector<engine_part> engine_parts;
vector<engine_gear> engine_gears;

regex numbers("(\\d+)");
regex gear("\\*");

int main() {

    ifstream file("input.txt");
    string line;

    int row = 0;
    int sum = 0;

    while (getline(file, line)) {
        smatch partmatch;
        string partline = line;
        int offset = 0;
        while (regex_search(partline, partmatch, numbers)) {
            engine_part part;

            part.row = row;
            part.value = stoi(partmatch[0]);
            part.start = partmatch.position() + offset;
            part.end = part.start + partmatch.length() - 1;
            engine_parts.push_back(part);

            partline = partmatch.suffix().str();
            offset += partmatch.position() + partmatch.length();
        }

        smatch gearmatch;
        string gearline = line;
        offset = 0;
        while (regex_search(gearline, gearmatch, gear)) {
            engine_gear gear;
            gear.row = row;
            gear.col = gearmatch.position() + offset;

            engine_gears.push_back(gear);

            gearline = gearmatch.suffix().str();
            offset += gearmatch.position() + gearmatch.length();
        }
        row++;
    }

    for (engine_gear& gear : engine_gears)
        for (engine_part& part : engine_parts) {
        {
            if (gear.row <= part.row + 1 && gear.row >= part.row - 1)
            {
                if (gear.col <= part.end + 1 && gear.col >= part.start - 1)
                {
                    gear.adjacent_nums++;
                    gear.ratio *= part.value;
                    if (gear.adjacent_nums > 2) continue;
                }
            }
            
        }
        
    }

    for (engine_gear& gear : engine_gears) {
        if (gear.adjacent_nums == 2) {
            sum += gear.ratio;
        }
    }

    cout << sum << endl;
}