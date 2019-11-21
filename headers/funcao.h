#ifndef FUNCAO_H
#define FUNCAO_H

#include<unordered_map>
#include<vector>
#include<stack>

using namespace std;

typedef struct funcao{
    string nomeFuncao, nomeLocal,tipoRetorno;
    vector<string> atributos;
    int numeroAtributos;
} Function;

typedef stack<string> FunctionStack;

typedef Function* FunctionPtr;

typedef unordered_map<string,vector<Function>> FunctionMap;

Function createFunction(int );
vector<Function> buscarFuncao(string);
bool inserirFuncao(Function);
void pushFunction(string);
void popFunction();
string getTopFunction();


extern FunctionMap tabelaFuncoes;
extern FunctionStack pilhaFuncoes;

#endif