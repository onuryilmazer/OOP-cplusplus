#include <iostream>

int main() {
    int a = 5;
    int b = 2;
    double c = b; 

    //Expression 1: Value=2, Type: Double. Reason: Implicit conversion.
    std::cout << c << ": " << typeid(c).name() << std::endl;

    //Expression 2: Value=22, Type: Float. Reason: Negatives cancel (basic math) and subtracting a float from an int results in a float. 
    std::cout << (a * b - - - - - - 12.0f) << ": " << typeid(a * b - - - - - - 12.0f).name() << std::endl;

    //Expression 3: Value=1, Type: Double. 
    //Reason: Operations are done left to right when they have the same priority. And (int/int)/double results in int/double which results in double.
    std::cout << (a / b / c) << ": " << typeid(a / b / c).name() << std::endl;

    //Expression 4: Value:1.25 Type: Double.
    //Reason: Same as in expression 3. (int/double)/int --> double/int --> double.
    std::cout << (a / c / b) << ": " << typeid(a / c / b).name() << std::endl;

    //Expression 5: Value: 0. Type: Double.
    //Reason: float - (int)*(double) + int/int =  float - double + int = double.
    std::cout << (-1.0f - a*2E-1 + a / 2) << ": " << typeid(-1.0f - a*2E-1 + a / 2).name() << std::endl;

    //Expression 5: Value: -14. Type: Double.
    //Reason: The part inside the parentheses is -15 and when added to the double literal 1.0, it results in the expression -14.0
    std::cout << ( 1.0 + (a *= (2 / - b - (c += .0E2))) ) << ": " << typeid( 1.0 + (a *= (2 / - b - (c += .0E2))) ).name() << std::endl;

    return 0;
}