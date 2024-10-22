#include "Catalan_tests.h"
#include <iostream>

using namespace std;

// bool CheckValues(Catalan cn, int n, int catalanNumber) {
//     return (
//         (cn.get_n_forThisCatalan() == n) &&
//         (cn.get_catalanNumber() == catalanNumber)
//     );
// }

// Catalan c1;
// Catalan c2(4);

// bool testDefault(Catalan c) {
//     return CheckValues(c, 0, 1);
// }

// bool testNormal1(Catalan c) {
//     return CheckValues(c, 4, 14);
// }

// void testCatalan() {
//     testDefault(c1);
//     testNormal1(c2);
// }

void CatalanTests() {
    cout << "CONSTRUCTION TEST" << endl;
    Catalan testCatalan(5);
    cout << "n: 5\nCatalan Number: 42 <- Expected" << endl;
    testCatalan.print();
    int n = testCatalan.get_n_forThisCatalan();
    int catalanNumber = testCatalan.get_catalanNumber();
    cout << "5, 42 <- Expected" << endl;
    cout << n << ", " << catalanNumber << endl;
    testCatalan.set_n(6);
    cout << "n: 6\nCatalan Number: 132 <- Expected" << endl;
    testCatalan.print();
    testCatalan.set_n(0);
    cout << "n: 0\nCatalan Number: 1 <- Expected" << endl;
    testCatalan.print();
    cout << "'n' must be a positive number (input was) -6 <- Expected" << endl;
    testCatalan.set_n(-6);
    cout << "n: 0\nCatalan Number: 1 <- Expected" << endl;
    testCatalan.print();
    cout << "Unfortunatley, 'n' greater than 6 is too large to solve :( due to factorial issues <- Expected" << endl;
    testCatalan.set_n(7);
    cout << "n: 0\nCatalan Number: 1 <- Expected" << endl;
    testCatalan.print();
    cout << "Unfortunatley, 'n' greater than 6 is too large to solve :( due to factorial issues <- Expected" << endl;
    testCatalan.set_n(23);
    cout << "n: 0\nCatalan Number: 1 <- Expected" << endl;
    testCatalan.print();

}