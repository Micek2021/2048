#include "GameLoop.h"
#include "GameBoard.h"
#include "DirectionInput.h"

#include <iostream>
#include <random>

void GameLoop::runGame() {
    std::random_device rd;
    std::mt19937 gen(rd());

    GameBoard board(gen);
    board.vStart();
    std::cout<<"Game Start"<<std::endl;

    while (!board.bIsLost()) {
        std::cout<<board<<std::endl;
        board.vOneTurn(dirGetDirectionFromInput());
    }

    std::cout << board << std::endl;
    std::cout<<"Game End"<<std::endl;
}