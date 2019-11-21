#ifndef FUNCAO_H
#define FUNCAO_H

#include<unordered_map>
#include<vector>

using namespace std;

typedef struct funcao{
    string nomeFuncao, nomeLocal,tipoRetorno;
    vector<string> atributos;
    int numeroAtributos;
} Function;

typedef Function* FunctionPtr;

typedef unordered_map<string,vector<Function>> FunctionMap;

Function createFunction(int );
vector<Function> buscarFuncao(string);
bool inserirFuncao(Function);

extern FunctionMap tabelaFuncoes;

#endif