#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <unordered_set>
#include <cmath>

using namespace std;

regex numbers("(?:Card\\s+\\d+:\\s+)?(\\d+|\\|)");

vector<int> card_count(200, 0);


int main() {

    ifstream file("input.txt");
    string line;

    int sum = 0;
    int curr_card = 0;

    while (getline(file, line)) {
        smatch match;
        unordered_set<int> winning_numbers;
        int matching = 0;
        bool in_winning_numbers = true;
        card_count[curr_card]++;

        
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
                    matching++;
                }
            }     
            line = match.suffix().str();   
        }

        for (int i = 0; i < matching; i++)
        {
            card_count[curr_card + i + 1] += card_count[curr_card];
        }
        curr_card++;
    }

    int temp = 1;
    for (int num : card_count)
    {
        cout << "Card " << temp << ": " << num << endl;
        sum += num;
        temp++;
    }

    cout << sum << endl;
}