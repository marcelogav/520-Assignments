#ifndef _RANDONPROCESS_H
#define _RANDONPROCESS_H

#include "elma/elma.h"

using namespace elma;

class RandomProcess : public Process {

    
    public:

    RandomProcess(std::string name) : Process(name) {}

    void init() {}
    void start() {}
    void update();   
    void stop() {}
  

 
};  

#endif