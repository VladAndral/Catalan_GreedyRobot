#ifndef GREEDY_ROBOT_TESTS_H_
#define GREEDY_ROBOT_TESTS_H_
#include "greedy_robot.h"
#include <vector>

bool CheckValues (GreedyRobot gr, int x1, int y1, int x2, int y2, int max_moves, int pathLength, vector<string> listOfShortestPaths);

void tests_GreedyRobot();

#endif