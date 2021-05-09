#include "dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stddef.h>


 int num_array = 0;                                          // introduce a global var to count total arrays created
 DynamicArray * GlobalDestroy = DynamicArray_new();          // introduce a global pointer to store used locations by created arrays

/* private functions *********************************************************/

/* Position in the buffer of the array element at position index */
static int index_to_offset ( const DynamicArray * da, int index ) {
    
    return index + da->origin;
}

/* Position of the element at buffer position 'offset' */
static int offset_to_index ( const DynamicArray * da, int offset ) {
    return offset - da->origin;
}

/* Non-zero if and only if offset lies ouside the buffer */
static int out_of_buffer ( DynamicArray * da, int offset ) {
    return offset < 0 || offset >= da->capacity;
}

/* Makes a new buffer that is twice the size of the old buffer,
   copies the old information into the new buffer, and deletes
   the old buffer */
static void extend_buffer ( DynamicArray * da ) {

    double * temp = (double *) calloc ( 2 * da->capacity, sizeof(double) );
    int new_origin = da->capacity - (da->end - da->origin)/2,
           new_end = new_origin + (da->end - da->origin);

    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        temp[new_origin+i] = DynamicArray_get(da,i);
    }

    free(da->buffer);
    da->buffer = temp;
    
    da->capacity = 2 * da->capacity;
    da->origin = new_origin;
    da->end = new_end;
    
    return;

}

/* public functions **********************************************************/

DynamicArray * DynamicArray_new(void) {
    DynamicArray * da = (DynamicArray *) malloc(sizeof(DynamicArray));
    da->capacity = DYNAMIC_ARRAY_INITIAL_CAPACITY;    
    da->buffer = (double *) calloc ( da->capacity, sizeof(double) ); 
    da->origin = da->capacity / 2;
    da->end = da->origin;
    num_array = num_array + 1;
    return da;
    
}

void DynamicArray_destroy(DynamicArray * da) {
    free(da->buffer);
    da->buffer = NULL;
    return;
}

int DynamicArray_size(const DynamicArray * da) {
    assert(da->buffer != NULL);
    return da->end - da->origin;
}

char * DynamicArray_to_string(const DynamicArray * da) {
    assert(da->buffer != NULL);
    char * str = (char *) calloc (20,DynamicArray_size(da)),
         temp[20];
    int j = 1;
    str[0] = '[';
    for ( int i=0; i < DynamicArray_size(da); i++ ) {
        if ( DynamicArray_get(da,i) == 0 ) {
            snprintf ( temp, 20, "0" );
        } else {
            snprintf ( temp, 20, "%.5lf", DynamicArray_get(da,i) ); 
        }
        if ( i < DynamicArray_size(da) - 1 ) {
            sprintf( str + j, "%s,", temp);
            j += strlen(temp) + 1;
        } else {
            sprintf( str + j, "%s", temp);
            j += strlen(temp);
        }

    }
    str[j] = ']';
    return str;
}

void DynamicArray_print_debug_info(const DynamicArray * da) {

    char * s = DynamicArray_to_string(da);
    printf ( "  %s\n", s);
    printf ( "  capacity: %d\n  origin: %d\n  end: %d\n  size: %d\n\n",
      da->capacity, 
      da->origin, 
      da->end,
      DynamicArray_size(da));

    free(s);

}

void DynamicArray_set(DynamicArray * da, int index, double value) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    while ( out_of_buffer(da, index_to_offset(da, index) ) ) {
        extend_buffer(da);
    }
    da->buffer[index_to_offset(da, index)] = value;
     if ( index >= DynamicArray_size(da) ) {
        da->end = index_to_offset(da,index+1);
    }

}

double DynamicArray_get(const DynamicArray * da, int index) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    if ( index >= DynamicArray_size(da) ) {
        return 0;
    } else {
        return da->buffer[index_to_offset(da,index)];
    }
}

void DynamicArray_push(DynamicArray * da, double value ) {
    DynamicArray_set(da, DynamicArray_size(da), value );
}

void DynamicArray_push_front(DynamicArray * da, double value) {
    assert(da->buffer != NULL);
    while ( da->origin == 0 ) {
        extend_buffer(da);
    }
    da->origin--;
    DynamicArray_set(da,0,value);
}

double DynamicArray_pop(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_get(da, DynamicArray_size(da)-1);
    DynamicArray_set(da, DynamicArray_size(da)-1, 0.0);
    da->end--;
    return value;
}

double DynamicArray_pop_front(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_get(da, 0);
    da->origin++;
    return value;    
}

DynamicArray * DynamicArray_map(const DynamicArray * da, double (*f) (double)) {
    assert(da->buffer != NULL);
    DynamicArray * result = DynamicArray_new();

    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        DynamicArray_set(result, i, f(DynamicArray_get(da, i)));
    }
    return result;
}

DynamicArray * DynamicArray_subarray(DynamicArray * da, int a, int b) {

  assert(da->buffer != NULL);
  assert(b >= a);

  DynamicArray * result = DynamicArray_new();

  for (int i=a; i<b; i++) {
      DynamicArray_push(result,DynamicArray_get(da, i));
  }
  return result;
}


/* HW3 exercises *************************************************/

// Exercise 1

//MIN
double DynamicArray_min ( const DynamicArray * da )
{
assert(da->buffer != NULL);

int location=0;
for ( int i=1; i<DynamicArray_size(da); i++ ) 
        {
        if ( da->buffer[index_to_offset(da,location)] > da->buffer[index_to_offset(da,i)] )
            {
            location = i;
            }
        }

return da->buffer[index_to_offset(da,location)];
}

//MAX
double DynamicArray_max ( const DynamicArray * da )
{
assert(da->buffer != NULL);

int location=0;
for ( int i=1; i<DynamicArray_size(da); i++ ) 
        {
        if ( da->buffer[index_to_offset(da,location)] < da->buffer[index_to_offset(da,i)] )
            {
            location = i;
            }
        }

return da->buffer[index_to_offset(da,location)];
}

//MEAN
double DynamicArray_mean ( const DynamicArray * da )
{
assert(da->buffer != NULL);
double sum = 0;
for ( int i=0; i<DynamicArray_size(da); i++ ) 
        {
        sum = sum + da->buffer[index_to_offset(da,i)];
        }

return sum/DynamicArray_size(da);
}

//MEDIAM
double DynamicArray_median ( const DynamicArray * da )
{
assert(da->buffer != NULL);
double result=0;
int mod = (DynamicArray_size(da)%2);
int div = (DynamicArray_size(da)/2);

for ( int i=0; i<DynamicArray_size(da); i++ ) 
        {
        for ( int j=0; j<DynamicArray_size(da); j++)
            {
            if (da->buffer[index_to_offset(da,j)] > da->buffer[index_to_offset(da,i)])
                    {
                        double tmp = da->buffer[index_to_offset(da,i)];
                        da->buffer[index_to_offset(da,i)] = da->buffer[index_to_offset(da,j)];
                        da->buffer[index_to_offset(da,j)] = tmp;
                    }  
            }
        }

if (mod != 0) { 
    result = da->buffer[index_to_offset(da,div)]; 
    }
    else { 
         result = ( da->buffer[index_to_offset(da,div)] + da->buffer[index_to_offset(da,div-1)] ) / 2; 
         }

return result;
}

//SUM
double DynamicArray_sum ( const DynamicArray * da )
{
double sum = 0;
for ( int i=0; i<DynamicArray_size(da); i++ ) 
        {
        sum = sum + da->buffer[index_to_offset(da,i)];
        }

return sum;
}


// Exercise 2

double DynamicArray_last ( const DynamicArray * da )
{
assert(da->buffer != NULL);
return da->buffer[da->end-1];
}

double DynamicArray_first ( const DynamicArray * da )
{
assert(da->buffer != NULL);
return da->buffer[da->origin];
}


// Exercise 3

DynamicArray * DynamicArray_copy ( const DynamicArray * da )
{
DynamicArray * da_copy = DynamicArray_new();

for (int i=0; i < DynamicArray_size(da); i++)
    { 
    DynamicArray_push(da_copy,DynamicArray_get(da,i));   
    }

for (int i=0; i < DynamicArray_size(da); i++) {                                       //Exercise 7
DynamicArray_push(GlobalDestroy,da_copy->buffer[index_to_offset(da_copy,i)]);         //Exercise 7
}
return da_copy;
}


// Exercise 4

DynamicArray * DynamicArray_range ( double a, double b, double step)
{
assert(b >= a);
DynamicArray * da = DynamicArray_new(); 

double value = a;
DynamicArray_push(da, value);

    while ( fabs(value - b) > 0.05 ) 
        {
        value = value + step;
        DynamicArray_push(da, value);
        }  

for (int i=0; i < DynamicArray_size(da); i++) {                                       //Exercise 7
DynamicArray_push(GlobalDestroy,da->buffer[index_to_offset(da,i)]);                   //Exercise 7
}
return da;
}


// Exercise 5

DynamicArray * DynamicArray_concat ( const DynamicArray * a, const DynamicArray * b )
{
DynamicArray * da = DynamicArray_new();

for (int aux = 0; aux < (DynamicArray_size(a)+DynamicArray_size(b)) ; aux++)
    {
        if (aux < DynamicArray_size(a)) {
        double value1 = DynamicArray_get(a, aux);
        DynamicArray_set(da, aux, value1);
        }

        if (aux < DynamicArray_size(b)) {
        double value2 = DynamicArray_get(b, aux);
        DynamicArray_set(da, DynamicArray_size(a)+aux, value2);
        }
   }  

for (int i=0; i < DynamicArray_size(da); i++) {                                       //Exercise 7
DynamicArray_push(GlobalDestroy,da->buffer[index_to_offset(da,i)]);                   //Exercise 7
}
return da;
}


// Exercise 6

DynamicArray * DynamicArray_take(DynamicArray * da, int a)
{
DynamicArray * sub = DynamicArray_new(); 

if (a >= 0) {
sub = DynamicArray_subarray( da, 0, a);
}
    else {
    sub = DynamicArray_subarray( da, (DynamicArray_size(da)+a), (DynamicArray_size(da)));    
    }

for (int i=0; i < DynamicArray_size(da); i++) {                                       //Exercise 7
DynamicArray_push(GlobalDestroy,da->buffer[index_to_offset(da,i)]);                   //Exercise 7
}
return sub;
}


// Exercise 7
/*
For this item we have created a global variable and introduced a new counter when new
array is created.
We also introduced a new pointer to store all used addresses, which will be used by the 
new method _destroy_all.

***  I was not able to make Exercise 7 code works, despite the method _num_arrays which is the one working ******

*/

int DynamicArray_num_arrays()
{
return num_array;
}


void DynamicArray_destroy_all()
{
for (int i = GlobalDestroy->origin; i <= GlobalDestroy->capacity; i++) 
{
GlobalDestroy->buffer[i] = 0;
}
//free(GlobalDestroy);     // this line will generate a segmentation fault (for _is_valid procedure)

DynamicArray_print_debug_info(GlobalDestroy); // I created a global pointer (GlobalDestroy) with the expectation that it could help to de-allocate all arrays at once, but it's not working...

return;
}


int DynamicArray_is_valid(const DynamicArray * da)
{
double confirm;  

if (da->buffer == NULL) {                   //this boolean comparison seems no to be working, as my GlobalDestroy is not helping to de-allocate used arrays
    confirm = 0;
    num_array = 0;
    }
    else {
       confirm = 1;
       }
return confirm;

}








