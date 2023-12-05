#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <unordered_set>
#include <cmath>

using namespace std;

regex numbers("(?:Card\\s+\\d+:\\s+)?(\\d+|\\|)");

int main() {

    ifstream file("input.txt");
    string line;

    int sum = 0;

    while (getline(file, line)) {
        smatch match;
        unordered_set<int> ticket_numbers;
        unordered_set<int> winning_numbers;
        int winning_count = 0;
        bool in_winning_numbers = true;
        
        while (regex_search(line, match, numbers)) {
            if (match[1] == "|")
            {
                in_winning_numbers = false;
                line = match.suffix().str();
                continue;
            }

            if (in_winning_numbers)
            {
                winning_numbers.insert(stoi(match[1]));
            }
            else{
                if (winning_numbers.find(stoi(match[1])) != winning_numbers.end())
                {
                    winning_count++;
                }
            }     
            line = match.suffix().str();   
        }

        if (winning_count > 0)
        {
            sum += pow(2, winning_count-1);
        }
    }

    cout << sum << endl;
}