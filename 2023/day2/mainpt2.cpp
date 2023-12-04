#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int main() {
    int redmax, greenmax, bluemax;
    int red, green, blue;
    int sum  = 0;

    regex red_regex("(\\d+)\\s+red");
    regex green_regex("(\\d+)\\s+green");
    regex blue_regex("(\\d+)\\s+blue");

    ifstream file("input.txt");
    string game;

    while (getline(file, game)) {

        int redmax = 0;
        int greenmax = 0;
        int bluemax = 0;


        smatch match;

        cout << game << endl;

        string red_game = game;
        while (regex_search(red_game, match, red_regex)) {
            red = stoi(match[1]);
            if (red > redmax) {
                redmax = red;
            }
            red_game = match.suffix().str();
        }
        string green_game = game;
        while (regex_search(green_game, match, green_regex)) {
            green = stoi(match[1]);
            if (green > greenmax) {
                greenmax = green;
            }
            green_game = match.suffix().str();
        }
        string blue_game = game;
        while (regex_search(blue_game, match, blue_regex)) {
            blue = stoi(match[1]);
            if (blue > bluemax) {
                bluemax = blue;
            }
            blue_game = match.suffix().str();
        }
        cout << redmax << " " << greenmax << " " << bluemax << endl;
        sum += redmax*greenmax*bluemax;
    }

    cout << sum << endl;

}

