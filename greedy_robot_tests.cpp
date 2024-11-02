#include "greedy_robot.h"
#include <iostream>

using namespace std;

GreedyRobot grDefault;
GreedyRobot gr1(1, 1, 1, 2, 2);
GreedyRobot gr2(1, 1, 1, -3, -3);
GreedyRobot gr3(10, 1, 1, 3, 1);
GreedyRobot gr4(10, 1, 1, 13, 1);
GreedyRobot gr5(10, 1, 1, 1, 1);

bool CheckValues (GreedyRobot gr,  int max_moves, int x1, int y1, int x2, int y2, int pathLength, vector<string> listOfShortestPaths) {
    
    bool listContentsAreEqual = true;
    if (listOfShortestPaths.size() != gr.list_of_shortestPaths().size()) listContentsAreEqual = false;
    for (int i = 0; i < listOfShortestPaths.size(); i++) {
        if (!(gr.list_of_shortestPaths()[i] == listOfShortestPaths[i])) {
            listContentsAreEqual = false;
            break;
        }
    }
    
    return (
        (gr.startingX() == x1) &&
        (gr.startingY() == y1) &&
        (gr.treasureX() == x2) &&
        (gr.treasureY() == y2) &&
        (gr.max_movementDistance() == max_moves) &&
        (gr.path_length() == pathLength) &&
        listContentsAreEqual
    );
}

bool testDefault(GreedyRobot gr) {
    vector<string> temp;
    return CheckValues(gr, 0, 0, 0, 0, 0, 0, temp);
}
bool testNormal1(GreedyRobot gr) {
    vector<string> temp = {"EN", "NE"};
    return CheckValues(gr, 1, 1, 1, 2, 2, 2, temp);
}

bool testNormal2(GreedyRobot gr) {
    vector<string> temp = {"WSWSWSWS", "SWSWSWSW"};
    // gr.print_listof_shortestPaths();
    return CheckValues(gr, 1, 1, 1, -3, -3, 8, temp);
}

bool testLine1(GreedyRobot gr) {
    vector<string> temp = {"EE"};
    return CheckValues(gr, 10, 1, 1, 3, 1, 2, temp);
}

bool testLine2(GreedyRobot gr) {
    vector<string> temp = {"No paths exist for the coordinates and maximum foward movement."};
    // gr.print_listof_shortestPaths();
    return CheckValues(gr, 10, 1, 1, 13, 1, 12, temp);
}

bool testOnTreasure(GreedyRobot gr) {
    vector<string> temp = {"Robot starts at treasure"};
    // gr.print_listof_shortestPaths();
    return CheckValues(gr, 10, 1, 1, 1, 1, 0, temp);
}


void tests_GreedyRobot() {
    cout << "GREEDY ROBOT TESTS:" << endl;
    if (!testDefault(grDefault)) cout << "   Failed: testDefault\n"
    << grDefault << endl;
    if (!testNormal1(gr1)) cout << "   Failed: testNormal1\n"
    << gr1 << endl;
    if (!testNormal2(gr2)) cout << "   Failed: testNormal2\n"
    << gr2 << endl;
    if (!testLine1(gr3)) cout << "   Failed: testLine1\n"
    << gr3 << endl;
    if (!testLine2(gr4)) cout << "   Failed: testLine2\n"
    << gr4 << endl;
    if (!testOnTreasure(gr5)) cout << "   Failed: testOnTreasure\n"
    << gr5 << endl;
}



