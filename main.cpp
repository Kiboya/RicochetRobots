/**
 * @file main.cpp
 * @author Bastien
 * @brief Main file for the game
 * @version 0.1
 * @date 2023-06-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "game.h"
#include "log.h"

const LogLevel loggingLevel = LogLevel::DEBUG;// Set the minimum log level to log

int main()
{
  setLogLevel(loggingLevel);

  vector<Player*> players;
  Board* board = new Board();
  Robot* robots[4];
  for(int i = 0; i < 4; i++){
    robots[i] = new Robot();
  }
  char colors[4] = {'R', 'B', 'G', 'Y'};
  for(int i = 0; i < 4; i++){
    robots[i]->setColor(colors[i]);
    robots[i]->setNumber(i);
    robots[i]->setBoard(board);
  }
  int input;
  log(LogLevel::INFO, "Enter the number of players: ");
  while (true) {
      if (cin >> input && input > 0 && input <= numeric_limits<int>::max()) {
          break;
      } else {
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          log(LogLevel::ERROR, "Invalid number of players, please enter a number");
      }
  }
  for(int i = 0; i < input; i++){
    Player* p = new Player();
    p->setNumber(i);
    players.push_back(p);
  }
  Game game = Game(board, players, robots);
  game.initGame();

  return 0;
}