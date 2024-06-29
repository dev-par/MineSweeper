//
// Created by Devan Parekh on 4/16/24.
//

#include "Board.h"
#include "TextureManager.h"
#include <iostream>
#include <vector>
using namespace std;

Board::Board(int rowCount, int columnCount, int mineCount) {
    this->rowCount = rowCount;
    this->columnCount = columnCount;
    this->mineCount = mineCount;

    tiles.resize(columnCount, vector<Tile>(rowCount));

    initializeBoard();
}

int Board::getRows() {
    return rowCount;
}

int Board::getCols() {
    return columnCount;
}

void Board::initializeBoard() {

    for (int i = 0; i < columnCount; i++) {
        for (int j = 0; j < rowCount; j++) {
            Tile &newTile = tiles[i][j];
            for (int x = -1; x <= 1; x++){
                for (int y = -1; y <= 1; y++){
                    if (x == 0 && y == 0) {
                        continue;
                    }
                    try {
                        Tile *neighbor = &tiles.at(i+x).at(j+y);
                        newTile.neighbors.push_back(neighbor);
                        if (neighbor->mine){
                            newTile.neighborMineCount++;
                        }
                    }
                    catch (const std::out_of_range& e){
                        continue;
                    }
                }
            }
        }
    }
}







