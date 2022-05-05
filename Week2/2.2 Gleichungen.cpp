#include <iostream>
#include <cmath>

int main() {
    std::cout << "ax^2 + bx + c = 0\n" << "Coefficients a, b, c:\n";
    double a, b, c;
    std::cin >> a >> b >> c;

    double discriminant = (b*b) - 4*a*c;
    std::cout << "Discriminant: " << discriminant << std::endl;

    if (discriminant < 0) {
        std::cout << "The equation has no real roots.";
        return 0;
    }

    discriminant = sqrt(discriminant);

    double root1 = ((-1)*b + discriminant)/(2*a);
    std::cout << "Equation: " << a <<"x^2 + " << b << "x + " << c << "\n" << "Root(s): " << root1;
    
    if (discriminant>0) {
        double root2 = ((-1)*b - discriminant)/(2*a);
        std::cout << ", " << root2 << std::endl;
    }

    return 0;
}