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

vector<engine_part> engine_parts;
vector<pair<int, int>> engine_symbols;

regex numbers("(\\d+)");
regex symbols("[^0-9.\n]+");

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

        smatch symbolmatch;
        string symbolline = line;
        offset = 0;
        while (regex_search(symbolline, symbolmatch, symbols)) {
            engine_symbols.push_back(make_pair(row, symbolmatch.position() + offset));

            symbolline = symbolmatch.suffix().str();
            offset += symbolmatch.position() + symbolmatch.length();
        }
        row++;
    }

    for (engine_part& part : engine_parts) {
        for (pair<int, int>& symbol : engine_symbols)
        {
            if (symbol.first <= part.row + 1 && symbol.first >= part.row - 1)
            {
                if (symbol.second <= part.end + 1 && symbol.second >= part.start - 1)
                {
                    if (!part.counted){
                        sum += part.value;
                        part.counted = true;
                    }
                    continue;
                }
            }
            
        }
        
    }

    cout << sum << endl;
}