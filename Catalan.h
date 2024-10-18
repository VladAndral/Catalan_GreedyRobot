#ifndef CATALAN_H_ // Need underscore at the end
#define CATALAN_H_

#include <iostream>

using namespace std;

/*
    A Catalan number cna be described as the number of non-crossing partitions that can be made in an n-sided shape
    (includes empty and full set).
*/
class Catalan {

    public:

        Catalan();
        Catalan(int n);

        int get_n_forThisCatalan() const;
        int get_catalanNumber() const;
        void set_n(int n);
        void print();

        friend ostream& operator<<(ostream& stream, const Catalan& catalan);
        friend istream& operator>>(istream& stream, Catalan& catalan);



    private:
        int _n;
        int _catalanNumber;
        int factorial(int n);
        int recursiveFactorial(int n);
        int calculateCatalan(int n);



};


#endif