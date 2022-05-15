#include <iostream>
#include <string>

using namespace std;
void askForBoundaries(int& lowerBound, int& upperBound);
bool askYNQeustion(const string &question);
int tryToGuessNumber(int lowerBound, int upperBound);


int main() {
    int lowerBound, upperBound;
    askForBoundaries(lowerBound, upperBound);    

    int number = tryToGuessNumber(lowerBound, upperBound);
    cout << number << " is the number you had in your mind.";
    return 0;
}

void askForBoundaries(int& lowerBound, int& upperBound) {
    cout << "Enter the lower and upper bounds, both inclusive:\n";
    cin >> lowerBound;
    cin >> upperBound;
    cin.ignore();

    if (lowerBound > upperBound) {
        int temp = lowerBound;
        lowerBound = upperBound;
        upperBound = temp;
    }
}

bool askYNQeustion(const string &question) {
    cout << question << " yes/no\n";
    string answer;
    getline(cin, answer);
    bool answerIsCorrect = answer == "yes";

    return answerIsCorrect;
}

int tryToGuessNumber(int lowerBound, int upperBound) {
    int lengthOfInterval = upperBound - lowerBound;
    int middleIndex = lengthOfInterval / 2;
    int middleNumber = lowerBound + middleIndex;

    string askIfMiddle = "Is your number " + to_string(middleNumber) + "?";
    string askIfLower = "Is your number between " + to_string(lowerBound) + " and " + to_string(middleNumber-1) + " inclusive?";


    if(askYNQeustion(askIfMiddle)) {
        cout << "Found it! ";
        return middleNumber;
    }
    else if (lengthOfInterval == 1) {
        cout << "There is only one other possibility. ";
        return middleNumber+1;
    }
    else if (askYNQeustion(askIfLower)) {
        return tryToGuessNumber(lowerBound, middleNumber-1);
    }
    else {
        return tryToGuessNumber(middleNumber + 1, upperBound);
    }
}