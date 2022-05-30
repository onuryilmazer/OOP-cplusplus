#include <iostream>
#include <vector>
#include <string>

using namespace std;

void bubbleSort(vector<string *> &strings) {
    for(int i = 0; i < strings.size(); i++) {
        int noComparisons = 1;
        
        for (int j = 0; j < strings.size()-1-i; j++) {
            if (*(strings[j]) > *(strings[j+1])) {
                string* temp = strings[j+1];
                strings[j+1] = strings[j];
                strings[j]=temp;
                noComparisons=0;
            }
        }
        
        if (noComparisons==1) 
            break;
    }
}

vector<string *> createPointerArray(vector<string> &strings) {
    vector<string *> pointers;
    for (string &text : strings) {
        pointers.push_back(&text);
    }
    
    return pointers;
}

void printVector(vector<string *> &strings) {
    for(string *&text : strings) {
        cout << *text << " ";
    }
}

int main() {
    vector<string> letters;
    for (int i = 90; i >=65; i--) {
        letters.push_back(string(1, (char)i)); //letters z to a.
    }

    letters.push_back("x");

    vector<string*> pointers = createPointerArray(letters);
    bubbleSort(pointers);
    printVector(pointers);
}