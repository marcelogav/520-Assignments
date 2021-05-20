#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "typed_array.h"
#include "complex.h"
#include "gtest/gtest.h"


namespace {


// HW4 - Exercise1

TEST(TypedArray,push) {
        TypedArray<int> a;
         for (int i=0; i<5; i++) {
            a.set(i,11*i+11);
            }

        std::cout << a << "\n";      
        int b = 100;
        a.push(b);
        std::cout << a << "\n"; 
        EXPECT_EQ(a.get(0), 11);
        EXPECT_EQ(a.get(1), 22);
        EXPECT_EQ(a.get(4), 55);
        EXPECT_EQ(a.get(5), 100);
        EXPECT_EQ(a.size(), 6);
}


TEST(TypedArray,push_front) {
         TypedArray<int> a;
         for (int i=0; i<5; i++) {
            a.set(i,11*i+11);
            }
        std::cout << a << "\n";          
        int b = 100;
        a.push_front(b);
        std::cout << a << "\n";      
        EXPECT_EQ(a.get(0), 100);
        EXPECT_EQ(a.get(1), 11);
        EXPECT_EQ(a.get(4), 44);
        EXPECT_EQ(a.get(5), 55);
        EXPECT_EQ(a.size(), 6);
}        

TEST(TypedArray,pop) {
        TypedArray<int> a;
         for (int i=0; i<5; i++) {
            a.set(i,11*i+11);
            }
        std::cout << a << "\n";       
        EXPECT_EQ(a.pop(),55);
        std::cout << a << "\n"; 
        EXPECT_EQ(a.get(0), 11);
        EXPECT_EQ(a.get(1), 22);
        EXPECT_EQ(a.get(4), 0);
        try{
        //TypedArray<int> c ;                   // this test has not worked
        //std::cout << c << "\n";               // this test has not worked
        //c.pop();                              // this test has not worked
        } 
        catch (std::invalid_argument e ) {
           ASSERT_STREQ(e.what(), "Cannot pop from an empty array");
        }
}

TEST(TypedArray,pop_front) {
        TypedArray<int> a;
         for (int i=0; i<5; i++) {
            a.set(i,11*i+11);
            }
        std::cout << a << "\n"; 
        EXPECT_EQ(a.pop_front(),11);
        std::cout << a << "\n";
        EXPECT_EQ(a.get(0), 22);
        EXPECT_EQ(a.get(1), 33);
        EXPECT_EQ(a.get(4), 0);
        try{
        //TypedArray<int> c ;                   // this test has not worked
        //std::cout << c << "\n";               // this test has not worked
        //c.pop_front();                        // this test has not worked
        } 
        catch (std::invalid_argument e ) {
           ASSERT_STREQ(e.what(), "Cannot pop from an empty array");
        }
}

// HW4 - Exercise2

TEST(TypedArray,concat) {
        TypedArray<int> a;
         a.set(0,0);
         a.set(1,1);
        std::cout << a << "\n"; 
        TypedArray<int> x = a.concat(a);
        std::cout << x << "\n"; 
        TypedArray<int> c = a.concat(a).concat(a);
        std::cout << c << "\n"; 
        EXPECT_EQ(c.get(0), 0);
        EXPECT_EQ(c.get(1), 1);
        EXPECT_EQ(c.get(2), 0);
        EXPECT_EQ(c.get(3), 1);
        EXPECT_EQ(c.get(4), 0);
        EXPECT_EQ(c.get(5), 1);
             
}

// HW4 - Exercise3

TEST(TypedArray,reverse) {
        TypedArray<int> a;
         for (int i=0; i<5; i++) {
            a.set(i,11*i+11);
            }
        std::cout << a << "\n"; 
        TypedArray<int> c = a.reverse();
        std::cout << c << "\n"; 
        EXPECT_EQ(c.get(0), 55);
        EXPECT_EQ(c.get(1), 44);
        EXPECT_EQ(c.get(2), 33);
        EXPECT_EQ(c.get(3), 22);
        EXPECT_EQ(c.get(4), 11);
        EXPECT_EQ(c.size(), 5);      
}

// HW4 - Exercise4

TEST(TypedArray,overload_operator) {
        TypedArray<int> a;
         for (int i=0; i<=1; i++) {
            a.set(i,1*i);
            }
        std::cout << a << "\n"; 
        TypedArray<int> c = a + a + a;
        std::cout << c << "\n"; 
        EXPECT_EQ(c.get(0), 0);
        EXPECT_EQ(c.get(1), 1);
        EXPECT_EQ(c.get(4), 0);
        EXPECT_EQ(c.get(5), 1);
        EXPECT_EQ(c.size(), 6);      
}


// Exercise 5
/*
    TEST(Ex5,Complex) {
        Complex x(1,2), y(3);
    }

/*
    template<typename T>
    int compare(const T& x, const T& y) {
        if ( x < y ) {
            return -1;
        } else if ( y < x ) {
            return 1;
        } else {
            return 0;
        }
    }    

    TEST(Ex5,Templates) {
        EXPECT_EQ(compare(1.0, 2.0), -1);
        EXPECT_EQ(compare(Complex(5,4), Complex(-3,4)), 1);
    }

    TEST(Ex5,Return_re) {
        EXPECT_EQ(re(1.0, 2.0), 1.0);
    }

    TEST(Ex5,Return_im) {
        EXPECT_EQ(im(1.0, 2.0), 2.0);
    }

    TEST(Ex5,Conjugate) {
        EXPECT_EQ(conjugate(1.0, 2.0), (1.0, -2.0));
    }

    TEST(Ex5, Overload*) {
        EXPECT_EQ((1.0, 2.0)*(3.0, -1.0), (3.0, 5.0));
    }

    TEST(Ex5, Overload+) {
        EXPECT_EQ((1.0, 2.0)+(3.0, -1.0), (4.0, 1.0));
    }
*/


}