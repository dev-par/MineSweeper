//
// Created by Devan Parekh on 4/16/24.
//

#include "Tile.h"
using namespace std;

Tile::Tile() {
    mine = false;
    flag = false;
    revealed = false;
    neighborMineCount = 0;
}

void Tile::reset() {
    mine = false;
    flag = false;
    revealed = false;
    neighborMineCount = 0;
    neighbors.clear();
}

vector<Tile*> Tile::getNeighbors() {
    return neighbors;
}

bool Tile::isMine() {
    return mine;
}

void Tile::toggleMine() {
    mine = !mine;
}

