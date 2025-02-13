#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#pragma once

#include "GameSquare.h"

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

    [[nodiscard]] bool bIsLost() const;

    void vSpawnNewTile();

    void vOneTurn();

    void vReset();

    void vClearOneSquare(int index);

    //logika poruszania
    void vMove();

    void vMoveLeft();

    void vMoveRight();

    void vMoveUp();

    void vMoveDown();

    //logika wypisywania

    [[nodiscard]] std::string sToString() const;

    friend std::ostream& operator<<(std::ostream& os, const GameBoard& board);
};



#endif //GAMEBOARD_H
