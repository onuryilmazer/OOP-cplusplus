#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h> //random number generation.
#include <time.h>   //to seed the random number generator.

using namespace std;

enum Color {RED, GREEN, YELLOW, BLUE, MAGENTA, WHITE, BLACKBG, WHITEBG, NOCOLOR};

string returnColoredTile(Color bgColor, string text = " ") {
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

        case NOCOLOR:
            tile += RESET;
            break;

        default:
            break;
    }

    tile += text + RESET;

    return tile;
}

void drawBoard9x9(const vector<vector<Color>> &board) {
    for (int i = 0; i < 10; i++) {
        if (i==0) {
            cout << "  1 2 3 4 5 6 7 8 9" << endl;
            continue;
        }

        for (int j = 0; j < 10; j++) {
            if (j==0) {
                char letter = (i+64);
                cout << letter << " ";
                continue;
            }
            

            cout << returnColoredTile(board.at(i-1).at(j-1), " ");
            cout << returnColoredTile(board.at(i-1).at(j-1), " ");  //outputting twice for x2 width.
            
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

vector<int> calculateCoordinates (const string &userInput) {
    //expected input: C1, D2 etc. Row-Column.
    //ASCII A-I: 65-73.   1-9: 49-57
    char firstLetter = userInput[0];
    char secondLetter = userInput[1];

    int row = (int)(firstLetter-65); //A-I
    if (row < 0 || row > 8) {
        throw runtime_error("invalid column");
    }

    int column = (int)(secondLetter - 49);  //1-9 to 0-8
    if (row < 0 || row > 8) {
        throw runtime_error("invalid row");
    }

    vector<int> results;
    results.push_back(row);
    results.push_back(column);
    
    return results;
}

vector<int> userPickTilePrompt() {  //returns column, row
    vector<int> pickedTile;
    bool correctInputReceived = false;

    while (!correctInputReceived) {
        try {
            string userInput = askForInput("Choose a tile (ex: C5):");
            pickedTile = calculateCoordinates(userInput);
            correctInputReceived = true;
        }
        catch (exception &e) {
            cout << "Error: " << e.what() << endl;
        }
    }
    
    return pickedTile;  //row, column.
}

vector<vector<int>> searchNeighboringSameColorTiles (int row, int column, vector<vector<Color>> board) {
    vector<vector<int>> listOfMatchingTileIndices(0, vector<int>(2));

    int nrOfTilesAbove = row;
    int nrOfTilesBelow = 8-row;
    int nrOfTilesLeft = column;
    int nrOfTilesRight = 8-column;

    Color pickedColor = board[row][column];

    if (pickedColor == NOCOLOR) {
        cout << "Empty tile selected." << endl;
        return listOfMatchingTileIndices;
    }

    for (int i = 1; i <= nrOfTilesAbove; i++) {
        if (pickedColor == board[row-i][column]) {
            vector<int> tile;
            tile.push_back(row-i);
            tile.push_back(column);
            listOfMatchingTileIndices.push_back(tile);
        }
        else {
            break;
        }
    }

    for (int i = 1; i <= nrOfTilesBelow; i++) {
        if (pickedColor == board[row+i][column]) {
            vector<int> tile;
            tile.push_back(row+i);
            tile.push_back(column);
            listOfMatchingTileIndices.push_back(tile);
        }
        else {
            break;
        }
    }

    for (int i = 1; i <= nrOfTilesLeft; i++) {
        if (pickedColor == board[row][column-i]) {
            vector<int> tile;
            tile.push_back(row);
            tile.push_back(column-i);
            listOfMatchingTileIndices.push_back(tile);
        }
        else {
            break;
        }
    }

    for (int i = 1; i <= nrOfTilesRight; i++) {
        if (pickedColor == board[row][column+i]) {
            vector<int> tile;
            tile.push_back(row);
            tile.push_back(column+i);
            listOfMatchingTileIndices.push_back(tile);
        }
        else {
            break;
        }
    }

    if (listOfMatchingTileIndices.size() > 0) {  //the tile itself has to be removed along with its neighbors.
        vector<int> tile;
        tile.push_back(row);
        tile.push_back(column);
        listOfMatchingTileIndices.push_back(tile);
    }

    return listOfMatchingTileIndices;
}

vector<int> determineEmptyColumns(const vector<vector<Color>> &board) {
    vector<int> emptyColumns;

    for (int i = 0; i < board.at(0).size(); i++) { //traversing columns, based on 1st row's number of elements.
        bool columnEmpty = true;

        for (int j = 0; j < board.size(); j++) { //height of board, based on number of rows.
            if (board.at(j).at(i) != NOCOLOR) {
                columnEmpty = false;
                break;
            }
        }

        if (columnEmpty) {
            emptyColumns.push_back(i);
        }
    }

    return emptyColumns;
}

void shiftColumnsToLeft(vector<vector<Color>> &board, int beginningColumnIndex) {
    //# rows: board.size()
    //# columns: board.at(x).size()
    for(int i = beginningColumnIndex+1; i < board.at(0).size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            //color to prev (empty) column, this color empty, move on to next column.
            board.at(j).at(i-1) = board.at(j).at(i);
            board.at(j).at(i) = NOCOLOR;
        }
    }
}

void shiftTilesDown(vector<vector<Color>> &board) {
    //starting from last row, traversing rows up
    //find the first non-empty above each element and bring it down (update the original NOCOLOR)

    int nrOfRows = board.size();
    int nrOfColumns = board.at(0).size();

    for (int i = nrOfRows -1; i >= 0; i--) { //i: row.
        for (int j = nrOfColumns-1; j >= 0; j--) { //j: column.
            if (board[i][j] != NOCOLOR) {
                continue;
            }

            int upperTileRow = j-1;
            while (upperTileRow > 0 && board[upperTileRow][j] == NOCOLOR) {
                upperTileRow--;
            }

            if (board[upperTileRow][j] != NOCOLOR) {
                cout << "shifting down: " << upperTileRow << ", " << j << endl;
                board[i][j] = board[upperTileRow][j];
                board[upperTileRow][j] = NOCOLOR;
            }
        }
    }
}

void deleteTiles(vector<vector<int>> tileCoordinates, vector<vector<Color>> &board) {
    //approach:
    //mark all given tiles NOCOLOR
    //check if any empty columns exist
        //if so, shift columns to the right of it to the left.
    //starting from the bottom, shift filled tiles down

    for (int i = 0; i < tileCoordinates.size(); i++) {
        board.at(tileCoordinates.at(i).at(0)).at(tileCoordinates.at(i).at(1)) = NOCOLOR;
    }

    vector<int> emptyColumns = determineEmptyColumns(board);

    for (int i = emptyColumns.size(); i > 0; i--) {  //starting from last empty column, fill the blank columns.
        int currentColumn = emptyColumns.at(i-1);
        shiftColumnsToLeft(board, currentColumn);
    }

    shiftTilesDown(board);
}

void createEmptyColumn (vector<vector<Color>> &board, int columnIndex) { //for debugging purposes.
    for (int i = 0; i < board.size(); i++) {
        board.at(i).at(columnIndex) = NOCOLOR;
    }
}


//coordinate format: row, column. Ex: A1.
int main() {
    vector<vector<Color>> board(9, vector<Color>(9));
    populateBoard9x9(board);

    //createEmptyColumn(board, 5);  //for debugging purposes. 

    drawBoard9x9(board);

    while(true) {
        vector<int> pickedTile = userPickTilePrompt();

        cout << "Chosen tile's row index: " << pickedTile.at(0) << " column index: " << pickedTile.at(1) << endl;

        vector<vector<int>> neighbors = searchNeighboringSameColorTiles(pickedTile.at(0),pickedTile.at(1),board);

        cout << "Matching neighbors: \n";

        for (int i = 0; i < neighbors.size(); i++) {
            cout << "Row: " << neighbors.at(i).at(0) << ", Column: " << neighbors.at(i).at(1) << endl;
        }

        deleteTiles(neighbors, board);

        drawBoard9x9(board);
    }
}