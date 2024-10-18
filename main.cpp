#include "GreedyRobot.h"
#include "Catalan.h"
#include <iostream>

using namespace std;

int main() {
    Catalan testCatalan(5);
    testCatalan.print();

    int n = testCatalan.get_n_forThisCatalan();
    int catalanNumber = testCatalan.get_catalanNumber();
    cout << n << ", " << catalanNumber << endl;
    testCatalan.set_n(6);
    testCatalan.print();
    testCatalan.set_n(0);
    testCatalan.print();
    testCatalan.set_n(-6);
    testCatalan.print();
    testCatalan.set_n(7);
    testCatalan.print();
    testCatalan.set_n(23);
    testCatalan.print();

}