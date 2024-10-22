#include "GreedyRobot.h"
#include <iostream>

using namespace std;

GreedyRobot grDefault;
GreedyRobot gr1(1, 1, 1, 2, 2);
GreedyRobot gr2(1, 1, 1, 3, 3);

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
    vector<string> temp = {"ENEN", "NENE"};
    return CheckValues(gr, 1, 1, 1, 3, 3, 4, temp);
}


void tests_GreedyRobot() {
    if (!testDefault(grDefault)) cout << "   Failed: testDefault\n"
    << grDefault << endl;
    if (!testNormal1(gr1)) cout << "   Failed: testNormal1\n"
    << gr1 << endl;
    if (!testNormal2(gr2)) cout << "   Failed: testNormal2\n"
    << gr2 << endl;

}



