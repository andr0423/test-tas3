#include "rnd.h"

random_device   rd;         // non-deterministic generator
mt19937         gen(rd());  // to seed mersenne twister.

uniform_int_distribution<>  
                dist(0,255); 

unsigned char rnd(){
    return dist(gen);
}
