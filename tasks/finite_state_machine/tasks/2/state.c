#pragma once

#include "shared_header.c"

StateName FindFirstSymbolComments1(StateMachine* sm, char ch) {
    printf("Programm started and finding symbol - / - this is start comment\n");
    if (ch == '/') {
        ++sm->step;
        printf(" I am finding / symbol in start of comment\n");
        return FINDSECONDSYMBOLCOMMENTS1;
    }
    return FINDFIRSTSYMBOLCOMMENTS1;
}

StateName FindSecondSymbolComments1(StateMachine* sm, char ch) {
    if (ch == '*') {
        printf(" I am finding * symbol in start of comment\n");
        ++sm->step;
        return COMMENTDETECTED;
    } else {
        printf(" I dont find second symbol - * - because i go to first state\n");
        --sm->step;
        return FINDFIRSTSYMBOLCOMMENTS1;
    }
}

StateName FindCountWords(StateMachine* sm, char ch) {
    if (ch == '/' && sm->lastsym == '*') {
        printf("Last symbol was - * and now symbol - / - comment finished \n");
        ++sm->count;
        return END;
    }
    if (ch == ' ' && sm->lastsym != ' ') {
        ++sm->count;
    } else if (ch == '*') {
        printf("Find * and go to check future symbol\n");
        return FINDFIRSTSYMBOLCOMMENTS2;
    }
    sm->lastsym = ch;
    return COMMENTDETECTED;
}

StateName FindSecondSymbolComments2(StateMachine* sm, char ch) {
    if (ch == '/') {
        printf("Last symbol was - * and now symbol - / - comment finished \n");
        if (sm->lastsym != ' ') {
            ++sm->count;
        }
        return END;
    } else {
        printf("Last symbol was - * - but now symbol is not - / - comment continue\n");
        if (ch == ' ') {
            ++sm->count;
        }
        sm->lastsym = ch;
        return COMMENTDETECTED;
    }
}

State* MakeStates() {
    State* st = (State*)malloc(sizeof(State) * STATECOUNT);
    int i = 0;
    st[i].name = (StateName)i;
    st[i].action = &FindFirstSymbolComments1;
    ++i;
    st[i].name = (StateName)i;
    st[i].action = &FindSecondSymbolComments1;
    ++i;
    st[i].name = (StateName)i;
    st[i].action = &FindCountWords;
    ++i;
    st[i].name = (StateName)i;
    st[i].action = &FindSecondSymbolComments2;
    return st;
}

void DeleteStates(State* st) {
    free(st);
}
