#ifndef COMPLEX
#define COMPLEX

#include <iostream>

class Complex {
    public:
    Complex(double x, double y) : real(x), imag(y) {};
    Complex(double a) : real(a), imag(0) {};

    double magnitude() const;


    double re() const;                 // HW4 - Exercise 5

    double im() const;                 // HW4 - Exercise 5

    Complex conjugate() const ;        // HW4 - Exercise 5
  

    private:
    double real, imag;
};

bool operator<(const Complex& a, const Complex& b);



Complex operator*(const Complex& a, const Complex& b);          // HW4 - Exercise 5

Complex operator+(const Complex& a, const Complex& b);          // HW4 - Exercise 5

bool operator==(const Complex& a, const Complex& b);            // HW4 - Exercise 5




#endif