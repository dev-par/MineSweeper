//
// Created by Devan Parekh on 4/16/24.
//

#ifndef CMAKESFMLPROJECT_BOARD_H
#define CMAKESFMLPROJECT_BOARD_H
#include "Tile.h"
#include <vector>


class Board {
public:
    vector<vector<Tile>> tiles;
    int rowCount;
    int columnCount;
    int mineCount;

    Board(int rowCount, int columnCount, int mineCount);
    void initializeBoard();
    int getRows();
    int getCols();

};

#endif //CMAKESFMLPROJECT_BOARD_H
