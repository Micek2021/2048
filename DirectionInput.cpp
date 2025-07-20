#include "DirectionInput.h"

#include <iostream>

#ifdef _WIN32
#include <cstdlib>
#include <limits>

Direction dirGetDirectionFromInput() {
    char ch;
    while (true) {
        std::cout << "Podaj kierunek:" << std::endl;
        std::cin >> ch;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (ch) {
            case 'w': case 'W': return Up;
            case 's': case 'S': return Down;
            case 'a': case 'A': return Left;
            case 'd': case 'D': return Right;
            case 'p': case 'P': std::exit(0);
            default: std::cout << "Wykryto niepoprawny kierunek!\n";
        }
    }
}
#endif