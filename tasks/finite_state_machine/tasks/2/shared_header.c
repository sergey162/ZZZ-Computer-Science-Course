#pragma once

#include <stdbool.h>

#include "stdlib.h"

typedef enum {
    FINDFIRSTSYMBOLCOMMENTS1 = 0,
    FINDSECONDSYMBOLCOMMENTS1,
    COMMENTDETECTED,
    FINDFIRSTSYMBOLCOMMENTS2,
    STATECOUNT,
    END
} StateName;

typedef struct State State;

typedef struct {
    State* pipeline;
    StateName cur_state;
    int step;
    int count;
    char lastsym;
} StateMachine;

typedef struct State {
    StateName name;
    StateName (*action)(StateMachine*, char c);
} State;