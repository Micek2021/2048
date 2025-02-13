#include <iostream>
#include <random>

#include "Constants.h"
#include "GameBoard.h"

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());


    GameBoard board(gen);
    for(int i =0; i<BOARDSIZE; i++) {
        board.vSpawnNewTile();
    }
    std::cout << board;
    std::cout<<board.bIsLost() << std::endl;

    board.vReset();
    std::cout << board;
    std::cout << board.bIsLost() << std::endl;

    board.vStart();
    std::cout << board;
    return 0;
}
