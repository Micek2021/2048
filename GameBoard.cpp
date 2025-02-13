#include "GameBoard.h"
#include "Constants.h"

#include <sstream>

GameBoard::GameBoard(std::mt19937 &gen): v_board(), c_random_engine(gen), s_empty_cells() {
    v_board.reserve(BOARDSIZE);
    for (int ii = 0; ii < BOARDSIZE; ii++) {
        v_board.emplace_back(gen);
        s_empty_cells.insert(ii);
    }
}

void GameBoard::vSpawnNewTile() {
        std::uniform_int_distribution<int> dist(0, static_cast<int>(s_empty_cells.size()-1));
        auto rolledSetIndex = std::next(s_empty_cells.begin(), dist(c_random_engine));
        int temp =  *rolledSetIndex;
        s_empty_cells.erase(rolledSetIndex);

        v_board[temp].vInitiate();
        // std::cout << v_board[temp];
}

bool GameBoard::bIsLost() const {
    return s_empty_cells.empty();
}

std::string GameBoard::sToString() const {
    std::ostringstream os;
    for (int ii = 0; ii < ONESIDEOFTHEBOARD; ii++) {
        for (int jj = 0; jj < ONESIDEOFTHEBOARD; jj++) {
            os << v_board[ii * ONESIDEOFTHEBOARD + jj];
        }
        os << "\n";
    }
    return os.str();
}


std::ostream& operator<<(std::ostream& os, const GameBoard& board) {
    return os << board.sToString();
}

void GameBoard::vStart() {
    if (s_empty_cells.empty()) {
        vReset();
    }
    vSpawnNewTile();
    vSpawnNewTile();
}

void GameBoard::vClearOneSquare(const int index) {
    v_board[index].vClear();
    s_empty_cells.insert(index);
}

void GameBoard::vReset() {
    for (int ii = 0; ii < BOARDSIZE; ii++) {
        vClearOneSquare(ii);
    }
}