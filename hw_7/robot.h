#ifndef _ROBOT_H
#define _ROBOT_H

#include "elma/elma.h"
#include <json/json.h>

using namespace elma;
using nolohmann::json;


//Exercise 1

class Mode : public State {
    public:
    Mode(std::string name) : State(name) {}
    void entry(const Event& e) {
        std::cout << "entering " + name() << "\n";
    }
    void during() {}
    void exit(const Event&) {}
};



class Robot : public StateMachine {

    public:

    Robot() : StateMachine() {
        set_initial(Wander);
        add_transition("intruder detected", Wander, MakeNoise);
        add_transition("reset", MakeNoise, Wander);
        add_transition("proximity warning", MakeNoise, Evade);
        add_transition("reset", Evade, MakeNoise);
        add_transition("battery low", Evade, FindRechargeStation);
        add_transition("battery low", Wander, FindRechargeStation);
        add_transition("found recharge station", FindRechargeStation, Recharge);
        add_transition("battery full", Recharge, Wander);        
    }

    private:

    Mode Wander, MakeNoise, Evade, FindRechargeStation, Recharge;      

};


// Exercise 2

class BetterStateMachine : public StateMachine {

    friend class Robot;

    public:

    json to_json() const;

    for (_transitions) {
        to_json << "{" << 





    }




};

#endif