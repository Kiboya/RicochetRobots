/**
 * @file robot.cpp
 * @author Bastien 
 * @brief Class for a robot
 * @version 0.1
 * @date 2023-06-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "robot.h"
#include "board.h"
#include "log.h"

/**
 * @brief Construct a new Robot:: Robot object
 * 
 */
Robot::Robot(){
    this->color = ' ';
    this->number = 0;
    this->positionX = 0;
    this->positionY = 0;
    this->tile = new Tile();
    this->board = new Board();
}

/**
 * @brief Construct a new Robot:: Robot object
 * 
 * @param c Color of the robot
 * @param n Number of the robot
 * @param x X position of the robot
 * @param y Y position of the robot
 * @param t Tile of the robot
 * @param b Board of the robot
 */
Robot::Robot(char c, int n, int x, int y, Tile* t, Board* b){
    this->color = c;
    this->number = n;
    this->positionX = x;
    this->positionY = y;
    this->tile = t;
    this->board = b;
}

/**
 * @brief The getColor function returns the color of the robot
 * 
 * @return int 
 */
int Robot::getColor(){
    return this->color;
}

/**
 * @brief The getNumber function returns the number of the robot
 * 
 * @return int 
 */
int Robot::getNumber(){
    return this->number;
}

/**
 * @brief The getBasePositionX function returns the base position X of the robot
 * 
 * @return int 
 */
int Robot::getBasePositionX(){
    return this->positionX;
}

/**
 * @brief The getBasePositionY function returns the base position Y of the robot
 * 
 * @return int 
 */
int Robot::getBasePositionY(){
    return this->positionY;
}

/**
 * @brief The getTile function returns the tile of the robot
 * 
 * @return Tile* 
 */
Tile* Robot::getTile(){
    return this->tile;
}

/**
 * @brief The getBoard function returns the board of the robot
 * 
 * @return Board* 
 */
Board* Robot::getBoard(){
    return this->board;
}

/**
 * @brief The setColor function sets the color of the robot
 * 
 * @param c 
 */
void Robot::setColor(char c){
    this->color = c;
}

/**
 * @brief The setNumber function sets the number of the robot
 * 
 * @param n 
 */
void Robot::setNumber(int n){
    this->number = n;
}

/**
 * @brief The setBasePositionX function sets the base position X of the robot
 * 
 * @param x 
 */
void Robot::setBasePositionX(int x){
    this->positionX = x;
}

/**
 * @brief The setBasePositionY function sets the base position Y of the robot
 * 
 * @param y 
 */
void Robot::setBasePositionY(int y){
    this->positionY = y;
}

/**
 * @brief The setTile function sets the tile of the robot
 * 
 * @param t 
 */
void Robot::setTile(Tile* t){
    this->tile = t;
}

/**
 * @brief The setBoard function sets the board of the robot
 * 
 * @param b 
 */
void Robot::setBoard(Board* b){
    this->board = b;
}

/**
 * @brief The moveRobot function moves the robot in the direction given
 * 
 * @param direction 
 */
void Robot::moveRobot(char direction){ 
    int currentX = this->positionX;
    int currentY = this->positionY;
    if(direction == 'N'){
        //check if the robot is on the top row or if there is a robot or a wall above it to prevent it from moving at all
        if(this->positionY == 0 || this->board->getTile(this->positionX, this->positionY-1)->checkHasRobot() || this->board->getTile(this->positionX, this->positionY)->checkHasTopWall())return;
        for(int i = this->positionY; i >= 0; i--){
            if(this->board->getTile(this->positionX, i)->checkHasTopWall() || this->board->getTile(this->positionX, i-1)->checkHasRobot()){
                this->positionY = i;
                this->board->getTile(this->positionX, i)->setHasRobot(true);
                this->setTile(this->board->getTile(this->positionX, i));
                this->board->getTile(this->positionX, i)->setRobotColor(this->getColor());
                this->board->getTile(currentX, currentY)->setHasRobot(false);
                log(LogLevel::INFO, "Robot moved to tile: " + to_string(this->positionX) + ", " + to_string(this->positionY));
                break;             
            }
        }
    }else if(direction == 'S'){
        if(this->positionY == 15 || this->board->getTile(this->positionX, this->positionY+1)->checkHasRobot() || this->board->getTile(this->positionX, this->positionY)->checkHasBottomWall())return;
        for(int i = this->positionY; i < 16; i++){
            if(this->board->getTile(this->positionX, i)->checkHasBottomWall() || this->board->getTile(this->positionX, i+1)->checkHasRobot()){
                this->positionY = i;
                this->board->getTile(this->positionX, i)->setHasRobot(true);
                this->setTile(this->board->getTile(this->positionX, i));
                this->board->getTile(this->positionX, i)->setRobotColor(this->getColor());
                this->board->getTile(currentX, currentY)->setHasRobot(false);
                log(LogLevel::INFO, "Robot moved to tile: " + to_string(this->positionX) + ", " + to_string(this->positionY));
                break;             
            }
        }
    }else if(direction == 'E'){
        if(this->positionX == 15 || this->board->getTile(this->positionX+1, this->positionY)->checkHasRobot() || this->board->getTile(this->positionX, this->positionY)->checkHasRightWall())return;
        for(int i = this->positionX; i < 16; i++){
            if(this->board->getTile(i, this->positionY)->checkHasRightWall() || this->board->getTile(i+1, this->positionY)->checkHasRobot()){
                this->positionX = i;
                this->board->getTile(i, this->positionY)->setHasRobot(true);
                this->setTile(this->board->getTile(i, this->positionY));
                this->board->getTile(i, this->positionY)->setRobotColor(this->getColor());
                this->board->getTile(currentX, currentY)->setHasRobot(false);
                log(LogLevel::INFO, "Robot moved to tile: " + to_string(this->positionX) + ", " + to_string(this->positionY));
                break;             
            }
        }
    }else if(direction == 'W'){
        if(this->positionX == 0 || this->board->getTile(this->positionX-1, this->positionY)->checkHasRobot() || this->board->getTile(this->positionX, this->positionY)->checkHasLeftWall())return;
        for(int i = this->positionX; i >= 0; i--){
            if(this->board->getTile(i, this->positionY)->checkHasLeftWall() || this->board->getTile(i-1, this->positionY)->checkHasRobot()){
                this->positionX = i;
                this->board->getTile(i, this->positionY)->setHasRobot(true);
                this->setTile(this->board->getTile(i, this->positionY));
                this->board->getTile(i, this->positionY)->setRobotColor(this->getColor());
                this->board->getTile(currentX, currentY)->setHasRobot(false);
                log(LogLevel::INFO, "Robot moved to tile: " + to_string(this->positionX) + ", " + to_string(this->positionY));
                break;             
            }
        }
    }
}