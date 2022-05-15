#include <iostream>

//function declarations.
bool simplifyFraction(int &numerator, int &denominator);
int findGreatestCommonDivisor(int number1, int number2);
void fixDenominatorsSign(int &numerator, int &denominator);
bool fractionIsValid(int denominator);

int main() {

    int numerator=1, denominator=1;

    while(true) {
        std::cout << "Enter the numerator and the denominator to simplify the fraction: \n";
        std::cin >> numerator;
        std::cin >> denominator;

        if (!fractionIsValid(denominator)) {
            std::cout << "Invalid fraction.\n";
            continue;
        }

        if (simplifyFraction(numerator, denominator)) {
            std::cout << "The simplified fraction is: " << numerator << "/" << denominator << "\n";
        }
        else {
            std::cout << "The fraction " << numerator << "/" << denominator << " is already in its simplest terms.\n";
        }

    }
}

bool simplifyFraction(int &numerator, int &denominator) {
    fixDenominatorsSign(numerator, denominator);
    int greatestCommonDivisor = findGreatestCommonDivisor(numerator, denominator);
    bool fractionSimplified = false;

    if (greatestCommonDivisor > 1) {
        fractionSimplified = true;
        numerator/=greatestCommonDivisor;
        denominator/= greatestCommonDivisor;
    }

    return fractionSimplified;
}

int findGreatestCommonDivisor(int number1, int number2) {
    int smaller = number1 < number2 ? number1 : number2;
    int greatestCommonDivisor = 1;  //this is guaranteed to be true for any number.

    for (int i = 1; i <= smaller; i++) {
        if (number1 % i == 0 && number2 % i == 0) {
            greatestCommonDivisor = i;
        }
    }

    return greatestCommonDivisor;
} 

void fixDenominatorsSign(int &numerator, int &denominator) {
    if (denominator < 0) { //covers case1: both negative. case2: only denominator negative. 
        numerator *= -1;
        denominator *= -1;
    }
}

bool fractionIsValid(int denominator) {
    return denominator != 0 ? true : false;
}