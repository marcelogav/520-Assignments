#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include "dynamic_array.h"
#include "gtest/gtest.h"

#define X 1.2345


namespace {

    TEST(DynamicArray, CreateAndDestroy) {
        DynamicArray * a = DynamicArray_new();
        DynamicArray_destroy(a);
    }

    TEST(DynamicArray, DeathTests) {
        DynamicArray * a = DynamicArray_new();
        ASSERT_DEATH(DynamicArray_pop(a), ".*Assertion.*");
        ASSERT_DEATH(DynamicArray_pop_front(a), ".*Assertion.*");
        DynamicArray_destroy(a);
        ASSERT_DEATH(DynamicArray_size(a), ".*Assertion.*");
    }    

    TEST(DynamicArray, SmallIndex) {
        DynamicArray * da = DynamicArray_new();
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_set(da, 0, -X);        
        DynamicArray_set(da, 3, X);
        ASSERT_EQ(DynamicArray_size(da),4);
        ASSERT_EQ(DynamicArray_get(da,0), -X);
        ASSERT_EQ(DynamicArray_get(da,3), X);
        DynamicArray_destroy(da);
    }

    TEST(DynamicArray, BigIndex) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 8, X);
        ASSERT_EQ(DynamicArray_get(da,8), X);
        DynamicArray_destroy(da);              
    }

    TEST(DynamicArray, ReallyBig) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 400, X);
        DynamicArray_set(da, 200, X/2);        
        ASSERT_EQ(DynamicArray_get(da,200), X/2);
        ASSERT_EQ(DynamicArray_get(da,400), X);
        DynamicArray_destroy(da);              
    }  

    TEST(DynamicArray, Push) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 10 ) {
            DynamicArray_push(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_size(da),40);
        printf("Push test Intermediate Result: %s\n", 
               DynamicArray_to_string(da));
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop(da);
        }
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, PushFront) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 10 ) {
            DynamicArray_push_front(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_size(da),40);
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop_front(da);
        }
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_destroy(da);          
    } 

    TEST(DynamnicArray,ToString) {
        DynamicArray * da = DynamicArray_new();
        double x = 1.0;
        while ( x <= 5 ) {
            DynamicArray_push(da, x);  
            x += 1.0;
        }
        char * str = DynamicArray_to_string(da);
        printf("ToString Example: %s\n", str);
        ASSERT_STREQ(
            str,
            "[1.00000,2.00000,3.00000,4.00000,5.00000]"
        );
        DynamicArray_destroy(da);
        free(str);
    }

    TEST(DynamicArray, Pop) {
        DynamicArray * da = DynamicArray_new();
        double x;
        DynamicArray_push(da, X);  
        DynamicArray_push(da, X);  
        x = DynamicArray_pop(da);  
        ASSERT_EQ(DynamicArray_size(da),1);
        ASSERT_EQ(x,X);
        ASSERT_EQ(DynamicArray_get(da,1), 0.0);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, Map) {
        DynamicArray * t = DynamicArray_new(),
                     * y;
        double s = 0.0;
        for ( int i=0; i<628; i++ ) {
            DynamicArray_set(t, i, s);
            s = s + 0.1;
        }
        y = DynamicArray_map(t,sin);
        for (int i=0; i<DynamicArray_size(t); i++) {
            ASSERT_NEAR(
                DynamicArray_get(y,i),sin(0.1*i), 0.0001
            );
        }
        DynamicArray_destroy(t);    
        DynamicArray_destroy(y);                    
    }         

// Tests for HW_3 exercises ***********************************************

// Exercise 1 - Tests for Mathematical Operations

  TEST(DynamicArray, MathOperations1) {
        DynamicArray * da = DynamicArray_new();
        double x[] = {1,5,-3,21,6};
        for(int i=0;i<5;i++) {
                DynamicArray_push(da, x[i]);
            }
        ASSERT_EQ(DynamicArray_min(da),-3);  
        ASSERT_EQ(DynamicArray_max(da),21);
        ASSERT_EQ(DynamicArray_mean(da),6);
        ASSERT_EQ(DynamicArray_median(da),5);
        ASSERT_EQ(DynamicArray_sum(da),30);
        DynamicArray_destroy(da);
        free(da);
    } 

  // test median of an array with even number of elements
  TEST(DynamicArray, MathOperations2) {
        DynamicArray * da = DynamicArray_new();
        double y[] = {3,8,4,2,12,15};
        for(int i=0;i<6;i++) {
                DynamicArray_push(da, y[i]);
            }
        ASSERT_EQ(DynamicArray_median(da),6);
        DynamicArray_destroy(da);  
        free(da);        
    }


// Exercise 2 - _last / _first

  TEST(DynamicArray, last_or_first) {
        DynamicArray * da = DynamicArray_new();
        double x[] = {1,5,-3,21,6,15,30,53};
        for(int i=0;i<8;i++) {
            DynamicArray_push(da, x[i]);
            }
        ASSERT_EQ(DynamicArray_first(da),1);  
        ASSERT_EQ(DynamicArray_last(da),53);
        DynamicArray_destroy(da);
        free(da);
    } 


// Exercise 3 - _copy

  TEST(DynamicArray, copy_array) {
        DynamicArray * da = DynamicArray_new();
        double x[] = {1,5,-3,21,6,15,30,53};
        for(int i=0;i<8;i++) {
                DynamicArray_push(da, x[i]);
            }
        ASSERT_EQ(DynamicArray_get(da,2),-3);
        ASSERT_EQ(DynamicArray_get(da,5),15);
        ASSERT_EQ(DynamicArray_get(da,1),5);
        ASSERT_EQ(DynamicArray_get(da,7),53);
        ASSERT_EQ(DynamicArray_size(da),8);
        DynamicArray_destroy(da);
        free(da);
    } 


// Exercise 4 - _range

  TEST(DynamicArray, range) {
        DynamicArray * a = DynamicArray_range(0, 1, 0.1); 
        DynamicArray * b = DynamicArray_range(1.1, 2.0, 0.1); 
        ASSERT_NEAR(DynamicArray_get(a,3),0.3,0.01);
        ASSERT_NEAR(DynamicArray_get(a,0),0,0.01);
        ASSERT_NEAR(DynamicArray_get(b,9),2,0.01);     
        ASSERT_NEAR(DynamicArray_get(b,1),1.2,0.01);
        DynamicArray_destroy(a);
        free(a);
        DynamicArray_destroy(b);
        free(b);
    } 


// Exercise 5 - _concat

  TEST(DynamicArray, concatenate) {
        DynamicArray * a = DynamicArray_range(0, 1, 0.1);
        DynamicArray * b = DynamicArray_range(1.1, 2, 0.1);
        DynamicArray * c = DynamicArray_concat(a, b);
        ASSERT_EQ(DynamicArray_size(c),21);
        ASSERT_NEAR(DynamicArray_get(c,0),0,0.0001);
        ASSERT_NEAR(DynamicArray_get(c,3),0.3,0.0001);
        ASSERT_NEAR(DynamicArray_get(c,9),0.9,0.0001);
        ASSERT_NEAR(DynamicArray_get(c,10),1,0.0001);
        ASSERT_NEAR(DynamicArray_get(c,11),1.1,0.0001);
        ASSERT_NEAR(DynamicArray_get(c,15),1.5,0.0001);
        ASSERT_NEAR(DynamicArray_get(c,20),2,0.0001);   
        DynamicArray_destroy(a);
        DynamicArray_destroy(b);
        DynamicArray_destroy(c);
        free(a);
        free(b);
        free(c);
    }


// Exercise 6 - _take

  TEST(DynamicArray, take_subarray) {
        DynamicArray * a = DynamicArray_range(1, 5, 1);
        DynamicArray * b = DynamicArray_take(a,2);   //{1,2}  
        DynamicArray * c = DynamicArray_take(a,-2);  //{4,5} 
        DynamicArray * d = DynamicArray_take(a,7);   //{1,2,3,4,5,0,0}
        ASSERT_EQ(DynamicArray_get(b,0),1);
        ASSERT_EQ(DynamicArray_get(b,1),2);
        ASSERT_EQ(DynamicArray_get(c,0),4);
        ASSERT_EQ(DynamicArray_get(c,1),5);
        ASSERT_EQ(DynamicArray_get(d,0),1);
        ASSERT_EQ(DynamicArray_get(d,1),2);
        ASSERT_EQ(DynamicArray_get(d,2),3);
        ASSERT_EQ(DynamicArray_get(d,3),4);
        ASSERT_EQ(DynamicArray_get(d,4),5);
        ASSERT_EQ(DynamicArray_get(d,5),0);
        ASSERT_EQ(DynamicArray_get(d,6),0);
        DynamicArray_destroy(a);
        DynamicArray_destroy(b);
        DynamicArray_destroy(c);
        DynamicArray_destroy(d);
        free(a);
        free(b);
        free(c);
        free(d);
    }

// Exercise 7 - Test 

  TEST(DynamicArray, Test_Ex_7) {
    DynamicArray * a = DynamicArray_range(0, 1, 0.1);
    DynamicArray * b = DynamicArray_range(1.1, 2, 0.1);
    DynamicArray * c = DynamicArray_concat(a, b);
    ASSERT_EQ(DynamicArray_is_valid(a), 1);
    ASSERT_EQ(DynamicArray_num_arrays(), 29);
    //DynamicArray_destroy_all();
    //ASSERT_EQ(DynamicArray_is_valid(a), 0);
    //ASSERT_EQ(DynamicArray_num_arrays(), 0);
    free(a);
    free(b);
    free(c);
    }



}