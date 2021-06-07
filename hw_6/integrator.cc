#include "filter.h"

using namespace elma;

double integrated_value = 0;

void Integrator::update() {
    integrated_value = integrated_value + (channel("link");        
}


double Integrator::value() {
    return integrated_value;

}