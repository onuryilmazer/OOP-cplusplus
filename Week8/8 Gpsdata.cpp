#include <iostream>
#include <string>
#include <vector>
#include <time.h> 
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

class Position {
    private:
        double latitude;
        double longtitude;
        double altitude;
    
    public:
        Position() 
            : latitude(0), longtitude(0), altitude(0) {}

        Position(const double latitude, const double longtitude, const double altitude)
            : latitude(latitude), longtitude(longtitude), altitude(altitude) {}

        Position(const Position& pos) 
            : latitude(pos.latitude), longtitude(pos.longtitude), altitude(pos.altitude) {}

        virtual void print() {
            cout << "Breitengrad: " << latitude << ", Laengengrad: " << longtitude << ", Hoehe: " << altitude <<endl;
        }

        double getLatitude() const {
            return latitude;
        }

        double getLongtitude() const {
            return longtitude;
        }

        double getAltitude() const {
            return altitude;
        }
};

class Wegpunkt : public Position {
    private:
        string name;

    public:
        Wegpunkt() 
            : Position(), name("") {}

        Wegpunkt(const double latitude, const double longtitude, const double altitude, const string& name) 
            : Position(latitude, longtitude, altitude), name(name) {}

        Wegpunkt(const Position& pos, const string& name) 
            : Position(pos), name(name) {}

        Wegpunkt(const Wegpunkt& wp) 
            : Position(wp), name(wp.name) {};

        void print() {
            Position::print();
            cout << "Name: " << name << endl;
        }

        string getName() {
            return name;
        }
};

class Zeitpunkt {
    private:
        static const int unixGpsTimeOffset = 315964800;
        int seconds;  

    public:
        Zeitpunkt()
            : seconds(0) {}

        Zeitpunkt(int seconds)
            : seconds(seconds) {}

        Zeitpunkt(const Zeitpunkt& zp)
            : seconds(zp.seconds) {}

        //ignores leap seconds, output probably drifts btw. 0-20 seconds depending on year (couldn't get std::chrono::gps_clock to work...)
        string getDate() const {        
            time_t unixTimestamp = seconds + unixGpsTimeOffset;
            string date(ctime(&unixTimestamp));
            return date;
        }

        int getSeconds() {
            return seconds;
        }
};

class Trackpunkt : public Position {
    private:
        Zeitpunkt time;

    public:
        Trackpunkt() 
            : Position(), time() {}

        Trackpunkt(const double latitude, const double longtitude, const double altitude, const Zeitpunkt& time) 
            : Position(latitude, longtitude, altitude), time(time) {}

        Trackpunkt(const Position& pos, const Zeitpunkt& time)
            : Position(pos), time(time) {}

        Trackpunkt(const Trackpunkt& tp) 
            : Position(tp), time(tp.time) {}

        void print() {
            Position::print();
            cout << "Datum: " << time.getDate() << endl;
        }

        Zeitpunkt getTime() {
            return Zeitpunkt(time); //a copy.
        }
};

class Track {
    private:
        vector<Trackpunkt> waypoints;

    public:
        Track() 
            : waypoints() {}

        Track(const vector<Trackpunkt>& waypoints) 
            : waypoints(waypoints) {}

        Track(const Track& tr) 
            : waypoints(tr.waypoints) {}

        void print() {
            std::cout.precision(16);
            cout << "Trackpunkte: " << endl;
            for (int i = 0; i < waypoints.size(); i++) {
                waypoints.at(i).print();
            }
        }

        void addTrackpunkt(const Trackpunkt& t) {
            waypoints.push_back(Trackpunkt(t));
        }

        double averageHeight() {
            double sum = 0;
            for (int i = 0; i < waypoints.size(); i++) {
                sum += waypoints.at(i).getAltitude();
            }

            double average = sum / waypoints.size();
            return average;
        }

        void write(string fileName) {
            ofstream textFile;
            textFile.open(fileName, ios::out);  //if exists, old version is deleted.

            while (textFile.fail()) {
                cout << "Die Datei konnte nicht geoeffnet werden.\nGeben Sie einen anderen Namen ein." << endl;
                cin >> fileName;
                textFile.open(fileName, ios::out);
            }

            for (int i = 0; i < waypoints.size(); i++) {
                Trackpunkt& tp = waypoints.at(i);
                stringstream ss;
                ss << setprecision(16) << tp.getLatitude() << " " << tp.getLongtitude() << " " << tp.getAltitude() << " " << tp.getTime().getSeconds() << endl;
                
                textFile << ss.str();
            }

            textFile.close();
        }

        void read(string fileName) {
            ifstream textFile;
            textFile.open(fileName, ios::in);

            while (textFile.fail()) {
                cout << "Die Datei konnte nicht geoeffnet werden.\nGeben Sie einen anderen Namen ein." << endl;
                cin >> fileName;
                textFile.open(fileName, ios::in);
            }

            waypoints.clear();

            string input;
            getline(textFile, input, '\n');

            while(!textFile.fail()) {
                stringstream ss(input);

                double latitude;
                ss >> latitude;
                double longtitude;
                ss >> longtitude;
                double altitude;
                ss >> altitude;
                int seconds;
                ss >> seconds;

                waypoints.push_back(Trackpunkt(latitude, longtitude, altitude, Zeitpunkt(seconds)));

                getline(textFile, input, '\n');
            }

            textFile.close();
        }    
};

int main() {
    Track track1;
    track1.read("track.txt");
    track1.print();
    cout << "Durchschnittshoehe: " << track1.averageHeight() << "\n\n";

    Track track2;
    for (int i = 0; i < 10; i++) {
        Trackpunkt t(50.92098598554814 + i*0.00000000000014, 11.582074254810182 + i*0.00000000000014, 20 + i, Zeitpunkt(1340145771+10*i));
        track2.addTrackpunkt(t);
    }
    track2.print();
    cout << "Durchschnittshoehe: " << track1.averageHeight() << "\n\n";
    track2.write("track2.txt");


    Position coordinates(50.92130714051402, 11.5820752, 20);
    Wegpunkt buschtoilette(coordinates, "Buschtoilette, Paradiespark");
    buschtoilette.print();    
}