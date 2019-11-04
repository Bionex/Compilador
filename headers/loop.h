#ifndef LOOP_H
#define LOOP_H

//...

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

typedef struct Loop {
    string startLabel;
    string endLabel;
    string continueLabel;
}Loop;

typedef struct pilhaLoop{
    vector <Loop> loops;
}pilhaLoop;

typedef pilhaLoop* pilhaLoopPtr;

void pushLoop(Loop, pilhaLoopPtr);
Loop popLoop(pilhaLoopPtr);
Loop getLoop (pilhaLoopPtr);
Loop getLoopAt(pilhaLoopPtr , int);
pilhaLoopPtr createLoopStack();
int hasLoop(pilhaLoopPtr);


#endif