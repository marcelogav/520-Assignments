#include "gtest/gtest.h"
#include <iostream>
#include <vector>
#include <cctype>
#include <numeric>      // std::accumulate
#include <iostream>
#include <math.h>
#include <assert.h>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <utilities.h>

namespace {

using namespace std;


TEST(HW5, SortByMagnitude) {

vector<double> v = {-30, 1, 3, 5, -10, 8, -12, -6};
vector<double> res = sort_by_magnitude(v);

//checking result:
   std::cout << "After sort, the vector ordered by magnitude is : ";
   for(int i=0; i < res.size(); i++) {
        cout << res.at(i) << ' ';
   }
cout << "\n";
}

/*
TEST(HW5, ReadMatrix) {
TypedArray<TypedArray<double>> mat = read_matrix_csv ("/source/test_reading.csv");
std::cout << mat << "\n";
}
*/

TEST(HW5, WriteMatrix) {
      TypedArray<TypedArray<double>> m;
          for (int i=0; i<5; i++) {
              for (int j=0; j<5; j++) {
              m.get(i).set(j, i+j+1);
              }
          }
      //cout << "check input matrix : "; 
      //cout << m << "\n";

  write_matrix_csv(m, "/source/test_CreatingFile.csv");
}


TEST(HW5, MAP) {
      
        occurrence_map("/source/MapFunction_inputFile.txt");

// check ..._output.txt for result        
}














}


