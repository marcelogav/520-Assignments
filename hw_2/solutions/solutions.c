#include <stdio.h>
#include <math.h>
#include "solutions.h"


// Exercise 1: cummulative sum of a sequence of values
// PV = Previous Value
// CV = Current Value

double running_total ( double CV ) 
{
  static double PV = 0;
  PV = PV + CV;
    
  return PV;
}



// Exercise 2: returns reverse of an array of N elements

int *reverse (int A[], int n)
{
int *R = (int *) calloc ( n, sizeof (int));

for (int i=0 ; i <= (n-1) ; i++)
    {  
      R[i] = A[n-1-i];
    }
    
return R;
}  



// Exercise 3: takes an array and revert it in its place

int reverse_in_place (int A[], int n)
{
int i = 0;
int j = n-1;
int temp;

while (i <= j)
    { 
      temp = A[i];
      A[i] = A[j];
      A[j] = temp;
      i++;
      j--;
    }
    
return *A;
}


//Exercise 4: Returns the # of occurrences of x in an array of N elements
    // A = an array of n elements
    // n = length of array
    // x = value to be verified

int num_occurences (int A[], int n, int x )
{
int NumOcc = 0;

for (int i=0 ; i <= (n-1) ; i++ )
    {
      if ( A[i]==x ) 
         NumOcc = NumOcc + 1; 
    }

return NumOcc;
}





