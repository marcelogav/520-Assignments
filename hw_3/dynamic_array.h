#ifndef _DYNAMIC_ARRAY
#define _DYNAMIC_ARRAY

#define DYNAMIC_ARRAY_INITIAL_CAPACITY 10

typedef struct {
    int capacity,
        origin,
        end;
    double * buffer;
} DynamicArray;

extern int num_array;                 // introduce a global var to count total arrays created
extern DynamicArray * destroy;        // introduce a global pointer to store used locations by created arrays

/* Constructors / Destructors ************************************************/

DynamicArray * DynamicArray_new(void);
void DynamicArray_destroy(DynamicArray *);

/* Getters / Setters *********************************************************/

void DynamicArray_set(DynamicArray *, int, double);
double DynamicArray_get(const DynamicArray *, int);
int DynamicArray_size(const DynamicArray *);

/* Printing ******************************************************************/

char * DynamicArray_to_string(const DynamicArray *);
void DynamicArray_print_debug_info(const DynamicArray *);

/* Operations ****************************************************************/

void DynamicArray_push(DynamicArray *, double);
void DynamicArray_push_front(DynamicArray *, double);

double DynamicArray_pop(DynamicArray *);
double DynamicArray_pop_front(DynamicArray *);

DynamicArray * DynamicArray_map ( const DynamicArray *, double (*) (double) );

/* EXERCISES: ********************************************************/

/*! Return the first value in the given array. Throw a runtime error if the array is empty.
 *  \param da The array
 */
double DynamicArray_last ( const DynamicArray * da );

/*! Return the first last in the given array. Throw a runtime error if the array is empty.
 *  \param da The array
 */
double DynamicArray_first ( const DynamicArray * da );

/*! Return a copy of the array.
 *  \param da The array
 */
DynamicArray * DynamicArray_copy ( const DynamicArray * da );

/*! Return a new array whose elements span the given range and are step units apart.
 *  \param a The first value
 *  \param b The second value
 *  \param step The different between consecutive elements.
 */
DynamicArray * DynamicArray_range ( double a, double b, double step);

/*! Return a new array that is the concatenation of the given arrays. 
 *  \param a The first array
 *  \param b The second array
 */
DynamicArray * DynamicArray_concat ( const DynamicArray * a, const DynamicArray * b );

/*! Mathematical operations
  */
double DynamicArray_min ( const DynamicArray * da );
double DynamicArray_max ( const DynamicArray * da );
double DynamicArray_mean ( const DynamicArray * da );
double DynamicArray_median ( const DynamicArray * da );
double DynamicArray_sum ( const DynamicArray * da );

/*! Returns 1 if the array is valid (meaning its buffer is not NULL) and 0 otherwize.
 */
int DynamicArray_is_valid(const DynamicArray * da);

/*! Returns the number of arrays that have been constructed to far.
 */
int DynamicArray_num_arrays();

/*! Destroys all arrays that have been constructed so far.
 */
int DynamicArray_destroy_all();


/*! Returns a sub-array of n elements. 
*/
DynamicArray * DynamicArray_subarray(DynamicArray * da, int, int);

/*! Returns a sub-array of n elements. If argument is positive, it takes from beginning. If it's negative it takes from the end.
    Fullfil sub-array with 0 if there are not enough elements.
 */
DynamicArray * DynamicArray_take(DynamicArray * da, int a);

/* Exercise 7
For this item we have created a global variable and introduced a new counter when new
array is created.
We also introduced a new pointer to store all used addresses, which will be used by the 
new method _destroy_all.
The new functions declarations for this item (_num arrays, _destroy_all, _is_valid) were already
declared in the original .h file.
*/


#endif
