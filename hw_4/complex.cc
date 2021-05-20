#include <math.h>
#include "complex.h"

double Complex::magnitude() const {

    return sqrt(re*re + im*im);

}

bool operator<(const Complex& a, const Complex& b) {

    return a.magnitude() < b.magnitude();

}

// Exercise 5 *****************************************************

double Complex::re() const {
    return re;
}
/*
double Complex::im() const{
    return im(a);
} 

Complex Complex::conjugate() {
    return (re(a),-im(a));
}

Complex operator*(const Complex a, const Complex b) {
    return ((re(a)*re(b)-im(a)*im(b)),(re(a)*im(b)+re(b)*im(a)));
}

Complex operator+(const Complex a, const Complex b) {
    return ((re(a)+re(b), im(a)+im(b));
}

bool operator==(const Complex a, const Complex b) {
      if ( re(a) != re(b) ) {
        return false;
       }
        if ( im(a) != im(b) ) {
            return false;
        }
    return true;
}
*/