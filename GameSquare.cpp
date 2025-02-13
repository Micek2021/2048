#include "GameSquare.h"

#include <format>

#include "Constants.h"


GameSquare::GameSquare(std::mt19937 &gen): i_value(0), b_is_taken(false), c_random_engine(gen) {}

GameSquare::GameSquare(int value, std::mt19937 &gen): i_value(value), b_is_taken(true), c_random_engine(gen) {}


void GameSquare::vInitiate() {
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    if(dist(c_random_engine) > CHANCETOGETFOUR) {
        i_value = 2;
    } else {
        i_value = 4;
    }
    b_is_taken = true;
}

void GameSquare::vJoin(const GameSquare &other) {
    i_value += other.i_value;
}

std::string GameSquare::sToString() const {
    if (b_is_taken) {
        return std::format("| {:^4} |", i_value);
    } else {
        return "|  __  |";
    }
}


//gettery i clear
int GameSquare::iGetValue() const {
    return i_value;
}

bool GameSquare::bGetIsTaken() const {
    return b_is_taken;
}

void GameSquare::vClear() {
    i_value = 0;
    b_is_taken = false;
}

std::ostream& operator<<(std::ostream& os, const GameSquare& square) {
    return os << square.sToString();
}