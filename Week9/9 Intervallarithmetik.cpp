#include <iostream>
#include <utility> //swap()
#include <string>
#include <sstream>

template<typename T> class Interval {
    private:
        T lowerBound;
        T upperBound;
        bool intervalIsValid;

        bool swapIllegalBounds(T& lowerBound, T& upperBound) {
            if (lowerBound > upperBound) {
                std::swap(lowerBound, upperBound);
                return true;
            }
            else { return false; }
        }
    
    public:
        Interval() : lowerBound(), upperBound(), intervalIsValid(false) {}

        Interval(T lowerBound, T upperBound) {
            intervalIsValid = true;

            if (swapIllegalBounds(lowerBound, upperBound)) {
                //std::cout << "Swapped lower/upper bounds." << std::endl;
            }

            this->lowerBound = lowerBound;
            this->upperBound = upperBound;

        }

        Interval(T lowerAndUpperBounds) {
            Interval(lowerAndUpperBounds, lowerAndUpperBounds);
        }

        bool isValid() const {
            return intervalIsValid;
        }

        T getLowerBound() const {
            if (!isValid()) {
                throw "Invalid Interval.";
            }
            return lowerBound;
        }

        T getUpperBound() const {
            if (!isValid()) {
                throw "Invalid Interval.";
            }
            return upperBound;
        }

        //getter with output parameters.
        void getIntervalBounds(T& lowerBoundOut, T& upperBoundOut) const {
            if (!isValid()) {
                throw "Invalid Interval.";
            }
            
            lowerBoundOut = getLowerBound();
            upperBoundOut = getUpperBound();
        }

        void setIntervalBounds(T lowerBound, T upperBound) {
            if (swapIllegalBounds(lowerBound, upperBound)) {
                //std::cout << "Swapped lower/upper bounds." << std::endl;
            }

            this->lowerBound = lowerBound;
            this->upperBound = upperBound;

            intervalIsValid = true;
        }

        std::string toString() const {
            std::ostringstream out;
            out << "[" << getLowerBound() << ", " << getUpperBound() << "]" << std::endl;

            return out.str();
        }

        void printInterval() const {
            if (isValid()) {
                std::cout << toString() << std::endl;
            }
            else {
                std::cout << "Invalid interval." << std::endl;
            }
            
        }

        Interval<T> operator+(const Interval<T>& i) const {
            if (!isValid() || !(i.isValid()) ) {
                Interval<T> newInterval;
                return newInterval;
            }

            Interval<T> newInterval(getLowerBound() + i.getLowerBound(), getUpperBound() + i.getUpperBound());
            return newInterval;       
        }

        Interval<T> operator-(const Interval<T>& i) const {
            if (!isValid() || !(i.isValid()) ) {
                Interval<T> newInterval;
                return newInterval;
            }

            Interval<T> newInterval(getLowerBound() - i.getLowerBound(), getUpperBound() - i.getUpperBound());
            return newInterval; 
        }

        Interval<T> operator-() const {
            if (!isValid()) {
                Interval<T> newInterval;
                return newInterval;
            }

            Interval<T> newInterval( (-1) * getUpperBound(), (-1) * getLowerBound() );
            return newInterval; 
        }

        Interval<T> operator*(const Interval<T>& i) const {
            if (!isValid() || !(i.isValid()) ) {
                Interval<T> newInterval;
                return newInterval;
            }

            Interval<T> newInterval(getLowerBound() * i.getLowerBound(), getUpperBound() * i.getUpperBound());
            return newInterval; 
        }

        Interval<T> operator/(const Interval<T>& i) const {
            if (!isValid() || !(i.isValid()) || i.getLowerBound() == 0 || i.getUpperBound() == 0) {
                Interval<T> newInterval;
                return newInterval;
            }

            Interval<T> newInterval(getLowerBound() / i.getLowerBound(), getUpperBound() / i.getUpperBound());
            return newInterval; 
        }
};


int main(int argc, char** argv) {
    Interval<double> i1(2.0, 3.0);
    Interval<double> i2(3, 4);
    Interval<double> i3 = i1 + i2;
    i1.printInterval();
    i2.printInterval();
    i3.printInterval();


    i3 = -i3;  
    i3.printInterval();


    i1.setIntervalBounds(-2,1);
    i2.setIntervalBounds(3,4);
    i3 = i1 * i2;
    i3.printInterval();

    i2.setIntervalBounds(1,0);
    i3 = i1 / i2;
    std:: cout << "Division with 0 - i3 is valid: " << (i3.isValid() ? "true" : "false") << std::endl;

    Interval<double> i4 = i3 + i2;
    std:: cout << "Addition with invalid interval - i4 is valid: " << (i4.isValid() ? "true" : "false") << std::endl;

    //usw...

}