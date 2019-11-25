#include "../headers/funcao.h"

FunctionMap tabelaFuncoes;
FunctionStack pilhaFuncoes;

Function createFunction(int numeroAtributos){
    Function f;
    f.numeroAtributos = numeroAtributos;
    return f;
}

vector<Function> buscarFuncao(string nome){
    if(tabelaFuncoes.find(nome) != tabelaFuncoes.end()){
        return tabelaFuncoes[nome];
    }
    return vector<Function>();
}

bool inserirFuncao(Function f){
    string nome = f.nomeFuncao;
    bool error = false;
    if(tabelaFuncoes.find(nome) != tabelaFuncoes.end()){
        vector<Function> funcoes = tabelaFuncoes[nome];
        for(int i = 0; i < funcoes.size(); i++){
            if(f.atributos == funcoes[i].atributos){
                error = true;
            }
        }
    }
    if(!error){
        tabelaFuncoes[nome].push_back(f);
    }

    return !error;
}

void pushFunction(string tipo){
    pilhaFuncoes.push(tipo);
}


void popFunction(){
    pilhaFuncoes.pop();
}

string getTopFunction(){
    if(!pilhaFuncoes.empty())
        return pilhaFuncoes.top();
    else
        return "";
}


