#include <iostream>
#include <limits>

int main() {

    std::cout << "Properties of arithmetic types:\n";
    std::cout << "Default char:\t\t\t" << sizeof(char) << " bytes, Range: " << +std::numeric_limits<char>::min() << " to " << +std::numeric_limits<char>::max() << "\n";
    std::cout << "Signed char:\t\t\t" << sizeof(signed char) << " bytes, Range: " << +std::numeric_limits<signed char>::min() << " to " << +std::numeric_limits<signed char>::max() << "\n";
    std::cout << "Unsigned char:\t\t\t" << sizeof(unsigned char) << " bytes, Range: " << +std::numeric_limits<unsigned char>::min() << " to " << +std::numeric_limits<unsigned char>::max() << "\n\n";

    std::cout << "Short integer:\t\t\t" << sizeof(short int) << " bytes, Range: " << std::numeric_limits<short int>::min() << " to " << std::numeric_limits<short int>::max() << "\n";
    std::cout << "Unsigned short integer:\t\t" << sizeof(unsigned short int) << " bytes, Range: " << std::numeric_limits<unsigned short int>::min() << " to " << std::numeric_limits<unsigned short int>::max() << "\n\n";

    std::cout << "Integer:\t\t\t" << sizeof(int) << " bytes, Range: " << std::numeric_limits<int>::min() << " to " << std::numeric_limits<int>::max() << "\n";
    std::cout << "Unsigned Integer:\t\t" << sizeof(unsigned int) << " bytes, Range: " << std::numeric_limits<unsigned int>::min() << " to " << std::numeric_limits<unsigned int>::max() << "\n\n";
    
    std::cout << "Long integer:\t\t\t" << sizeof(long int) << " bytes, Range: " << std::numeric_limits<long int>::min() << " to " << std::numeric_limits<long int>::max() << "\n";
    std::cout << "Unsigned long integer:\t\t" << sizeof(unsigned long int) << " bytes, Range: " << std::numeric_limits<unsigned long int>::min() << " to " << std::numeric_limits<unsigned long int>::max() << "\n\n";

    std::cout << "Long^2 integer:\t\t\t" << sizeof(long long int) << " bytes, Range: " << std::numeric_limits<long long int>::min() << " to " << std::numeric_limits<long long int>::max() << "\n";
    std::cout << "Unsigned long^2 integer:\t" << sizeof(unsigned long long int) << " bytes, Range: " << std::numeric_limits<unsigned long long int>::min() << " to " << std::numeric_limits<unsigned long long int>::max() << "\n\n";

    return 0;
}
