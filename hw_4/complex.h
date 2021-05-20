#ifndef COMPLEX
#define COMPLEX

#include <iostream>

class Complex {
    public:
    Complex(double x, double y) : re(x), im(y) {}
    Complex(double a) : re(a), im(0) {};

    double magnitude() const;

    double re() const ;
/*
    double im() const ;

    Complex conjugate(const Complex a) ;

    Complex operator*(const Complex& a, const Complex& b);

    Complex operator+(const Complex& a, const Complex& b);

    bool operator==(const Complex& a, const Complex& b);


    private:
    double re, im;
} 
*/
bool operator<(const Complex& a, const Complex& b);

#endif