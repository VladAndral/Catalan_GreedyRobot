#include "Catalan.h"
#include <iostream>
#include <cmath>

using namespace std;

int main(int argc, char *argv[]) {
    Catalan toReturn(stoi(argv[1]));
    cout << toReturn.get_catalanNumber();
}

/*
        CONSTRUCTOR
*/

Catalan::Catalan() : _n(0), _catalanNumber(1) { }

Catalan::Catalan(int n) : _n(0), _catalanNumber(1) {
    if (n < 0) {
        cout << "'n' must be a positive number (input was) " << n << endl;
    } else if (n > 19) {
        cout << "Unfortunatley, 'n' greater than 19 is too large to solve due to integer overflow :(" << endl;
    }
    _catalanNumber = _calculateCatalan(n);
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
    } else if (n > 19) {
        cout << "Unfortunatley, 'n' greater than 19 is too large to solve due to integer overflow :(" << endl;
    } else {
        _n = n;
        _catalanNumber = _calculateCatalan(n);
    }
}

void Catalan::print() {
    cout << "catalan " << get_n_forThisCatalan() << "\n" << get_catalanNumber() << endl;
}


/*
        CALCULATIONS
*/

int Catalan::_calculateCatalan(int n) {
    return _recursive_calculateCatalan(n);
}

int Catalan::_recursive_calculateCatalan(int n) {
    // n is n+1 in this case!
    /* 
        Base Case
     */
    if (n == 0) {
        return 1;
    } else {
        n -= 1;
        int toReturn = 0;
        for (int i = 0; i <= n; i++) {
            toReturn += _recursive_calculateCatalan(i)*_recursive_calculateCatalan(n-i);
        }
        return toReturn;
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

