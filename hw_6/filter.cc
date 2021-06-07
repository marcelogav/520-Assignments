#include "filter.h"
#include <deque>

using namespace elma;
using std::deque;

int numUpd = 0;
double sum = 0;
double running_average = 0;

void Filter::update() {
    numUpd++;
    deque<double> v;
    if (v.size<=10) {
        v.push_back(channel("link"));
        
    }
    else {
        v.pop_front();
        v.push_back(channel("link"));
    }

    if(numUpd<10) {
        for (auto i=v.begin(); i!=v.end(); i++) {
            sum = sum + v[i]; 
        } 
        running_average = sum / numUpd;
    }
    else {
        for (auto i=v.begin(); i!=v.end(); i++) {
            sum = sum + v[i]; 
        } 
        running_average = sum / 10;
    }

}


double Filter::value() {
    return running_average;

}