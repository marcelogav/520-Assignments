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
#include <map>

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

string *buffer;
TypedArray<string> temp;
fstream file_source(path, ios::in);

if ( !file_source ) {
        throw std::invalid_argument ("data file cannot be converted into a matrix");
        }

else {       
    int i=0; 
    while (file_source >> buffer) {
        for (auto i = 0; i < m.size(); i++) {
            m.set(i,atof(buffer));
        }
        
    }

}  

return m;
}

*/

//HW5 - Exercise 2.2
void write_matrix_csv(const TypedArray<TypedArray<double>> &matrix, const string path) {
fstream file_output (path, ios::out | ios::app);

TypedArray<TypedArray<double>> temp = matrix;

     for (int i=0; i < temp.size(); i++) {
         file_output <<  temp.get(i);
         file_output << "\n";
     }
}



// HW5  = Exercise 2.3
map<string, int> occurrence_map(const string path) {

map<string, int> results;
vector<string> words;
string word;
vector<string> valid_keys;
vector<string> invalid_strings;
string valid = "abcdefghijklmnopqrstuvwxyz0123456789'";
string invalid = "`~!@#$%^&*()_-+=[]|{};<>?/";
string punctuation = ",.:;!()\"";

fstream file_source(path, ios::in);

    while(file_source >> word) {
        for (string::iterator i = word.begin(); i != word.end(); i++) {
            *i = tolower(*i);
            }
            while (count(punctuation.begin(),punctuation.end(),word.front())>0) {
                word.erase(0,1);
            }
            while (count(punctuation.begin(),punctuation.end(),word.back())>0) {
                word.pop_back();
            }
        words.push_back(word);
    }
    for (int index = 0; index < words.size(); index++) {
        int inv = 0;
        for (char ch : words[index]) {
           inv = inv + count(invalid.begin(), invalid.end(),ch); 
            }
            if (inv==0) {
                valid_keys.push_back(words[index]);
            }
            else {
                invalid_strings.push_back(words[index]); 
            }
    }

    sort(valid_keys.begin(),valid_keys.end());
    valid_keys.erase(unique(valid_keys.begin(), valid_keys.end()),valid_keys.end());

    for (int index = 0; index < valid_keys.size(); index++) {
    results.insert(make_pair(valid_keys[index], (count(words.begin(), words.end(), valid_keys[index])))); 
    }


// Outputs

cout << "Stored text:" << "\n";
for (int index = 0; index < words.size(); index++) {
    cout << words[index] << " ";
    }
    cout << "\n" << "\n";

cout << "Valid Keys:" << "\n";
for (int index = 0; index < valid_keys.size(); index++) {
    cout << valid_keys[index] << " ";
    }
    cout << "\n" << "\n";

cout << "Invalid strings:" << "\n";
for (int index = 0; index < invalid_strings.size(); index++) {
    cout << invalid_strings[index] << " ";
    }
    cout << "\n" << "\n";

fstream file_output ("/source/MapFunction_output.txt", ios::out | ios::app);

cout << "Map result:" << "\n";

map<string,int>::iterator it;
    for(it = results.begin(); it != results.end(); it++) {
        cout << it->first << " => " << it -> second << "\n";
        file_output << it->first << " => " << it -> second << "\n";
    }

return results ;
} 








