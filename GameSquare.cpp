#include "GameSquare.h"

#include <format>

#include "Constants.h"


GameSquare::GameSquare(std::mt19937 &gen): i_value(0), c_random_engine(gen) {}

GameSquare::GameSquare(int value, std::mt19937 &gen): i_value(value), c_random_engine(gen) {}


void GameSquare::vInitiate() {
    if(std::uniform_real_distribution<double> dist(0.0, 1.0); dist(c_random_engine) > CHANCETOGETFOUR) {
        i_value = 2;
    } else {
        i_value = 4;
    }
}

void GameSquare::vJoin(const GameSquare &other) {
    i_value += other.i_value;
}

std::string GameSquare::sToString() const {
    if (i_value != 0) {
        return std::format("| {:^4} |", i_value);
    } else {
        return "|  __  |";
    }
}


//getters, setters i clear
int GameSquare::iGetValue() const {
    return i_value;
}

void GameSquare::vSetValue(int newValue) {
    i_value = newValue;
}


void GameSquare::vClear() {
    i_value = 0;
}

std::ostream& operator<<(std::ostream& os, const GameSquare& square) {
    return os << square.sToString();
}