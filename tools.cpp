/**
 * @file tools.cpp
 * @author Bastien
 * @brief Utility functions for the game (implementation file)
 * @version 0.1
 * @date 2023-06-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include "tools.h"

/**
 * @brief Checks if a combination can be placed in a vector without violating the placement rules
 * 
 * @param x 
 * @param vector 
 * @return True if the combination can be placed, false otherwise
 */
bool canPlace(Combination x, const vector<Combination>& vector) {
  for (int i = 0; i < vector.size(); ++i) {
    const Combination& y = vector[i];
    if (x[0] == y[0] || x[1] == y[1]) {
      return false;
    }
  }
  return true;
}

/**
 * @brief Finds the quarter where a combination can be placed
 * 
 * @param combination 
 * @param vectors 
 * @return The index of the quarter where the combination can be placed, or -1 if it can't be placed anywhere
 */
int findQuarter(Combination combination, const array<vector<Combination>, 4>& vectors) {
  for (int i = 0; i < 4; ++i) {
    if (canPlace(combination, vectors[i])) {
      return i;
    }
  }
  return -1;
}

/**
 * @brief Greedily places the combinations in the vectors. It aims to place as many combinations as possible in the first quarter, then in the second quarter, and so on.
 * 
 * @param combinations 
 * @param vectors 
 */
void greedy(vector<Combination>& combinations, array<vector<Combination>, 4>& vectors) {
  vector<Combination> nones;
  for (int i = 0; i < combinations.size();) {
    Combination combination = combinations[i];
    int slot = findQuarter(combination, vectors);
    if (slot != -1) {
      vectors[slot].push_back(combination);
      combinations.erase(combinations.begin() + i);
    } else {
      nones.push_back(combination);
      ++i;
    }
  }
  combinations.swap(nones);
}

/**
 * @brief Extracts a random combination from the vectors
 * 
 * @param gen 
 * @param combinations 
 * @param vectors 
 * @return True if a combination was extracted, false otherwise
 */
bool extractRandom(mt19937& gen, vector<Combination>& combinations,
                   array<vector<Combination>, 4>& vectors) {
  shuffle(vectors.begin(), vectors.end(), gen);
  for (int i = 0; i < vectors.size(); ++i) {
    shuffle(vectors[i].begin(), vectors[i].end(), gen);
  }
  int vectorIndex = gen() % 4;
  if (vectors[vectorIndex].empty()) {
    return false;
  }
  int combinationIndex = gen() % vectors[vectorIndex].size();
  combinations.push_back(exchange(vectors[vectorIndex][combinationIndex], vectors[vectorIndex].back()));
  vectors[vectorIndex].pop_back();
  return true;
}