#include "rnd.h"

random_device   rd;         // non-deterministic generator
mt19937         gen(rd());  // to seed mersenne twister.
uniform_int_distribution<>  
                dist(1,255); 
unsigned char rnd(){
    return dist(gen);
}

// unsigned char rnd(){
//     return rand() % 254 + 1;
// }

