#include <iostream>
#include <vector>

using namespace std;

class IntMenge {
    private:
        vector<bool> menge;
        int min;
        int max;
        int anzahlDerElemente;

    public:
        IntMenge(int min, int max) {
            if (min > max) {
                cerr << "Die untere Schranke muss groesser als die obere Schranke sein. Die Werte werden ausgetauscht." << endl;
                int tmp = min;
                min = max;
                max = tmp;
            }

            this->min = min;
            this->max = max;

            anzahlDerElemente = 0;
            menge.resize(max-min+1, false);             
        }

        bool isValid(int i) {
            return (i >= min && i <= max);
        }

        void add(int i) {
            if (!isValid(i)) {
                cerr << "Die Zahl befindet sich nicht in dem gueltigen Wertebereich." << endl;
                return;
            }

            if(menge.at(i-min)) {
                cerr << "Die Zahl befindet sich bereits in der Menge." << endl;
            }
            else {
                menge.at(i-min) = true;
                anzahlDerElemente++;
            }
        }

        void remove(int i) {
            if (!isValid(i)) {
                cerr << "Die Zahl befindet sich nicht in dem gueltigen Wertebereich." << endl;
                return;
            }

            if(!menge.at(i-min)) {
                cerr << "Die Zahl befindet sich nicht in der Menge." << endl;
            }
            else {
                menge.at(i-min) = false;
                anzahlDerElemente--;
            }
        }

        bool contains(int i) {
            return menge.at(i-min);
        }

        bool isEmpty() {
            return (anzahlDerElemente == 0);
        }

        int getSize() {
            return anzahlDerElemente;
        }

        vector<int> getElements() {
            vector<int> elements;
            for (int i = 0; i < menge.size(); i++) {
                if (menge.at(i)) {
                    elements.push_back(i+min);
                }
            }
            return elements;
        }

        void print() {
            cout << "Elemente: ";
            for (int i = 0; i < menge.size(); i++) {
                if (menge.at(i)) {
                    cout << i + min << " ";
                }
            }
            cout << endl;
        }
};

int main()
{
    IntMenge m(10,100);
    int input;
    std::cin >> input;

    while ( input != 0 ) {
        //if ( m.isValid(input) ) { //Meine Implementierung von IntMenge::add kontrolliert bereits, ob Eingabe gueltig ist. Dies ist daher nicht benoetigt.
            m.add(input);
        //}

        std::cout << "Menge enthaelt " << m.getSize() << " Elemente:" << std::endl;
        m.print();
        std::cin >> input;
    }
    std::vector<int> intv = m.getElements();
    for ( int i=0; i<intv.size(); i++ ) {
        m.remove(intv[i]);
    }

    std::cout << (m.isEmpty() ? "Menge ist leer" : "Menge ist nicht leer") << std::endl;
}