#pragma once

#include <random>
#include <string>

class GameSquare {
private:
    int i_value;
    std::mt19937& c_random_engine;
public:
    explicit GameSquare(std::mt19937& gen);

    GameSquare(int value, std::mt19937& gen);

    void vInitiate();

    void vJoin(const GameSquare& other);

    [[nodiscard]] std::string sToString() const;

    //gettery i settery
    [[nodiscard]] int iGetValue() const;

    void vSetValue(int i_value);

    void vClear();

    friend std::ostream& operator<<(std::ostream& os, const GameSquare& square);
};