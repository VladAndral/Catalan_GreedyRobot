#include "GreedyRobot.h"
#include "GreedyRobot_tests.h"
#include "Catalan.h"
// #include "GreedyRobot_tests.cpp"
#include <iostream>

using namespace std;

void CatalanTests();

int main() {
    // CatalanTests();
    // tests_GreedyRobot();

    // GreedyRobot testRobot(1, 0, 0, -10, 10);
    // cout << testRobot << endl;
    // testRobot.print_listof_shortestPaths();



    GreedyRobot testRobot;
    cout << "Enter your path and restraint [max, x1, y1, x2, y2]" << endl;
    cin >> testRobot; //TODO
    // cout << testRobot << endl;
    
    // cout << testRobot << endl;
    testRobot.print_infoNoPaths();
    cout << "Would you like to print list of paths? (y/n)" << endl;
    string printPathLen;
    cin >> printPathLen;
    if (printPathLen == "y") {
        testRobot.print_listof_shortestPaths();
    }


}