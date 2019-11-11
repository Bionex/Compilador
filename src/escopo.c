#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "../headers/escopo.h"

using namespace std;

void pushEscopo(pilhaMapaPtr pilha, tabelaVariavel mapaEscopo){
    pilha->escopoAtual += 1;
  	pilha->escopos.push_back(mapaEscopo);
}

tabelaVariavel popEscopo(pilhaMapaPtr pilha){

    if(pilha->escopos.empty()){
        cout << "POP_FUNCTION: Não há escopos a serem removidos" << endl;
        exit(0); 
    }

  	tabelaVariavel escopo = pilha->escopos.back();

    pilha->escopos.pop_back();
    pilha->escopoAtual -= 1;

    return escopo;

}

pilhaMapaPtr createMapStack(){

    pilhaMapaPtr pilha = (pilhaMapaPtr) malloc(sizeof(pilhaMapa));
    
    tabelaVariavel escopinho;
    pushEscopo(pilha, escopinho);
    
	pilha->escopoAtual = 0;
    return pilha;
}

caracteristicas createVar(string nome_var, string tipo, string nome_temp){

	caracteristicas var;
	var.tipo = tipo;
	var.nomeVar = nome_var;
	var.localVar = nome_temp;

	return var;
}

void addVar2Escopo (pilhaMapaPtr pilha, caracteristicas v){

	pilha->escopos[pilha->escopoAtual][v.nomeVar] = v;

}

void addVar2Global (pilhaMapaPtr pilha, caracteristicas v){
    //cout<< "inserindo a variavel " + v.nomeVar + "como " + v.localVar << endl; 
	pilha->escopos[0][v.nomeVar] = v;

}
