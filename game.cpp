/**
 * @file game.cpp
 * @author Bastien
 * @brief Class for a game
 * @version 0.1
 * @date 2023-06-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "game.h"
#include "log.h"
#include "robot.h"
#include <random>

/**
 * @brief Construct a new Game:: Game object
 * 
 * @param b The board that will be used for the game
 * @param p The players that will play the game
 * @param r The robots that will be used for the game
 */
Game::Game(Board* b, vector<Player*> p, Robot* r[4]){
    this->board = b;
    for(int i = 0; i < p.size(); i++){
        this->players.push_back(p[i]);
    }
    for(int i = 0; i < 4; i++){
        this->robots[i] = r[i];
    }
    this->timer = 0;
    this->movecountgoal = 0;
    this->objectiveTile = nullptr;
    this->currentPlayer = nullptr;
}

/**
 * @brief The getBoard method will return the board of the game.
 * 
 * @return Board* 
 */
Board* Game::getBoard(){
    return this->board;
}

/**
 * @brief The drawObjectiveTile method will draw a tile from the objective tile deck.
 * 
 * @return Tile 
 */
void Game::drawObjectiveTile(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(0, 16);
    int n = distr(gen);
    this->objectiveTile = this->board->getTarget(n);
}

/**
 * @brief The placeRobots method will place the robots on the board.
 * @details The robots will be placed randomly on the board. 
 * 
 */
void Game::placeRobots(){
    //choose a random tile for each robot
    for(int i = 0; i < 4; i++){
        int x = rand() % 16;
        int y = rand() % 16;
        //check if the tile is empty or if it is a center tile
        if(!this->board->getTile(x,y)->checkHasRobot() && !this->board->getTile(x,y)->checkIsCentralTile()){
            this->board->getTile(x,y)->setHasRobot(true);
            this->board->getTile(x,y)->setRobotColor(this->robots[i]->getColor());
            this->robots[i]->setBasePositionX(x);
            this->robots[i]->setBasePositionY(y);
            this->robots[i]->setTile(this->board->getTile(x,y));
            //print the placed robot
            log(LogLevel::DEBUG, "Robot " + to_string(i+1) + " placed at (" + to_string(x) + ", " + to_string(y) + ") with number " + to_string(this->robots[i]->getNumber()) + " and color " + string(1, this->robots[i]->getColor()));
        }
        else{
            //if the tile is not empty, choose another tile
            i--;
        }
    }
}

/**
 * @brief The getRobot method will return a robot from the robots array.
 * 
 * @param i index of the robot
 * @return Robot* 
 */
Robot* Game::getRobot(int i){
    return this->robots[i];
}

/**
 * @brief The setRobot method will set a robot in the robots array at the given index.
 * 
 * @param i index of the robot 
 * @param r the robot to set 
 */
void Game::setRobot(int i, Robot* r){
    this->robots[i] = r;
}

/**
 * @brief The setBoard method will set the board of the game.
 * 
 * @param b the board to set
 */
void Game::setBoard(Board* b){
    this->board = b;
}

/**
 * @brief The initGame method will initialize the game.
 * 
 */
void Game::initGame(){
    log(LogLevel::INFO, "Initializing game...");
    this->board->initializeBoard();
    this->placeRobots();
    this->board->drawBoard(this->objectiveTile);
    this->getInputs();
}

/**
 * @brief The colorToString method will return a string corresponding to the color given in parameter.
 * 
 * @param c first letter of the color 
 * @return string 
 */
string colorToString(char c){
    switch (c) {
        case 'R':
            return "red";
            break;
        case 'B':
            return "blue";
            break;
        case 'G':
            return "green";
            break;
        case 'Y':
            return "yellow";
            break;
        default:
            return "unknown";
            break;
    }
}

/**
 * @brief The getInputs method will get the inputs from the players to trigger the beginning of the game/round.
 * 
 */
void Game::getInputs(){
    char input;
    while (true) {
        log(LogLevel::INFO, "Controls: n = new round, e = exit, b = new board");
        cin >> input;
        switch (input) {
            case 'n':
                log(LogLevel::INFO, "Starting new round");
                this->resetRobotsPosition();
                this->newRound();
                break;
            case 'b':
                log(LogLevel::INFO, "Starting new board");
                this->board = new Board();
                for(int i = 0; i < 4; i++){
                    robots[i]->setBoard(board);
                }
                this->initGame();
            case 'e':
                log(LogLevel::INFO, "Exiting game");
                return;
                break;
            default:
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                log(LogLevel::INFO, "Unknown input");
                break;
        }
    }
    return;
}

/**
 * @brief The startTimer method will start a timer for the given number of seconds.
 * 
 * @param seconds 
 */
void Game::startTimer(int seconds){
    timerRunning = true;
    timerDuration = seconds;
    startTime = chrono::high_resolution_clock::now();
    endTime = startTime + chrono::seconds(seconds);
    log(LogLevel::INFO, "Starting timer for " + to_string(seconds) + " seconds...");
    log(LogLevel::INFO, "enter 's' to stop timer before time is up");
    thread timerThread([this, seconds]() {
    this_thread::sleep_for(chrono::seconds(seconds));
    if (timerRunning) {
        stopTimer();
        log(LogLevel::INFO, "Timer stopped, enter any key to continue");
    }
    });
    timerThread.detach();
}

/**
 * @brief The stopTimer method will stop the timer.
 * 
 */
void Game::stopTimer(){
    timerRunning = false;
    endTime = chrono::high_resolution_clock::now();
}

/**
 * @brief The getTimer method will return the remaining time of the timer.
 * 
 * @return int 
 */
int Game::getTimer(){
    if (timerRunning) {
        auto remaining = chrono::duration_cast<chrono::seconds>(endTime - chrono::high_resolution_clock::now()).count();
        return remaining;
    } else {
        auto elapsed = chrono::duration_cast<chrono::seconds>(endTime - startTime).count();
        return timerDuration - elapsed;
    }
}

/**
 * @brief The getMoveCount method will return the move count goal.
 * 
 * @return int 
 */
int Game::getMoveCount(){
    return this->movecountgoal;
}

/**
 * @brief The getObjectiveTile method will return the objective tile.
 * 
 * @return Tile* 
 */
Tile* Game::getObjectiveTile(){
    return this->objectiveTile;
}

/**
 * @brief The selectPlayer method will select the current player.
 * 
 */
void Game::selectPlayer(){
    int playerNumber;
    while(true){
        cin >> playerNumber;
        if(playerNumber > 0 && playerNumber <= this->players.size()){
            break;
        }
        else{
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            log(LogLevel::INFO, "Invalid player number, please enter a valid player number");
        }
    }
    this->currentPlayer = this->players[playerNumber-1];
}

/**
 * @brief The setMoveCount method will set the move count goal.
 * 
 */
void Game::setMoveCount(){
    int moveCount;
    while(true){
        cin >> moveCount;
        if(moveCount > 0){
            this->movecountgoal = moveCount;
            log(LogLevel::INFO, "Move count set to " + to_string(moveCount));
            break;
        }
        else{
            log(LogLevel::INFO, "Invalid move count, please enter a valid move count");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

/**
 * @brief The moveRobot method will move the robot according to the input.
 * 
 */
void Game::moveRobot(){
    char input;
    int selectedRobot = 0;
    string color;
    int movecount = 0;
    while(true){
        log(LogLevel::INFO, "Current robot: " + colorToString(robots[selectedRobot]->getColor()));
        log(LogLevel::INFO, "Controls: z = up, s = down, q = left, d = right, n = next robot, e = exit");
        cin >> input;
        switch (input) {
            case 'z':
                log(LogLevel::INFO, "Robot " + colorToString(robots[selectedRobot]->getColor()) + " moved up");
                this->robots[selectedRobot]->moveRobot('N');
                this->board->drawBoard(this->objectiveTile);
                movecount++;
                break;
            case 's':
                log(LogLevel::INFO, "Robot " + colorToString(robots[selectedRobot]->getColor()) + " moved down");
                this->robots[selectedRobot]->moveRobot('S');
                this->board->drawBoard(this->objectiveTile);
                movecount++;
                break;
            case 'q':
                log(LogLevel::INFO, "Robot " + colorToString(robots[selectedRobot]->getColor()) + " moved left");
                this->robots[selectedRobot]->moveRobot('W');
                this->board->drawBoard(this->objectiveTile);
                movecount++;
                break;
            case 'd':
                log(LogLevel::INFO, "Robot " + colorToString(robots[selectedRobot]->getColor()) + " moved right");
                this->robots[selectedRobot]->moveRobot('E');
                this->board->drawBoard(this->objectiveTile);
                movecount++;
                break;
            case 'n':
                selectedRobot = (selectedRobot + 1) % 4;
                color = colorToString(robots[selectedRobot]->getColor());
                break;
            case 'e':
                log(LogLevel::INFO, "Exiting robot movement");
                initGame();
                break;
            default:
                log(LogLevel::INFO, "Unknown input");
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
        }
        if(input == 'n'){
            continue;
        }else if(this->isRoundSolved(this->objectiveTile)){
            log(LogLevel::INFO, "Board solved");
            this->updateScore();
            this->getInputs();
            break;
        }
        if(movecount >= this->movecountgoal){
            log(LogLevel::DEBUG, "Move count is : " + to_string(movecount) + " and move count goal is : " + to_string(this->movecountgoal));
            log(LogLevel::INFO, "Move count reached, next player with the best solution can play");
            this->resetRobotsPosition();
            this->play();
            break;
        }else{
            log(LogLevel::DEBUG, "Move count is : " + to_string(movecount) + " and move count goal is : " + to_string(this->movecountgoal));
            log(LogLevel::INFO, "Moves remaining : " + to_string(this->movecountgoal - movecount));
        }
    }
}

/**
 * @brief The isRoundSolved method will check if the round is solved after a move.
 * 
 * @param objectiveTile The objective tile to aim for
 * @return true 
 * @return false 
 */
bool Game::isRoundSolved(Tile* objectiveTile){
    int tileX = objectiveTile->getX();
    int tileY = objectiveTile->getY();
    char tileColor = objectiveTile->getTargetColor();
    bool hasRobot = objectiveTile->checkHasRobot();
    log(LogLevel::DEBUG, "Checking if round is solved");
    log(LogLevel::DEBUG, "Objective tile: " + to_string(tileX) + " " + to_string(tileY) + " " + tileColor);
    if (hasRobot) {
        log(LogLevel::DEBUG, "Objective tile has a robot on it, checking if it's the right one");
        for(int i = 0; i < 4; i++){
            log(LogLevel::DEBUG, "Robot " + to_string(i) + " position: " + to_string(this->robots[i]->getTile()->getX()) + " " + to_string(this->robots[i]->getTile()->getY()) + " " + colorToString(this->robots[i]->getColor()));
            int robotX = this->robots[i]->getTile()->getX();
            int robotY = this->robots[i]->getTile()->getY();
            char robotColor = this->robots[i]->getColor();
            if(robotX == tileX && robotY == tileY && robotColor == tileColor){
                return true;
            }
            if(tileColor == 'M'){//if the objective tile is multicolor, we need to check if any robot is on it
                if(robotX == tileX && robotY == tileY){
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * @brief The updateScore method will update the score of the current player.
 * 
 */
void Game::updateScore(){
    this->currentPlayer->incrementScore();
    log(LogLevel::INFO, "Player " + to_string(this->currentPlayer->getNumber() + 1) + " has now " + to_string(this->currentPlayer->getScore()) + " points");
}

/**
 * @brief The newRound method will start a new round.
 * 
 */
void Game::newRound(){
    this->drawObjectiveTile();
    log(LogLevel::DEBUG, "Objective tile drawn");
    this->board->drawBoard(this->objectiveTile);
    log(LogLevel::INFO, "Round started, each player needs to find the way to get the robot with the same color as the objective tile to the target tile in the least amount of moves");
    log(LogLevel::INFO, "When you are ready, enter the number of moves the player with the best solution thinks he can do it in, the 1min timer will start right after");
    this->setMoveCount();
    this->startTimer(60);
    char input;
    while (timerRunning) {
        cin >> input;
        if (timerRunning && input == 's') {
            stopTimer();
            log(LogLevel::INFO, "Timer stopped");
            break;
        }
        if(input != 's' && timerRunning){
            log(LogLevel::INFO, "Unknown input");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    this->play();

}

/**
 * @brief The play method will start the moves of the current player.
 * 
 */
void Game::play(){
    log(LogLevel::INFO, "Enter the number of the player with the best solution");
    this->selectPlayer();
    log(LogLevel::INFO, "Player " + to_string(this->currentPlayer->getNumber() + 1) + " selected");
    log(LogLevel::INFO, "Enter the number of moves the player thinks he can do it in");
    this->setMoveCount();
    log(LogLevel::INFO, "Player " + to_string(this->currentPlayer->getNumber() + 1) + " thinks she/he can do it in " + to_string(this->movecountgoal) + " moves");
    log(LogLevel::INFO, "The player with the best solution will now play");
    this->board->drawBoard(this->objectiveTile);
    this->moveRobot();
}

/**
 * @brief The resetRobotsPosition method will reset the robots position to their base position after a round or if the move count is reached.
 * 
 */
void Game::resetRobotsPosition(){
    for(int i = 0; i < 4; i++){
        this->robots[i]->getTile()->setHasRobot(false);
        this->robots[i]->setTile(this->board->getTile(this->robots[i]->getBasePositionX(), this->robots[i]->getBasePositionY()));
        this->robots[i]->getTile()->setHasRobot(true);
    }
    this->board->drawBoard(this->objectiveTile);
}