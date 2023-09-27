/**
 * @file tile.cpp
 * @author Bastien
 * @brief Class for Tile (Implementation File)
 * @version 0.1
 * @date 2023-06-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "tile.h"

/**
 * @brief Construct a new Tile:: Tile object
 * 
 */
Tile::Tile(){
    this->topWall = false;
    this->bottomWall = false;
    this->leftWall = false;
    this->rightWall = false;
    this->hasTarget = false;
    this->hasCorner = false;
    this->hasSpecialTarget = false;
    this->hasRobot = false;
    this->isCentralTile = false;
    this->targetColor = ' ';
    this->targetSymbol = ' ';
    this->robotColor = ' ';
}

/**
 * @brief Construct a new Tile:: Tile object
 * 
 * @param t Top wall
 * @param b Bottom wall
 * @param l Left wall
 * @param r Right wall
 * @param hasT Has target
 * @param hasC Has corner
 * @param hasST Has special target
 * @param hasR Has robot
 * @param isCentral Is central tile
 * @param tColor Target color
 * @param tSymbol Target symbol
 * @param rColor Robot color
 * @param x X position
 * @param y Y position
 */
Tile::Tile(bool t, bool b, bool l, bool r, bool hasT, bool hasC, bool hasST, bool hasR, bool isCentral, char tColor, char tSymbol, char rColor, int x, int y){
    this->topWall = t;
    this->bottomWall = b;
    this->leftWall = l;
    this->rightWall = r;
    this->hasTarget = hasT;
    this->hasCorner = hasC;
    this->hasSpecialTarget = hasST;
    this->hasRobot = hasR;
    this->isCentralTile = isCentral;
    this->targetColor = tColor;
    this->targetSymbol = tSymbol;
    this->robotColor = rColor;
    this->positionX = x;
    this->positionY = y;
}

/**
 * @brief The checkHasWall function checks if the tile has a wall
 * 
 * @return true 
 * @return false 
 */
bool Tile::checkHasWall(){
    return (this->topWall || this->bottomWall || this->leftWall || this->rightWall);
}

/**
 * @brief The checkHasTopWall function checks if the tile has a top wall
 * 
 * @return true 
 * @return false 
 */
bool Tile::checkHasTopWall(){
    return this->topWall;
}

/**
 * @brief The checkHasBottomWall function checks if the tile has a bottom wall
 * 
 * @return true 
 * @return false 
 */
bool Tile::checkHasBottomWall(){
    return this->bottomWall;
}

/**
 * @brief The checkHasLeftWall function checks if the tile has a left wall
 * 
 * @return true 
 * @return false 
 */
bool Tile::checkHasLeftWall(){
    return this->leftWall;
}

/**
 * @brief The checkHasRightWall function checks if the tile has a right wall
 * 
 * @return true 
 * @return false 
 */
bool Tile::checkHasRightWall(){
    return this->rightWall;
}

/**
 * @brief The checkHasTarget function checks if the tile has a target
 * 
 * @return true 
 * @return false 
 */
bool Tile::checkHasTarget(){
    return this->hasTarget;
}

/**
 * @brief The checkHasCorner function checks if the tile has a corner
 * 
 * @return true 
 * @return false 
 */
bool Tile::checkHasCorner(){
    return this->hasCorner;
}

/**
 * @brief The checkHasSpecialTarget function checks if the tile has a special target
 * 
 * @return true 
 * @return false 
 */
bool Tile::checkHasSpecialTarget(){
    return this->hasSpecialTarget;
}

/**
 * @brief The checkHasRobot function checks if the tile has a robot
 * 
 * @return true 
 * @return false 
 */
bool Tile::checkHasRobot(){
    return this->hasRobot;
}

/**
 * @brief The checkIsCentralTile function checks if the tile one of the central tiles
 * 
 * @return true 
 * @return false 
 */
bool Tile::checkIsCentralTile(){
    return this->isCentralTile;
}

/**
 * @brief The getTargetColor function returns the target color
 * 
 * @return char 
 */
char Tile::getTargetColor(){
    return this->targetColor;
}

/**
 * @brief The getTargetSymbol function returns the target symbol
 * 
 * @return char 
 */
char Tile::getTargetSymbol(){
    return this->targetSymbol;
}

/**
 * @brief The getRobotColor function returns the robot color
 * 
 * @return char 
 */
char Tile::getRobotColor(){
    return this->robotColor;
}

/**
 * @brief The setTopWall function sets the top wall
 * 
 * @param t 
 */
void Tile::setTopWall(bool t){
    this->topWall = t;
}

/**
 * @brief The setBottomWall function sets the bottom wall
 * 
 * @param b 
 */
void Tile::setBottomWall(bool b){
    this->bottomWall = b;
}

/**
 * @brief The setLeftWall function sets the left wall
 * 
 * @param l 
 */
void Tile::setLeftWall(bool l){
    this->leftWall = l;
}

/**
 * @brief The setRightWall function sets the right wall
 * 
 * @param r 
 */
void Tile::setRightWall(bool r){
    this->rightWall = r;
}

/**
 * @brief The setHasTarget function sets that the tile has a target
 * 
 * @param t 
 */
void Tile::setHasTarget(bool t){
    this->hasTarget = t;
}

/**
 * @brief The setHasCorner function sets that the tile has a corner
 * 
 * @param c 
 */
void Tile::setHasCorner(bool c){
    this->hasCorner = c;
}

/**
 * @brief The setHasSpecialTarget function sets that the tile has a special target
 * 
 * @param sc 
 */
void Tile::setHasSpecialTarget(bool sc){
    this->hasSpecialTarget = sc;
}

/**
 * @brief The setHasRobot function sets that the tile has a robot
 * 
 * @param r 
 */
void Tile::setHasRobot(bool r){
    this->hasRobot = r;
}

/**
 * @brief The setIsCentralTile function sets that the tile is one of the central tiles
 * 
 * @param c 
 */
void Tile::setIsCentralTile(bool c){
    this->isCentralTile = c;
}

/**
 * @brief The setTargetColor function sets the target color
 * 
 * @param c 
 */
void Tile::setTargetColor(char c){
    this->targetColor = c;
}

/**
 * @brief The setTargetSymbol function sets the target symbol
 * 
 * @param s 
 */
void Tile::setTargetSymbol(char s){
    this->targetSymbol = s;
}

/**
 * @brief The setRobotColor function sets the robot color
 * 
 * @param c 
 */
void Tile::setRobotColor(char c){
    this->robotColor = c;
}

/**
 * @brief The getX function returns the x position of the tile
 * 
 * @return int 
 */
int Tile::getX(){
    return this->positionX;
}

/**
 * @brief The getY function returns the y position of the tile
 * 
 * @return int 
 */
int Tile::getY(){
    return this->positionY;
}

/**
 * @brief The setX function sets the x position of the tile
 * 
 * @param x 
 */
void Tile::setX(int x){
    this->positionX = x;
}

/**
 * @brief The setY function sets the y position of the tile
 * 
 * @param y 
 */
void Tile::setY(int y){
    this->positionY = y;
}

