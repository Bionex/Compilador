#ifndef ESCOPO_H
#define ESCOPO_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

typedef struct caracteristicas{
	string localVar, tipo, nomeVar;
} caracteristicas;

typedef caracteristicas * caracteristicasPtr;

typedef unordered_map<string, caracteristicas> tabelaVariavel;

typedef struct pilhaMapa {
    vector <tabelaVariavel> escopos;
    int escopoAtual;
} pilhaMapa;

typedef pilhaMapa * pilhaMapaPtr;

void pushEscopo(pilhaMapaPtr, tabelaVariavel);
tabelaVariavel popEscopo(pilhaMapaPtr);
pilhaMapaPtr createMapStack();
caracteristicas createVar(string, string, string);
void addVar2Escopo (pilhaMapaPtr, caracteristicas);
void addVar2Global (pilhaMapaPtr, caracteristicas);

#endif