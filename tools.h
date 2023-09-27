/**
 * @file tools.h
 * @author Bastien
 * @brief Utility functions for the game
 * @version 0.1
 * @date 2023-06-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

using namespace std;

/**
 * Type definition for a combination, which is an array of two characters: the first character is the symbol, the second character is the color.
 */
typedef array<char, 2> Combination;
bool canPlace(Combination x, const vector<Combination>& vector);
int findQuarter(Combination combination, const array<vector<Combination>, 4>& vectors);
void greedy(vector<Combination>& combinations, array<vector<Combination>, 4>& vectors);
bool extractRandom(mt19937& gen, vector<Combination>& combinations,array<vector<Combination>, 4>& vectors);


