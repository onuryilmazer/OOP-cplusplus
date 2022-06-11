#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h> //random number generation.
#include <time.h>   //to seed the random number generator.

using namespace std;

enum Color {RED, GREEN, YELLOW, BLUE, MAGENTA, WHITE, BLACKBG, WHITEBG, NOCOLOR};

string returnColoredTile(Color bgColor, Color fgColor=NOCOLOR, string text = " ") {
    const string RESET = "\033[0m";
    string tile;

    switch (bgColor) {
        case RED:
            tile += (string)"\033[1;41m";
            break;
        
        case GREEN:
            tile += (string)"\033[1;42m";
            break;

        case YELLOW:
            tile += (string)"\033[1;43m";
            break;

        case BLUE:
            tile += (string)"\033[1;44m";
            break;

        case MAGENTA:
            tile += (string)"\033[1;105m";
            break;

        case WHITE:
            tile += (string)"\033[1;107m";
            break;

        default:
            break;
    }

    switch (fgColor) {
        default:
            break;
    }

    tile += text + RESET;

    return tile;
}

void drawBoard9x9(const vector<vector<Color>> &board, Color backgroundColor, string tileCharacter = "X") {
    for (int i = 0; i < 10; i++) {
        if (i==0) {
            cout << "  A B C D E F G H I" << endl;
            continue;
        }

        for (int j = 0; j < 10; j++) {
            if (j==0) {
                cout <<  to_string(i) + " ";
                continue;
            }
            

            cout << returnColoredTile(board.at(i-1).at(j-1), NOCOLOR);
            cout << returnColoredTile(board.at(i-1).at(j-1), NOCOLOR);  //x2 width.
            
            if (j == 9) {
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
    string input;
    getline(cin, input);

    return input;
}

vector<int> getCoordinates (const string &userInput) {
    //expected input: C1, D2 etc.
    //ASCII A-I: 65-73.   1-9: 49-57
    char firstLetter = userInput[0];
    char secondLetter = userInput[1];

    
    

    int row = (int)(firstLetter-65);
    //cout << row << " ";
    if (row < 0 || row > 9) {
        throw runtime_error("invalid row");
    }

    int column = (int)(secondLetter - 48);
    //cout << column;
    if (column < 1 || column > 9) {
        throw runtime_error("invalid column");
    }

    vector<int> results;
    results.push_back(row);
    results.push_back(column - 1); //arrays start at 0
    
    return results;
}

vector<int> userPickTilePrompt() {
    vector<int> pickedTile;
    bool inputReceived = false;

    while (!inputReceived) {
        try {
            string userInput = askForInput("Choose a tile (ex: C5):");
            pickedTile = getCoordinates(userInput);
            inputReceived = true;
        }
        catch (exception &e) {
            cout << "Error: " << e.what() << endl;
        }
    }
    
    return pickedTile;
}

int main(int argc, char** argv) {
    vector<vector<Color>> board(9, vector<Color>(9));
    populateBoard9x9(board);
    drawBoard9x9(board, BLACKBG);
    
    vector<int> pickedTile = userPickTilePrompt();

    for (int number : pickedTile) {
        cout << number << " ";
    }
}