/**
 * @file player.cpp
 * @author Bastien
 * @brief Class for a player
 * @version 0.1
 * @date 2023-06-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "player.h"

/**
 * @brief Construct a new Player:: Player object
 * 
 */
Player::Player(){
    this->name = "";
    this->score = 0;
}

/**
 * @brief Construct a new Player:: Player object
 * 
 * @param n Name of the player
 * @param s Score of the player
 */
Player::Player(string n, int s){
    this->name = n;
    this->score = s;
}

/**
 * @brief The getName function returns the name of the player
 * 
 * @return string 
 */
string Player::getName(){
    return this->name;
}

/**
 * @brief The getScore function returns the score of the player
 * 
 * @return int 
 */
int Player::getScore(){
    return this->score;
}

/**
 * @brief The setName function sets the name of the player
 * 
 * @param n 
 */
void Player::setName(string n){
    this->name = n;
}

/**
 * @brief The setScore function sets the score of the player
 * 
 * @param s The score of the player 
 */
void Player::setScore(int s){
    this->score = s;
}

/**
 * @brief The incrementScore function increments the score of the player
 * 
 */
void Player::incrementScore(){
    this->score++;
}

/**
 * @brief The setNumber function sets the number of the player
 * 
 * @param n The number of the player
 */
void Player::setNumber(int n){
    this->number = n;
}

/**
 * @brief The getNumber function returns the number of the player
 * 
 * @return int 
 */
int Player::getNumber(){
    return this->number;
}