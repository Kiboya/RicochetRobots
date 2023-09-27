/**
 * @file board.h
 * @author Bastien
 * @brief Class for a board
 * @version 0.1
 * @date 2023-06-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef BOARD_H
#define BOARD_H

#include "tile.h"
#include <vector>

const int X_SIZE = 16;
const int Y_SIZE = 16; 

/**
 * @brief The Board class represents the game board.
 * @details The game board is a 16x16 grid. Each tile on the game board can have walls on one or more of its sides, a target and/or a robot.
 */
class Board{
    private:
        Tile* tiles[X_SIZE][Y_SIZE];
        vector<Tile*> targets;

    public:
        Board();
        Board(Tile* t[X_SIZE][Y_SIZE]);
        Tile* getTile(int x, int y);
        Tile* getTarget(int i);
        void setTile(int x, int y, Tile* t);
        void initializeBoard();
        void placeWalls();
        void placeCorner(int quarter, int corner);
        void placeTargets();
        void drawBoard(Tile* objectiveTile);
};

#endif // BOARD_H