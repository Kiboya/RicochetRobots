/**
 * @file board.cpp
 * @author Bastien
 * @brief Class for the board
 * @version 0.1
 * @date 2023-06-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "board.h"
#include "log.h"
#include "tools.h"

const string red("\033[1;41m");
const string green("\033[1;42m");
const string yellow("\033[1;43m");
const string cyan("\033[1;46m");
const string white("\033[1;47m");
const string bold("\033[1m");
const string reset("\033[0m");

/**
 * @brief Construct a new Board:: Board object
 * 
 */
Board::Board(){
    for(int i = 0; i < X_SIZE; i++){
        for(int j = 0; j < Y_SIZE; j++){
            this->tiles[i][j] = new Tile();
            this->tiles[i][j]->setX(i);
            this->tiles[i][j]->setY(j);
        }
    }
}

/**
 * @brief Construct a new Board:: Board object
 * 
 * @param t a 2D array of Tile pointers 
 */
Board::Board(Tile* t[X_SIZE][Y_SIZE]){
    for(int i = 0; i < X_SIZE; i++){
        for(int j = 0; j < Y_SIZE; j++){
            this->tiles[i][j] = t[i][j];
        }
    }
}

/**
 * @brief The getTile method returns the tile at the given position
 * 
 * @param x X coordinate 
 * @param y Y coordinate
 * @return Tile* 
 */
Tile* Board::getTile(int x, int y){
    return this->tiles[x][y];
}

/**
 * @brief The getTarget method returns a target at the given index of the targets array
 * 
 * @param i 
 * @return Tile* 
 */
Tile* Board::getTarget(int i){
    return this->targets[i];
}

/**
 * @brief The setTile method sets the tile at the given position
 * 
 * @param x X coordinate 
 * @param y Y coordinate
 * @param t Tile pointer
 */
void Board::setTile(int x, int y, Tile* t){
    this->tiles[x][y] = t;
}

/**
 * @brief the initializeBoard method will do the following:
 * - Place the walls
 * - Place the targets  
 * - Give debug information about the board
 */
void Board::initializeBoard(){
    this->placeWalls();
    this->placeTargets();
    // Print each tile's wall as log
    for(int x = 0; x < X_SIZE; x++){
        for(int y = 0; y < Y_SIZE; y++){
            //Print the tile's position and its walls
            char top = this->tiles[x][y]->checkHasTopWall() ? 'T' : '*';
            char right = this->tiles[x][y]->checkHasRightWall() ? 'R' : '*';
            char bottom = this->tiles[x][y]->checkHasBottomWall() ? 'B' : '*';
            char left = this->tiles[x][y]->checkHasLeftWall() ? 'L' : '*';
            log(LogLevel::DEBUG, "Tile " + to_string(x) + "," + to_string(y) + " : " + top + right + bottom + left);
        }
    }
    log(LogLevel::INFO, "Board initialized");
}

/**
 * @brief The placeWalls method will do the following:
 * - Place the board walls
 * - Place the central square walls
 * - Randomly place the outer walls on the board according to the rules of the game.
 * - Randomly place the inner corners on the board according to the rules of the game.
 * - Randomly place the last corner on the board according to the rules of the game.
 * 
 */
void Board::placeWalls() {
    random_device rd;
    mt19937 gen(rd());

    // Place the board walls
    for (int x = 0; x < X_SIZE; x++) {
        for (int y = 0; y < Y_SIZE; y++) {
            // If the tile is on the left edge of the board
            if (x == 0) {
                this->tiles[x][y]->setLeftWall(true);
            }
            // If the tile is on the right edge of the board
            if (x == X_SIZE - 1) {
                this->tiles[x][y]->setRightWall(true);
            }
            // If the tile is on the top edge of the board
            if (y == 0) {
                this->tiles[x][y]->setTopWall(true);
            }
            // If the tile is on the bottom edge of the board
            if (y == Y_SIZE - 1) {
                this->tiles[x][y]->setBottomWall(true);
            }

            // Place the central square walls
            if (x == 7 && y == 7) {
                this->tiles[x][y]->setTopWall(true);
                this->tiles[x][y]->setLeftWall(true);
                this->tiles[x - 1][y]->setRightWall(true);
                this->tiles[x][y - 1]->setBottomWall(true);
            }
            if (x == 7 && y == 8) {
                this->tiles[x][y]->setBottomWall(true);
                this->tiles[x][y]->setLeftWall(true);
                this->tiles[x - 1][y]->setRightWall(true);
                this->tiles[x][y + 1]->setTopWall(true);
            }
            if (x == 8 && y == 7) {
                this->tiles[x][y]->setTopWall(true);
                this->tiles[x][y]->setRightWall(true);
                this->tiles[x + 1][y]->setLeftWall(true);
                this->tiles[x][y - 1]->setBottomWall(true);
            }
            if (x == 8 && y == 8) {
                this->tiles[x][y]->setBottomWall(true);
                this->tiles[x][y]->setRightWall(true);
                this->tiles[x + 1][y]->setLeftWall(true);
                this->tiles[x][y + 1]->setTopWall(true);
            }
        }
    }

    // Randomly place the outer walls on the board according to the rules of the game.
    uniform_int_distribution<int> dist(0, 7);

    // First quarter
    int verticalWallQ1 = dist(gen);
    this->tiles[verticalWallQ1][0]->setRightWall(true);
    this->tiles[verticalWallQ1 + 1][0]->setLeftWall(true);
    int horizontalWallQ1 = dist(gen);
    if (verticalWallQ1 == 0) {
        while (horizontalWallQ1 == 0) {
            horizontalWallQ1 = dist(gen);
        }
    }
    this->tiles[0][horizontalWallQ1]->setBottomWall(true);
    this->tiles[0][horizontalWallQ1 + 1]->setTopWall(true);

    // Second quarter
    int verticalWallQ2 = dist(gen) + 8;
    while (verticalWallQ2 == verticalWallQ1 + 8) {
        verticalWallQ2 = dist(gen) + 8;
    }
    this->tiles[verticalWallQ2][0]->setLeftWall(true);
    this->tiles[verticalWallQ2 - 1][0]->setRightWall(true);
    int horizontalWallQ2 = dist(gen);
    if (verticalWallQ2 == 15) {
        while (horizontalWallQ2 == 0) {
            horizontalWallQ2 = dist(gen);
        }
    }
    this->tiles[15][horizontalWallQ2]->setBottomWall(true);
    this->tiles[15][horizontalWallQ2 + 1]->setTopWall(true);

    // Third quarter
    int verticalWallQ3 = dist(gen);
    this->tiles[verticalWallQ3][15]->setRightWall(true);
    this->tiles[verticalWallQ3 + 1][15]->setLeftWall(true);
    int horizontalWallQ3 = dist(gen) + 8;
    while (horizontalWallQ3 == horizontalWallQ1 + 8) {
        horizontalWallQ3 = dist(gen) + 8;
    }
    if (verticalWallQ3 == 0) {
        while (horizontalWallQ3 == 15) {
            horizontalWallQ3 = dist(gen) + 8;
        }
    }
    this->tiles[0][horizontalWallQ3]->setTopWall(true);
    this->tiles[0][horizontalWallQ3 - 1]->setBottomWall(true);

    // Fourth quarter
    int verticalWallQ4 = dist(gen) + 8;
    while (verticalWallQ4 == verticalWallQ3 + 8) {
        verticalWallQ4 = dist(gen) + 8;
    }
    this->tiles[verticalWallQ4][15]->setLeftWall(true);
    this->tiles[verticalWallQ4 - 1][15]->setRightWall(true);
    int horizontalWallQ4 = dist(gen) + 8;
    while (horizontalWallQ4 == horizontalWallQ2 + 8) {
        horizontalWallQ4 = dist(gen) + 8;
    }
    if (verticalWallQ4 == 15) {
        while (horizontalWallQ4 == 15) {
            horizontalWallQ4 = dist(gen) + 8;
        }
    }
    this->tiles[15][horizontalWallQ4]->setTopWall(true);
    this->tiles[15][horizontalWallQ4 - 1]->setBottomWall(true);

    // Place the corners on each quarter
    for (int quarter = 1; quarter < 5; quarter++) {
        for (int i = 1; i < 5; i++) {
            placeCorner(quarter, i);
        }
    }

    // Place the last corner containing the multicolored target in a random quarter
    uniform_int_distribution<int> distQuarter(1, 4);
    int quarter = distQuarter(gen);
    placeCorner(quarter, 0);
}

/**
 * @brief Place a corner in a quarter of the board.
 * 
 * @param quarter The quarter of the board. 
 * @param corner The corner to place.
 */
void Board::placeCorner(int quarter, int corner) {
    int minX, maxX, minY, maxY;
    switch (quarter) {
        case 1:
            // First quarter
            minX = 1; maxX = 7; minY = 1; maxY = 7;
            break;
        case 2:
            // Second quarter
            minX = 8; maxX = 14; minY = 1; maxY = 7;
            break;
        case 3:
            // Third quarter
            minX = 1; maxX = 7; minY = 8; maxY = 14;
            break;
        case 4:
            // Fourth quarter
            minX = 8; maxX = 14; minY = 8; maxY = 14;
            break;
        default:
            log(LogLevel::ERROR, "quarter " + to_string(quarter) + " does not exist.");
            return;
    }

    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> xDist(minX, maxX);
    uniform_int_distribution<int> yDist(minY, maxY);

    int cornerX = xDist(gen);
    int cornerY = yDist(gen);

    // Check that there is no wall on that tile and that it is not adjacent to the center
    while (this->tiles[cornerX][cornerY]->checkHasWall() ||
           (cornerX >= 6 && cornerX <= 9) && (cornerY >= 6 && cornerY <= 9) &&
           !(cornerX == 6 && cornerY == 6) && !(cornerX == 9 && cornerY == 6) &&
           !(cornerX == 6 && cornerY == 9) && !(cornerX == 9 && cornerY == 9)) {
        cornerX = xDist(gen);
        cornerY = yDist(gen);
    }

    // Choose a side for the first corner
    // sides: 0 = top, 1 = right, 2 = bottom, 3 = left
    uniform_int_distribution<int> sideDist(0, 3);
    int side1 = sideDist(gen);

    // Choose a side for the second corner (needs to be adjacent to the first corner)
    int side2 = sideDist(gen);
    while (side2 == side1 || side2 == (side1 + 2) % 4) {
        side2 = sideDist(gen);
    }

    // Print all the corners generated
    if (corner == 0) {
        log(LogLevel::DEBUG, "Last corner is at (" + to_string(cornerX) + ", " + to_string(cornerY) +
            ") with sides " + to_string(side1) + " and " + to_string(side2) + " and contains the multicolored target");
    }
    else {
        log(LogLevel::DEBUG, "Corner " + to_string(corner) + " of quarter " + to_string(quarter) +
            " is at (" + to_string(cornerX) + ", " + to_string(cornerY) + ") with sides " +
            to_string(side1) + " and " + to_string(side2));
    }

    // Check if one of the walls is adjacent to another wall by checking the 2 diagonally adjacent tiles touching the side
    bool isValid = true;

    // Check diagonal tiles adjacent to the top side
    if (this->tiles[cornerX - 1][cornerY - 1]->checkHasRightWall() ||
        this->tiles[cornerX - 1][cornerY - 1]->checkHasBottomWall() ||
        this->tiles[cornerX + 1][cornerY - 1]->checkHasLeftWall() ||
        this->tiles[cornerX + 1][cornerY - 1]->checkHasBottomWall()) {
        if (side1 == 0 || side2 == 0) {// if one of the sides is the top side
            isValid = false;
        }
    }

    // Check diagonal tiles adjacent to the right side
    if (this->tiles[cornerX + 1][cornerY - 1]->checkHasLeftWall() ||
        this->tiles[cornerX + 1][cornerY - 1]->checkHasBottomWall() ||
        this->tiles[cornerX + 1][cornerY + 1]->checkHasLeftWall() ||
        this->tiles[cornerX + 1][cornerY + 1]->checkHasTopWall()) {
        if (side1 == 1 || side2 == 1) {// if one of the sides is the right side
            isValid = false;
        }
    }

    // Check diagonal tiles adjacent to the bottom side
    if (this->tiles[cornerX + 1][cornerY + 1]->checkHasLeftWall() ||
        this->tiles[cornerX + 1][cornerY + 1]->checkHasTopWall() ||
        this->tiles[cornerX - 1][cornerY + 1]->checkHasRightWall() ||
        this->tiles[cornerX - 1][cornerY + 1]->checkHasTopWall()) {
        if (side1 == 2 || side2 == 2) {// if one of the sides is the bottom side
            isValid = false;
        }
    }

    // Check diagonal tiles adjacent to the left side
    if (this->tiles[cornerX - 1][cornerY + 1]->checkHasRightWall() ||
        this->tiles[cornerX - 1][cornerY + 1]->checkHasTopWall() ||
        this->tiles[cornerX - 1][cornerY - 1]->checkHasRightWall() ||
        this->tiles[cornerX - 1][cornerY - 1]->checkHasBottomWall()) {
        if (side1 == 3 || side2 == 3) {// if one of the sides is the left side
            isValid = false;
        }
    }

    if (!isValid) {
        // Generate a new corner
        log(LogLevel::DEBUG, "Invalid corner, generating new corner");
        placeCorner(quarter, corner);
        return;
    }
    else {
        // Set the walls on the tiles
        switch (side1) {
            case 0:
                this->tiles[cornerX][cornerY]->setTopWall(true);
                this->tiles[cornerX][cornerY - 1]->setBottomWall(true);
                break;
            case 1:
                this->tiles[cornerX][cornerY]->setRightWall(true);
                this->tiles[cornerX + 1][cornerY]->setLeftWall(true);
                break;
            case 2:
                this->tiles[cornerX][cornerY]->setBottomWall(true);
                this->tiles[cornerX][cornerY + 1]->setTopWall(true);
                break;
            case 3:
                this->tiles[cornerX][cornerY]->setLeftWall(true);
                this->tiles[cornerX - 1][cornerY]->setRightWall(true);
                break;
            default:
                log(LogLevel::ERROR, "Unexpected side value: " + to_string(side1));
                break;
        }

        switch (side2) {
            case 0:
                this->tiles[cornerX][cornerY]->setTopWall(true);
                this->tiles[cornerX][cornerY - 1]->setBottomWall(true);
                break;
            case 1:
                this->tiles[cornerX][cornerY]->setRightWall(true);
                this->tiles[cornerX + 1][cornerY]->setLeftWall(true);
                break;
            case 2:
                this->tiles[cornerX][cornerY]->setBottomWall(true);
                this->tiles[cornerX][cornerY + 1]->setTopWall(true);
                break;
            case 3:
                this->tiles[cornerX][cornerY]->setLeftWall(true);
                this->tiles[cornerX - 1][cornerY]->setRightWall(true);
                break;
            default:
                log(LogLevel::ERROR, "Unexpected side value: " + to_string(side2));
                break;
        }

        // Set the corner
        if (corner == 0) {
            // The multicolored target is handled separately from the other targets. The latter are handled in the placeTargets method.
            this->tiles[cornerX][cornerY]->setHasTarget(true);
            this->tiles[cornerX][cornerY]->setTargetSymbol('*');
            this->tiles[cornerX][cornerY]->setTargetColor('M');
            this->tiles[cornerX][cornerY]->setHasSpecialTarget(true);
            this->targets.push_back(this->tiles[cornerX][cornerY]);
        }
        else {
            this->tiles[cornerX][cornerY]->setHasCorner(true);
        }
    }
}

/**
 * @brief The placeTargets method will place the targets on the board.
 * @details The targets will be placed on tiles which have corners. On each quarter of the board, there will be 4 targets with the following symbols/colors:
 * - target "&", target "#", target "%" and target "$"
 * - color "R", color "G", color "B" and color "Y"    
 * See the documentation for more information about the target placement.
 */
void Board::placeTargets(){
    vector<char> symbols = {'&', '#', '%', '$'};
    vector<char> colors = {'R', 'G', 'B', 'Y'};
    vector<Combination> combinations;

    random_device rd;
    mt19937 gen(rd());

    // Generate all possible combinations
    for (int i = 0; i < symbols.size(); ++i) {
        for (int j = 0; j < colors.size(); ++j) {
            combinations.push_back({symbols[i], colors[j]});
        }
    }
    shuffle(combinations.begin(), combinations.end(), gen);

    array<vector<Combination>, 4> vectors;

    int rounds = 0;

    while (true) {
        ++rounds;
        greedy(combinations, vectors);
        if (combinations.empty()) break;
        if (rounds > 1000) {
            log(LogLevel::ERROR, "Could not find a solution in 1000 rounds");
            break;
        }
        extractRandom(gen, combinations, vectors);
    }

    log(LogLevel::DEBUG, "Solution found in " + to_string(rounds) + " rounds");


    // Print the four separate vectors
    for (int i = 0; i < 4; i++) {
        log(LogLevel::DEBUG, "Vector " + to_string(i) + ":");
        for (int j = 0; j < vectors[i].size(); j++) {
            const Combination& combination = vectors[i][j];
            log(LogLevel::DEBUG, "  " + to_string(j) + ": " + combination[0] + combination[1]);
        }
    }
    // Print the remaining combinations
    log(LogLevel::DEBUG, "Unassigned combinations:");
    if (combinations.empty()) {
        log(LogLevel::DEBUG, "  None");
    }else{
        for (int i = 0; i < combinations.size(); i++) {
            const Combination& combination = combinations[i];
            log(LogLevel::DEBUG, "  " + to_string(i) + ": " + combination[0] + combination[1]);
        }
    }

    //place the targets on the board
    for(int quarter = 0; quarter < 4; quarter++){
        int minX = (quarter == 1 || quarter == 3) ? 0 : 8;
        int maxX = (quarter == 1 || quarter == 3) ? 8 : 16;
        int minY = (quarter == 1 || quarter == 2) ? 0 : 8;
        int maxY = (quarter == 1 || quarter == 2) ? 8 : 16;

        //go through all the tiles in the quarter
        for (auto combination : vectors[quarter]) {
            bool targetPlaced = false;  // flag to track successful placement
            for (int y = minY; y < maxY; y++) {
                for (int x = minX; x < maxX; x++) {
                    // check if the tile has a corner
                    if (this->tiles[x][y]->checkHasCorner()) {
                        // check if the tile has a target
                        if (!this->tiles[x][y]->checkHasTarget()) {
                            this->tiles[x][y]->setHasTarget(true);
                            this->tiles[x][y]->setTargetSymbol(combination[0]);
                            this->tiles[x][y]->setTargetColor(combination[1]);
                            this->targets.push_back(this->tiles[x][y]);
                            targetPlaced = true;  // mark target as placed
                            //print the placed target
                            log(LogLevel::DEBUG, "Target of quarter " + to_string(quarter+1) +  " placed at (" + to_string(x) + ", " + to_string(y) + ") with symbol " + string(1, combination[0]) + " and color " + string(1, combination[1]));
                            break;
                        }
                    }
                }
                if (targetPlaced) {
                    break;  // no need to continue looping if target is placed
                }
            }
        }

    }

}

/**
 * @brief The drawBoard method will draw the board on the screen.
 * @details The board will be drawn using the tiles in the board.
 * 
 */
void Board::drawBoard(Tile* objectiveTile){
    string objectiveTilePart1;
    string objectiveTilePart2;
    if (objectiveTile != nullptr) {
        // Write the objective tile
        if (objectiveTile->getTargetColor() == 'M'){
            objectiveTilePart1 = red + " " + green + "*";
            objectiveTilePart2 = white + " " + cyan + "*" + yellow + "  " + reset;
        }
        else{
            char targetSymbol = objectiveTile->getTargetSymbol();
            if (objectiveTile->getTargetColor() == 'R') {
                objectiveTilePart1 = red + " " + string(1, targetSymbol);
                objectiveTilePart2 = " " + string(1, targetSymbol) + " " + reset; 
            } else if (objectiveTile->getTargetColor() == 'G') {
                objectiveTilePart1 = green + " " + string(1, targetSymbol);
                objectiveTilePart2 = " " + string(1, targetSymbol) + " " + reset;
            } else if (objectiveTile->getTargetColor() == 'B') {
                objectiveTilePart1 = cyan + " " + string(1, targetSymbol);
                objectiveTilePart2 = " " + string(1, targetSymbol) + " " + reset;
            } else if (objectiveTile->getTargetColor() == 'Y') {
                objectiveTilePart1 = yellow + " " + string(1, targetSymbol);
                objectiveTilePart2 = " " + string(1, targetSymbol) + " " + reset;
            }
        }
    }else{
        objectiveTilePart1 = "  ";
        objectiveTilePart2 = "   ";
    }
    cout << "   ";
    // Write the numbers on the top
    for (int i = 0; i < X_SIZE; i++) {
        if (i == 15) {
            cout << " " << i << "  " << endl;
            break;
        }
        if (i == 10) {
            cout << " ";
        }
        if (i < 10)
            cout << "  " << i << "  ";
        else
            cout << " " << i << "  ";
    }

    // Write the board
    // We go through all the tiles on the board
    for (int y = 0; y < Y_SIZE; y++) {
        // Write the top border
        if (y == 0) {
            for (int x = 0; x < X_SIZE; x++) {
                if (x == 0) {
                    cout << "   ╔════";
                } else {
                    if (this->tiles[x][y]->checkHasLeftWall()) {
                        cout << "╦════";
                    } else {
                        cout << "╤════";
                    }
                }
                if (x == 15) {
                    cout << "╗" << endl;
                }
            }
            for (int x = 0; x < X_SIZE; x++) {
                // Write the left border of the first line's tiles
                string robot;
                if(this->tiles[x][y]->checkHasRobot()){
                    string color;
                    if (this->tiles[x][y]->getRobotColor() == 'R') {
                        color = red;
                    } else if (this->tiles[x][y]->getRobotColor() == 'G') {
                        color = green;
                    } else if (this->tiles[x][y]->getRobotColor() == 'B') {
                        color = cyan;
                    } else if (this->tiles[x][y]->getRobotColor() == 'Y') {
                        color = yellow;
                    }
                    robot = color + " ® " + reset + " ";
                }
                if (x == 0) {
                    if (this->tiles[x][y]->checkHasRobot()){
                        cout << " " << y << " ║"<< robot;
                    }else{
                        cout << " " << y << " ║    ";
                    }
                } else {
                    if (this->tiles[x][y]->checkHasLeftWall()) {
                        if (this->tiles[x][y]->checkHasRobot()){
                            cout << "║"<< robot;
                        }else{
                            cout << "║    ";
                        }
                    } else {
                        if (this->tiles[x][y]->checkHasRobot()){
                            cout << "│" << robot;
                        }else{
                            cout << "│    ";
                        }
                    }
                }
                if (x == 15) {
                    cout << "║" << endl;
                }
            }

        }
        // Write the rest of the board
        else {
            // Write the top side of the tiles
            for (int x = 0; x < X_SIZE; x++) {
                if (x == 0) {
                    if (this->tiles[x][y]->checkHasTopWall()) {
                        cout << "   ╠════";
                    } else {
                        cout << "   ╟────";
                    }
                } else {
                    if (this->tiles[x][y]->checkHasTopWall()) {
                        if (this->tiles[x][y]->checkHasLeftWall()) {
                            cout << "╔════";
                        } else if (this->tiles[x][y - 1]->checkHasLeftWall()) {
                            cout << "╚════";
                        } else {
                            if ((x == 8 && y == 7) || (x == 8 && y == 9)) {
                                if (y == 7) {
                                    cout << "╧";
                                } else if (y == 9) {
                                    cout << "╤";
                                }
                                cout << "════";
                            } else {
                                cout << "┤════";
                            }
                        }
                    } else if (this->tiles[x - 1][y]->checkHasTopWall()) {
                        if (this->tiles[x][y]->checkHasLeftWall()) {
                            cout << "╗────";
                        } else if (this->tiles[x][y - 1]->checkHasLeftWall()) {
                            cout << "╝────";
                        } else {
                            cout << "├────";
                        }
                    } else if (this->tiles[x][y]->checkHasLeftWall()) {
                        if (x == 7 && y == 8 || x == 9 && y == 8) {
                            if (x == 9) {
                                cout << "╟────";
                            } else if (x == 7) {
                                cout << "╢  " + objectiveTilePart1;
                            }
                        } else {
                            cout << "┴────";
                        }
                    } else if (this->tiles[x][y - 1]->checkHasLeftWall()) {
                        cout << "┬────";
                    } else {
                        if (x == 8 && y == 8) {
                            cout << objectiveTilePart2 + "  ";
                        } else {
                            cout << "┼────";
                        }
                    }
                }
                if (x == 15) {
                    if (this->tiles[x][y]->checkHasTopWall()) {
                        cout << "╣" << endl;
                    } else {
                        cout << "╢" << endl;
                    }
                }
            }
            // Write the left side of the tiles
            for (int x = 0; x < X_SIZE; x++) {
                string target = "";
                string robot = "";
                if(this->tiles[x][y]->checkHasTarget()){
                    string color;
                    if (this->tiles[x][y]->getTargetColor() == 'R') {
                        color = red;
                    } else if (this->tiles[x][y]->getTargetColor() == 'G') {
                        color = green;
                    } else if (this->tiles[x][y]->getTargetColor() == 'B') {
                        color = cyan;
                    } else if (this->tiles[x][y]->getTargetColor() == 'Y') {
                        color = yellow;
                    }
                    target = color + " " + this->tiles[x][y]->getTargetSymbol()  + this->tiles[x][y]->getTargetSymbol() + " " + reset;
                }
                if(this->tiles[x][y]->checkHasRobot()){
                    string color;
                    if (this->tiles[x][y]->getRobotColor() == 'R') {
                        color = red;
                    } else if (this->tiles[x][y]->getRobotColor() == 'G') {
                        color = green;
                    } else if (this->tiles[x][y]->getRobotColor() == 'B') {
                        color = cyan;
                    } else if (this->tiles[x][y]->getRobotColor() == 'Y') {
                        color = yellow;
                    }
                    robot = color + " ® " + reset + " ";
                }
                // Write the numbers on the left
                if (x == 0) {
                    if (y < 10)
                        cout << " " << y;
                    else
                        cout << y;
                    if (this->tiles[x][y]->checkHasLeftWall()) {
                        if (this->tiles[x][y]->checkHasSpecialTarget() && !this->tiles[x][y]->checkHasRobot()) {
                            cout << " ║" << red << " " << green << "*" << cyan << "*" << yellow << " " << reset;
                        }else if (this->tiles[x][y]->checkHasTarget() && !this->tiles[x][y]->checkHasRobot()) {
                            cout << " ║" << target;
                        }else if (this->tiles[x][y]->checkHasRobot()) {
                            cout << " ║" << robot;
                        } else {
                            cout << " ║    ";
                        }
                    }
                } else {
                    if (this->tiles[x][y]->checkHasLeftWall()) {
                        if (this->tiles[x][y]->checkHasSpecialTarget() && !this->tiles[x][y]->checkHasRobot()) {
                            cout << "║" << red << " " << green << "*" << cyan << "*" << yellow << " " << reset;
                        }else if (this->tiles[x][y]->checkHasTarget() && !this->tiles[x][y]->checkHasRobot()) {
                            cout << "║" << target;
                        }else if (this->tiles[x][y]->checkHasRobot()) {
                            cout << "║" << robot;
                        } else {
                            cout << "║    ";
                        }
                    } else {
                        if ((x == 8 && y == 7) || (x == 8 && y == 8)) {
                            cout << "     ";
                        } else {
                            if (this->tiles[x][y]->checkHasSpecialTarget() && !this->tiles[x][y]->checkHasRobot()) {
                                cout << "│" <<red << " " << green << "*" << cyan << "*" << yellow << " " << reset;
                            }else if (this->tiles[x][y]->checkHasTarget() && !this->tiles[x][y]->checkHasRobot()) {
                                cout << "│" << target;
                            }else if (this->tiles[x][y]->checkHasRobot()){
                                cout << "│" << robot;
                            }else {
                                cout << "│    ";
                            }
                        }
                    }
                }
                if (x == 15) {
                    cout << "║" << endl;
                }
            }
        }

        // Write the bottom border
        if (y == 15) {
            for (int x = 0; x < X_SIZE; x++) {
                if (x == 0) {
                    cout << "   ╚════";
                } else {
                    if (this->tiles[x][y]->checkHasLeftWall()) {
                        cout << "╩════";
                    } else {
                        cout << "╧════";
                    }
                }
                if (x == 15) {
                    cout << "╝" << endl;
                }
            }
        }
    }
    log(LogLevel::INFO, "Board drawn");
    
}
