#include <iostream>
#include <vector>
#include <limits> //min-max
#include <cmath> //sqrt

using namespace std;

double max(const vector<double> &v);
bool allPositive(const vector<double> &v);
double product(const vector<double> &v1, const vector<double> &v2);  //scalar prod.
vector<double> product(const vector<double> &v, double f);  //scalar multiplication
double norm(const vector<double> &v); 
void normalize(vector<double> &v);
void populateVector(vector<double> &v);
void printVectorOnConsole(const vector<double> &v);


int main() {
    vector<double> v1;
    populateVector(v1);

    vector<double> v2;
    populateVector(v2);
    
    cout << "Vector 1: ";
    printVectorOnConsole(v1);
    cout << "Vector 2: ";
    printVectorOnConsole(v2);

    cout << "\nMaximum values of both vectors: " << max(v1) << ", " << max(v2) << "\n";
    
    cout << "Whether if all values are positive: " 
         << (allPositive(v1) ? "v1: all positive " : "v1: negatives exist ") << (allPositive(v2) ? "v2: all positive" : "v2: negatives exist") << "\n";

    cout << "Scalar product of two vectors:" << product(v1, v2) << "\n";
    cout << "Product of vector1 with scalar value 5: "; printVectorOnConsole(product(v1, 5)); cout << "\n";
    cout << "Magnitudes of both vectors: " << norm(v1) << ", " << norm(v2) << "\n";
    
    cout << "Normalized versions of both vectors: "; 
    normalize(v1); 
    normalize(v2);
    cout << "\nVector 1: "; printVectorOnConsole(v1); 
    cout << "\nVector 2: "; printVectorOnConsole(v2);
    
}


void populateVector(vector<double> &v) {
    cout << "Input the components of your vector\n"
    "Enter any non-numerical input to stop adding components.\n";

    string input;

    while (true) {
        try {
            getline(cin, input);
            v.push_back(stod(input));
        }
        catch (const invalid_argument &e) {
            
            break;
        }
        catch (const out_of_range &e) {
            cout << "Entry out of range for double, ignoring it\n";
            continue;
        }
    }
}

void printVectorOnConsole(const vector<double> &v) {
    for(double component : v) {
        cout << "{" << component << "} ";
    }
}

double max(const vector<double> &v) {
    double max = numeric_limits<unsigned long long int>::min();

    for(double component : v) {
        if (component > max) {
            max = component;
        }
    }

    return max;
}

bool allPositive(const vector<double> &v) {
    bool allPositive = true;
    
    for(double component : v ) {
        if (component <= 0) { //0 is nonnegative, but not positive.
            allPositive = false;
        }
    }

    return allPositive;
}

double product(const vector<double> &v1, const vector<double> &v2) {  //scalar prod.
    double product = 0;
    if (v1.size() != v2.size()) {
        throw invalid_argument("The scalar product operation is only defined for vectors of same dimension.");
    }

    for(unsigned int i = 0; i < v1.size(); i++) {
        product += v1[i]*v2[i];
    }

    return product;
}

vector<double> product(const vector<double> &v, double f) { //scalar multiplication
    vector<double> scalarProduct;
    for(double component : v) {
        scalarProduct.push_back(f*component);
    }

    return scalarProduct;
}

double norm(const vector<double> &v) {
    double sumOfSquares = 0;

    for (double component : v) {
        sumOfSquares += component*component;
    }

    return sqrt(sumOfSquares);
}

void normalize(vector<double> &v) {
    double magnitudeOfVector = norm(v);

    for(double &component : v) {
        component = component / magnitudeOfVector;
    }
}