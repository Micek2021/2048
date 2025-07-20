#pragma once

#include "GameSquare.h"
#include "Constants.h"

#include <vector>
#include <set>
#include <string>

class GameBoard {
private:
    std::vector<GameSquare> v_board;
    std::mt19937& c_random_engine;
    std::set<int> s_empty_cells;

public:
    explicit GameBoard(std::mt19937& gen);

    void vStart();

    void vReset();

    void vMove(Direction direction);

    void vOneTurn(Direction dir);

    [[nodiscard]] bool bIsFull() const;

    [[nodiscard]] bool bIsLost() const;

    void vSpawnNewTile();

    void vClearOneSquare(int index);

    //logika wypisywania

    [[nodiscard]] std::string sToString() const;

    friend std::ostream& operator<<(std::ostream& os, const GameBoard& board);
};