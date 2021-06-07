#ifndef _INTEGRATOR_H
#define _INTEGRATOR_H

#include "elma/elma.h"

using namespace elma;

class Integrator : public Process {

  
    public:

    Integrator(std::string name) : Process(name) {}

    void init() {}
    void start() {}
    void update();   
    void stop() {}
    double value();
   

    private:

    double integrated_value;
    
};  

#endif