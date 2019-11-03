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

void pushLoop(Loop loop, pilhaLoopPtr stack){
    //cout<<"pushing loop"<< endl;
    stack->loops.push_back(loop); 
}

Loop popLoop(pilhaLoopPtr stack){
    Loop loop = stack->loops.back();
    //cout<<"popping loop"<< endl;
    stack->loops.pop_back();
    //cout<< "teste"<< endl;
    return loop;
}

Loop getLoop (pilhaLoopPtr stack){
    if(stack->loops.size() > 0){
        //cout<<"getting loop"<< endl;
        Loop loop = stack->loops.back();
        
        return loop;
    }
}

Loop getLoopAt(pilhaLoopPtr stack , int n){
    if(stack->loops.size() > n){
        //cout<<"getting loop"<< endl;
        Loop loop = stack->loops[n];
        
        return loop;
    }
}

pilhaLoopPtr createLoopStack(){
    //cout<<"creating loop"<< endl;
    return (pilhaLoopPtr) malloc(sizeof(pilhaLoop));
}

int hasLoop(pilhaLoopPtr stack){
    //cout << "retornando " << stack->loops.size() << endl;
    return stack->loops.size();
}