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

extern struct state machine[];

class StMashine {
    state * current_state;

public:
    StMashine();
    bool step(unsigned char);
    Sn   getState();
};

