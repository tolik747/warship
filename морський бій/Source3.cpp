#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int BOARD_SIZE = 10;

class Ship {
public:
    Ship(int size) : size(size), hits(0) {}
    bool isSunk() const {
        return hits == size;
    }
    void hit() {
        ++hits;
    }
private:
    int size;
    int hits;
};

class Board {
public:
    Board() {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            board.push_back(vector<bool>(BOARD_SIZE, false));
        }
    }
    bool hasShip(int x, int y) const {
        return board[x][y];
    }
    bool fire(int x, int y) {
        if (hasShip(x, y)) {
            ships[x][y].hit();
            board[x][y] = false;
            return true;
        }
        return false;
    }
    bool addShip(int x, int y, int size, bool horizontal) {
        if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
            return false;
        }
        if (horizontal && x + size > BOARD_SIZE) {
            return false;
        }
        if (!horizontal && y + size > BOARD_SIZE) {
            return false;
        }
        for (int i = 0; i < size; ++i) {
            if (hasShip(x + (horizontal ? i : 0), y + (horizontal ? 0 : i))) {
                return false;
            }
        }
        for (int i = 0; i < size; ++i) {
            board[x + (horizontal ? i : 0)][y + (horizontal ? 0 : i)] = true;
            ships[x + (horizontal ? i : 0)][y + (horizontal ? 0 : i)] = Ship(size);
        }
        return true;
    }
    bool isGameOver() const {
        for (int x = 0; x < BOARD_SIZE; ++x) {
            for (int y = 0; y < BOARD_SIZE; ++y) {
                if (hasShip(x, y) && !ships[x][y].isSunk()) {
                    return false;
                }
            }
        }
        return true;
    }
private:
    vector<vector<bool>> board;
    vector<vector<Ship>> ships;
};

class Game
{
public:
    Game() {}

    Board playerBoard();
    Board computerBoard();

    void play()
    {

        cout << "Welcome to Battleship!" << endl;
        cout << "You are playing against the computer.";
    }
}
;
