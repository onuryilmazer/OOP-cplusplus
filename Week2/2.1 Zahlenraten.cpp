#include <iostream>
#include <cstdlib>
#include <ctime> //to seed the random number generator.

int main() {
    std::srand(std::time(nullptr)); //current time as rng seed.

    std::cout << "Upper limit: ";
    int max;
    std::cin >> max;

    int randomNumber = std::rand() % (max+1);

    int numberOfTries = 0;
    int correctlyGuessed = 0;
    int guess;

    while (!correctlyGuessed) {
        numberOfTries++;

        std::cout << "Guess the number: ";
        std::cin >> guess;

        if (guess == randomNumber) {
            correctlyGuessed = 1;
        }
        else {
            std::cout << "Your number is too " << (guess > randomNumber ? "big" : "small") << ". ";
        }
    }

    std::cout << "It took you " << numberOfTries << " tries to guess " << randomNumber << " correctly." << std::endl;

    return 0;
}