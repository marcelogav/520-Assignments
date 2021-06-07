#include "stopwatch.h"
#include <iostream>

using namespace elma;

    Stopwatch(std::string name) : Process(name) {}

    void init() {}

    void start() {                                  //starts the timer
            high_resolution_clock::time_point t0 = 0;
        }

    void update() {}

    void stop() {                                   //stops the timer
            high_resolution_clock::time_point t = high_resolution_clock::now();
        }

    void reset() {                                  //sets stopwatch to zero
            high_resolution_clock::time_point t = 0;
        }                             

    double total = (t - t0).count();
    
    double get_minutes() {                          // number of minutes counted, as a double
            typedef duration<double,std::ratio<60*1000*1000*1000,1>> mins;
            auto y = mins(total);
            std::cout << y << "minutes " << "\n";
    return y;    
    }

    double get_seconds() {                           // number of seconds counted, as a double
            typedef duration<double,std::ratio<1000*1000*1000,1>> secs;
            auto y = secs(total);
            std::cout << y << "seconds " << "\n";
    return y;    
    }
        
    double get_milliseconds(){                      // number of milliseconds counted, as a double
            typedef duration<double,std::ratio<1000*1000>> mili;
            auto y = mili(total);
            std::cout << y << "miliseconds " << "\n";
    return y;    
    }

    double get_nanoseconds(){                       // number of nanoseconds counted, as a double
            std::cout << total << "nanoseconds " << "\n";
    return y;    
    }

