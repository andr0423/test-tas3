#include "state_mashine.h"



struct state machine[] = {
    { Sn::A,  10, Sn::B, 5, Sn::C, Sn::A },
    { Sn::B,  50, Sn::C, 5, Sn::D, Sn::B },
    { Sn::C,  90, Sn::D, 5, Sn::E, Sn::C },

    { Sn::D, 130, Sn::D, 5, Sn::F, Sn::E },  // ?

    { Sn::E, 170, Sn::F, 5, Sn::A, Sn::E },

    { Sn::F, 255, Sn::F, 0, Sn::F, Sn::F }   // ?
};

StMashine::StMashine()
    : current_state( &machine[Sn::A] )
{}

bool StMashine::step(unsigned char v)
{
    if ( v >= current_state->ge ) {
        current_state = &machine[current_state->ge_step];
    } else if ( v < current_state->lt ) {
        current_state = &machine[current_state->lt_step];
    } else {
        current_state = &machine[current_state->another];
    }
    return current_state->current < Sn::F;
}

Sn StMashine::getState()
{
    return current_state->current;
}

