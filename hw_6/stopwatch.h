#ifndef _STOPWATCH_H
#define _STOPWATCH_H

#include "elma/elma.h"

using namespace elma;
using namespace std::chrono;

class Stopwatch : public Process {
public:

    Stopwatch(std::string name) : Process(name) {}

    void init() {}
    void start();                                 //starts the timer                 
    void update() {}
    void stop();                                   //stops the timer
    void reset();                                  //sets stopwatch to zero
    double get_minutes();                          // number of minutes counted, as a double
    double get_seconds();                          // number of seconds counted, as a double
    double get_milliseconds();                     // number of milliseconds counted, as a double          
    double get_nanoseconds();                      // number of nanoseconds counted, as a double
           
};

#endif