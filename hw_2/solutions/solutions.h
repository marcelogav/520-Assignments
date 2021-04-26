#ifndef SOLUTIONS_H
#define SOLUTIONS_H

#include <stdlib.h>


// This file contains the solution for 4 exercises in homework 2
 
// Exercise 1: cummulative sum of a sequence of values
    // PV = Previous Value
    // CV = Current Value
    // CV will be added to the PV (cummulated value of numerical sequence) 

        double running_total ( double CV );



//Exercise 2: Returns a new array that is the reverse of an array with N elements
    // A = an array of n elements

        int* reverse (int A[], int n );



//Exercise 3: Returns the reverse of an array with N elements (reverses array in its place)
    // A = an array of n elements

        int reverse_in_place (int A[], int n );



//Exercise 4: Returns the # of occurrences of x in an array of N elements
    // A = an array of n elements
    // n = length of array
    // x = value to be verified

        int num_occurences (int A[], int n, int x );



#endif