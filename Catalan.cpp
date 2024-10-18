#include "Catalan.h"
#include <iostream>
#include <cmath>

using namespace std;

/*
        CONSTRUCTOR
*/

Catalan::Catalan() : _n(0), _catalanNumber(1) { }

Catalan::Catalan(int n) : _n(0), _catalanNumber(1) {
    if (n < 0) {
        cout << "'n' must be a positive number (input was) " << n << endl;
    } else if (n > 6) {
        cout << "Unfortunatley, 'n' greater than 6 is too large to solve :( due to factorial issues" << endl;
    }
    _catalanNumber = calculateCatalan(n);
    _n = n;
}

/*
        GETS AND SETS
*/

int Catalan::get_n_forThisCatalan() const {
    return _n;
}

int Catalan::get_catalanNumber() const {
    return _catalanNumber;
}

void Catalan::set_n(int n) {
    if (n < 0) {
        cout << "'n' must be a positive number (input was) " << n << endl;
    } else if (n > 6) {
        cout << "Unfortunatley, 'n' greater than 6 is too large to solve :( due to factorial issues" << endl;
    } else {
        _n = n;
        _catalanNumber = calculateCatalan(n);
    }
}

void Catalan::print() {
    cout << "n: " << get_n_forThisCatalan() << " Catalan Number: " << get_catalanNumber() << endl;

}

/*
        CALCULATIONS
*/

int Catalan::calculateCatalan(int n) {
    if (n == 0) {
        return 1;
    }
    int numerator = factorial(2*n);
    int denominator = factorial(n+1)*factorial(n);
    return numerator/denominator; // integer division
}

int Catalan::factorial(int n) {
    return recursiveFactorial(n);
}

int Catalan::recursiveFactorial(int n) {
    if (n == 1) {
        return 1;
    } else {
        return n*recursiveFactorial(n-1);
    }
}


/*
        OPERATOR OVERLOADS
*/

ostream& operator<<(ostream& stream, const Catalan& catalan) {

    stream << "n: " << catalan.get_n_forThisCatalan() << " Catalan Number: " << catalan.get_catalanNumber();
    return stream;
}


istream& operator>>(istream& stream, Catalan& catalan) {

    int n;
    stream >> n;
    catalan.set_n(n);
    return stream;
}

