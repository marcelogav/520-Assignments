#ifndef _FILTER_H
#define _FILTER_H

#include "elma/elma.h"

using namespace elma;

class Filter : public Process {

  
    public:

    Filter(std::string name) : Process(name) {}

    void init() {}
    void start() {}
    void update();   
    void stop() {}
    double value();
   

    private:

    int numUpd;
    double running_average;
    
};  

#endif