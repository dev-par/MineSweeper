//
// Created by Devan Parekh on 4/16/24.
//

#ifndef CMAKESFMLPROJECT_TILE_H
#define CMAKESFMLPROJECT_TILE_H
#include <vector>
using namespace std;

class Tile {
public:
    Tile();
    void reset();
    bool revealed;
    bool mine;
    bool flag;
    int neighborMineCount;
    void toggleMine();
    vector<Tile*> getNeighbors();
    bool isMine();
    vector<Tile*> neighbors;
};


#endif //CMAKESFMLPROJECT_TILE_H
