#include <iostream>
#include <string>

using namespace std;

bool isdigit(const char &c);
bool inputIsValid(const string &s);
string trimString(const string &s);
int stringToInteger (const string &s);

int main() {
    cout << "Enter a string: ";
    string input;
    getline(cin, input);

    int number = stringToInteger(input);

    cout << number;

}

bool isdigit(const char &c) {
    return c>='0' && c<='9';
}

bool inputIsValid(const string &s) {
    bool isValid = true;

    for (const char &c : s) {
        if (!isdigit(c)) {
            isValid = false;
            break;
        }
    }

    return isValid;
}

//trims leading spaces and everything after the first non-leading space.
string trimString(const string &s) {
    string trimmed;

    bool firstNonSpaceCharFound = false;

    for (int i = 0; i < s.length(); i++) {
        if (!firstNonSpaceCharFound && s[i] == ' ') {
            continue;
        }
        else if (!firstNonSpaceCharFound && s[i] != ' ') {
            firstNonSpaceCharFound = true;
        }
        
        if (s[i] != ' ') {
            trimmed+= s[i];
        }
        else {
            break;
        }
    }

    return trimmed;
}

int stringToInteger (const string &s) {
    string trimmedInput = trimString(s);
    int number = 0;

    if (!inputIsValid(trimmedInput)) {
        cout << "Invalid input.";
        return -1;
    }

    for (int i = 0; i < trimmedInput.length(); i++) {
        number = number*10 + ((int)trimmedInput[i] - 48);
        //ascii codes of digits 0-9:  48-57.
    }

    return number;
}