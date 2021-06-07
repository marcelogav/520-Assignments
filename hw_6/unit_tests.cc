#include "gtest/gtest.h"
#include "stopwatch.h"
#include <iostream>
#include "random_process.h"
#include "filter.h"
#include "integrator.h"

namespace {

// Ex1
TEST(Ex1,Stopwatch) {

        #define SLEEP std::this_thread::sleep_for(std::chrono::milliseconds(1500))

        Stopwatch w ("Stopwatch"); // should set the stopwatch to 0 seconds
        w.start();
        SLEEP;
        w.stop();
        std::cout << w.get_seconds() << "\n"; // about 1.5
        SLEEP;
        std::cout << w.get_seconds() << "\n"; // still about 1.5
        w.start();
        SLEEP;
        w.stop();
        std::cout << w.get_seconds() << "\n"; // about 3.0
        w.reset();
        std::cout << w.get_seconds() << "\n"; // 0.0

}   


// Ex2
class FilterTester : public Process {

        public:

        FilterTester(std::string name) : Process(name), x(0.25) {}

        void init() {}
        void start() {}
        void update() {
            channel("link").send(x);
            x = 1-x;
        }
        void stop() {}

        double x;

    };
    
    TEST(Ex2,Test_onlyFilter) {
      elma::Manager m;

      FilterTester ft("FilterTester only 0.25 & 0.75");
      Filter f("filter");
      elma::Channel link("link");

      m.schedule(ft, 1_ms)
      .schedule(f, 1_ms)
      .add_channel(link)
      .init()
      .run(100_ms);

     }


    TEST(Ex2,Test_RandomP_Filter) {
      elma::Manager m;

      RandomProcess r("random numbers");
      Filter f("filter");
      elma::Channel link("link");

      m.schedule(r, 1_ms)
      .schedule(f, 1_ms)
      .add_channel(link)
      .init()
      .run(100_ms);

     }


// Ex3
TEST(Ex3,Integrator) {
      elma::Manager m;

      FilterTester ft("FilterTester only 0.25 & 0.75");
      Integrator Integ("Integrator");
      elma::Channel link("link");

      m.schedule(ft, 1_ms)
      .schedule(Integ, 1_ms)
      .add_channel(link)
      .init()
      .run(100_ms);

    // value integrated should be 50  

     }


}