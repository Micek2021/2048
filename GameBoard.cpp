#include "GameBoard.h"

#include <sstream>
#include <algorithm>

GameBoard::GameBoard(std::mt19937 &gen): v_board(), c_random_engine(gen), s_empty_cells() {
    v_board.reserve(BOARDSIZE);
    for (int ii = 0; ii < BOARDSIZE; ii++) {
        v_board.emplace_back(gen);
        s_empty_cells.insert(ii);
    }
}

void GameBoard::vStart() {
    if (s_empty_cells.empty()) {
        vReset();
    }
    vSpawnNewTile();
    vSpawnNewTile();
}

void GameBoard::vReset() {
    for (int ii = 0; ii < BOARDSIZE; ii++) {
        vClearOneSquare(ii);
    }
}

void GameBoard::vMove(Direction direction) {
    bool isHorizontal = (direction == Direction::Left || direction == Direction::Right);
    bool isReversed = (direction == Direction::Right || direction == Direction::Down);

    for (int outer = 0; outer < ONESIDEOFTHEBOARD; ++outer) {
        std::vector<int> values;
        for (int inner = 0; inner < ONESIDEOFTHEBOARD; ++inner) {
            int index = isHorizontal
                            ? (outer * ONESIDEOFTHEBOARD + inner)
                            : (inner * ONESIDEOFTHEBOARD + outer);
            if (isReversed) index = isHorizontal
                                        ? (outer * ONESIDEOFTHEBOARD + (ONESIDEOFTHEBOARD - 1 - inner))
                                        : ((ONESIDEOFTHEBOARD - 1 - inner) * ONESIDEOFTHEBOARD + outer);

            if (v_board[index].iGetValue() != 0) {
                values.push_back(v_board[index].iGetValue());
            }
        }

        std::vector<int> mergedValues;
        for (int i = 0; i < values.size(); ++i) {
            if (i + 1 < values.size() && values[i] == values[i + 1]) {
                mergedValues.push_back(values[i] * 2);
                ++i;
            } else {
                mergedValues.push_back(values[i]);
            }
        }
        mergedValues.resize(ONESIDEOFTHEBOARD, 0);

        if (isReversed) std::ranges::reverse(mergedValues);

        for (int inner = 0; inner < ONESIDEOFTHEBOARD; ++inner) {
            int index = isHorizontal
                            ? (outer * ONESIDEOFTHEBOARD + inner)
                            : (inner * ONESIDEOFTHEBOARD + outer);

            int value = mergedValues[inner];
            if (value == 0) {
                v_board[index].vClear();
                s_empty_cells.insert(index);
            } else {
                v_board[index].vSetValue(value);
                s_empty_cells.erase(index);
            }
        }
    }
}

void GameBoard::vOneTurn(const Direction dir) {
    vMove(dir);
    if (!bIsFull()) {
        vSpawnNewTile();
    }
}

void GameBoard::vSpawnNewTile() {
        std::uniform_int_distribution<int> dist(0, static_cast<int>(s_empty_cells.size()-1));
        auto rolledSetIndex = std::next(s_empty_cells.begin(), dist(c_random_engine));
        int temp =  *rolledSetIndex;
        s_empty_cells.erase(rolledSetIndex);

        v_board[temp].vInitiate();
}

// Used to check if the board is full when evaluating potential valid moves near endgame
bool GameBoard::bIsFull() const{
    return s_empty_cells.empty();
}

std::string GameBoard::sToString() const {
    std::ostringstream os;
    for (int row = 0; row < ONESIDEOFTHEBOARD; row++) {
        for (int col = 0; col < ONESIDEOFTHEBOARD; col++) {
            os << v_board[row * ONESIDEOFTHEBOARD + col];
        }
        os << "\n";
    }
    return os.str();
}


std::ostream& operator<<(std::ostream& os, const GameBoard& board) {
    return os << board.sToString();
}

void GameBoard::vClearOneSquare(const int index) {
    v_board[index].vClear();
    s_empty_cells.insert(index);
}

bool GameBoard::bIsLost() const {
    if (!bIsFull()) return false;

    for (int row = 0; row < ONESIDEOFTHEBOARD; ++row) {
        for (int col = 0; col < ONESIDEOFTHEBOARD; ++col) {
            const int index = row * ONESIDEOFTHEBOARD + col;
            const int currentValue = v_board[index].iGetValue();

            // check right
            if (col < ONESIDEOFTHEBOARD - 1) {
                if (const int rightValue = v_board[index + 1].iGetValue(); currentValue == rightValue) return false;
            }

            if (row < ONESIDEOFTHEBOARD - 1) {
                if (const int downValue = v_board[index + ONESIDEOFTHEBOARD].iGetValue(); currentValue == downValue) return false;
            }
        }
    }

    return true;
}