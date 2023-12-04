#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

const int MAXRED = 12;
const int MAXGREEN = 13;
const int MAXBLUE = 14;

int main() {
    int red = 0;
    int green = 0;
    int blue = 0;

    regex red_regex("(\\d+)\\s+red");
    regex green_regex("(\\d+)\\s+green");
    regex blue_regex("(\\d+)\\s+blue");

    int sum  = 0;

    ifstream file("input.txt");
    string game;

    while (getline(file, game)) {
        bool possible = true;
        cout << game << endl;

        smatch match;

        string red_game = game;
        while (regex_search(red_game, match, red_regex)) {
            red = stoi(match[1]);
            if (red > MAXRED) {
                possible = false;
                break;
            }
            red_game = match.suffix().str();
        }
        string green_game = game;
        while (regex_search(green_game, match, green_regex)) {
            green = stoi(match[1]);
            if (green > MAXGREEN) {
                possible = false;
                break;
            }
            green_game = match.suffix().str();
        }
        string blue_game = game;
        while (regex_search(blue_game, match, blue_regex)) {
            blue = stoi(match[1]);
            if (blue > MAXBLUE) {
                possible = false;
                break;
            }
            blue_game = match.suffix().str();
        }
        if (possible) {
            sum += stoi(game.substr(game.find("Game") + 5, game.find(":") - 1));
            cout << "Possible" << endl;
        }
    }

    cout << sum << endl;

}

