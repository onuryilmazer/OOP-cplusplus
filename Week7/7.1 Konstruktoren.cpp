#include <iostream>

using namespace std;

class Time
{
    private:
        int minuten;

    public:
        virtual void set(const int &h, const int &m)
        {
            minuten = h * 60 + m;
        }

        virtual void get(int &h, int &m)
        {
            h = minuten / 60;
            m = minuten % 60;
        }

        virtual void inc()
        {
            minuten++;
        }

        Time()
        {
            minuten = 0;
            cout << "Default constructor" << endl;
        }

        Time(int minuten)
        {
            this->minuten = minuten;
            //(*this).minuten = minuten;
            cout << "Int type conversion constructor" << endl;
        }

        Time(int stunden, int minuten)
        {
            this->minuten = stunden * 60 + minuten;
            cout << "Two int parameter constructor" << endl;
        }

        Time(const Time &t)
        {
            minuten = t.minuten;
            cout << "Copy constructor" << endl;
        }

        ~Time()
        {
            cout << "Destructor" << endl;
        }
};

void print(Time t) {
    int h, m;
    t.get(h, m);
    cout << h << ":" << m << endl;
}

Time input() {
    Time result; //Standardkonstruktor wird aufgerufen.
    int h, m;
    cout << "Uhrzeit eingeben - Stunde: ";
    cin >> h;
    cout << " Minute: ";
    cin >> m;
    result.set(h, m);
    return result; //Destruktor wird für die lokale Variable "result" aufgerufen.
}

int main(int argc, char *argv[]) {
    Time t1(10, 10); //Konstruktor mit 2 Parametern wird aufgerufen.
    Time t2; //Standardkonstruktor wird aufgerufen.
    t2 = input(); //Kopierkonstruktor wird aufgerufen (Rückgabewert ist vom Typ Time).
    t2.inc(); //Die Funktion Time::inc nimmt t2 als eine Kopie, und nicht als Referenz, daher wird hier die Kopierkonstruktor und danach Destruktor aufgerufen.
    print(t2);
    print(1234); //int 1234 wird implizit konvertiert, daher die Integerwert-Konstruktor aufgerufen.
    return 0; //Alle lokalen Time-Variablen werden zerstört 3x Destruktor.
}