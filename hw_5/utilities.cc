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
#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"
#include <cstring>

using namespace std;

//HW5 - Exercise 1

vector<double> sort_by_magnitude (vector<double> v) {

sort(v.begin(), v.end(), [](double x, double y) {return sqrt(x*x)<sqrt(y*y);} );

return v;
}

/*

// HW5 - Exercise 2.1
TypedArray<TypedArray<double>> read_matrix_csv(const string path) {

TypedArray<TypedArray<double>> m;
ifstream file;
file.open(path);

if (file.is_open()) {printf("yes");} else {printf("no");}

cout << file << "\n";

    for(int i = 0; i < 10; i++)  {
        std::string line;
        std::getline(file, line);
        if ( !file.good() ) {
            throw std::invalid_argument ("data file cannot be converted into a matrix");
            }
        std::stringstream line_to_split (line);

        for (int j = 0; j < 10; j++) {
            std::string value;
            std::getline(line_to_split, value, ',');
            if ( !line_to_split.good() ) {
                throw std::invalid_argument ("data file cannot be converted into a matrix");
                }
            m.get(i).set(j, stod(value));
        }
    }
    return m;
}



//HW5 - Exercise 2.2
void write_matrix_csv(const TypedArray<TypedArray<double>> &matrix, const string path) {
FILE *file;
file = fopen("test2.csv", "w+");

for (int i= 0; i<10 ; i++) {
    for (int j=0; j<10; j++) {
        fprintf(file,to_string(matrix.get(i).get(j)) );
        if (j<10) {
            fprintf(file,",");
        }
    }
    fprintf(file,"\n");    
}
fclose(file);
}

/*
// HW5  = Exercise 2.3
map<string, int> occurrence_map(const string path) {

    
}

*/



