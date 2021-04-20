#ifndef COMPLEX_H
#define COMPLEX_H

/*! @file */

/*! \breif Complex object and method definitions
 *
 *  A Complex object is a struct with two members, one of them is denoted real, and
 *  the other denoted im. There are various methods that take complex(es) and do 
 *  arithmetical operations with them and return another complex or escalar.
 */
typedef struct {
    double real;
    double im;
} Complex;

/*! Add two complex together
 *  \param a The first term
 *  \param b The second term
 */
Complex add ( Complex a, Complex b );

/*! Negate a complex 
 *  \param a is the only term, the function will return -a
 */
Complex negate ( Complex a );

/*! Multiply two Complex together
 *  \param a The first term
 *  \param b The second term
 */
Complex multiply ( Complex a, Complex b );

/*! Magnitude of a Complex 
 *  \param a is the only term, the function will return its size
 */
double magnitude ( Complex a );

#endif