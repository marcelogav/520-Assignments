#include <math.h>
#include "complex.h"

double Complex::magnitude() const {
    return sqrt(real*real + imag*imag);
}

bool operator<(const Complex& a, const Complex& b) {
    return a.magnitude() < b.magnitude();
}

// Exercise 5 ****************************************************
double Complex::re() const {
    return real;
}

double Complex::im() const {
    return imag;
} 

Complex Complex::conjugate() const {
    Complex b = {real,-imag};
    return b;
}

Complex operator*(const Complex& a, const Complex& b) {
    Complex c = {(a.re()*b.re()-a.im()*b.im()),(a.re()*b.im()+b.re()*a.im())};
    return c;
}

Complex operator+(const Complex& a, const Complex& b) {
    Complex c = {(a.re()+b.re()), (a.im()+b.im())};
    return c;
}

bool operator==(const Complex& a, const Complex& b) {
      if ( a.re() != b.re() ) {
        return false;
       }
        if ( a.im() != b.im() ) {
            return false;
        }
    return true;
}
