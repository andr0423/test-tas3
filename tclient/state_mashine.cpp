#include "state_mashine.h"

StMashine::StMashine()
    : current_state( &machine[Sn::A] )
{
    //current_state = machine[Sn::A];
}

bool StMashine::step(unsigned char v)
{
    if ( v >= current_state->ge ) {
        current_state = &machine[current_state->another];
    } else if ( v < current_state->lt ) {
        current_state = &machine[current_state->lt_step];
    }
    return current_state->current < Sn::F;
}

Sn StMashine::getState()
{
    return current_state->current;
}

