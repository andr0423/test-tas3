#pragma once

using namespace std;

enum Sn{ A, B , C, D, E, F };

struct state {
    Sn current;
    unsigned char ge;
    Sn ge_step;
    unsigned char lt;
    Sn lt_step;
    Sn another;
};

struct state machine[] = {
    { Sn::A,  10, Sn::B, 5, Sn::C, Sn::A },
    { Sn::B,  50, Sn::C, 5, Sn::D, Sn::B },
    { Sn::C,  90, Sn::D, 5, Sn::E, Sn::C },

    { Sn::D, 130, Sn::D, 5, Sn::F, Sn::E },  // ?

    { Sn::E, 170, Sn::F, 5, Sn::A, Sn::E },

    { Sn::F, 255, Sn::F, 0, Sn::F, Sn::F }   // ?
};


class StMashine {
    state * current_state;

public:
    StMashine(); // : current_state(&machine[Sn::A]){};
    bool step(unsigned char);
    Sn   getState();
};

