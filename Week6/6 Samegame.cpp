#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h> //random number generation.
#include <time.h>   //to seed the random number generator.

using namespace std;

enum Color {RED, GREEN, YELLOW, BLUE, MAGENTA, WHITE, BLACKBG, WHITEBG, NOCOLOR};

string returnColoredTile(Color fgcolor, Color bgcolor, string text) {
    const string RESET = "\033[0m";
    string tile;

    switch (bgcolor) {
        case BLACKBG:
            tile += (string)"\033[0;40m";
            break;

        case WHITEBG:
            tile += (string)"\033[0;47m";
            break;

        default:
            break;
    }

    switch (fgcolor) {
        case RED:
            tile += (string)"\033[1;31m";
            break;
        
        case GREEN:
            tile += (string)"\033[1;32m";
            break;

        case YELLOW:
            tile += (string)"\033[1;33m";
            break;

        case BLUE:
            tile += (string)"\033[1;34m";
            break;

        case MAGENTA:
            tile += (string)"\033[1;95m";
            break;

        case WHITE:
            tile += (string)"\033[1;97m";
            break;

        default:
            break;
    }

    tile += text + RESET;

    return tile;
}

void drawBoard9x9(const vector<vector<Color>> &board, Color backgroundColor, string tileCharacter = "X") {

    for (int i = 0; i < 10; i++) {
        if (i==0) {
            cout << returnColoredTile(WHITE, BLACKBG, "  ");
            for (int j = 0; j < 9; j++) {
                char columnHeaderLetter =(65+j);
                string columnHeader(1,columnHeaderLetter);
                columnHeader += (j < 8 ? " " : "");
                
                cout << returnColoredTile(WHITE, BLACKBG, columnHeader);
            }
            cout << endl;
            continue;
        }

        for (int j = 0; j < 10; j++) {
            if (j==0) {
                cout << returnColoredTile(WHITE, BLACKBG, to_string(i) + " ");
                continue;
            }
            else {
                cout << returnColoredTile(board.at(i-1).at(j-1), backgroundColor, tileCharacter);
            }

            if (j != 9) {
                cout << returnColoredTile(NOCOLOR, backgroundColor, " ");
            }
            else {
                cout << endl;
            }
        }
    }

}

void populateBoard9x9(vector<vector<Color>> &board) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            board[i][j] = (Color)(rand() % 6);
        }
    }
}



string askForInput(const string &prompt) {
    cout << prompt << endl;
    return "";
}

int main(int argc, char** argv) {
    vector<vector<Color>> board(9, vector<Color>(9));
    populateBoard9x9(board);
    drawBoard9x9(board, BLACKBG);


}