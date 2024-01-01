#include <iostream>

int main()
{
    std::string character;
    std::cout << "Type a character or just press enter." << std::endl;
    std::getline(std::cin, character);
    std::cout << "The value of char as int is: " << ((int)character[0]) << std::endl;

    return 0;
}
