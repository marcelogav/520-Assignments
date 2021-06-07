#include "random_process.h"
#include<iostream>
#include<random>

using namespace elma;

void RandomProcess::update() {
    std:srand(std::time(nullptr));
    double x = (double)(rand()) / ((double)(RAND_MAX));
    channel("link").send(x);        
}

  