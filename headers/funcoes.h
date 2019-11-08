#ifndef FUNCOES_H
#define FUNCOES_H

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <map>
#include <vector>
#include <stack>
#include "escopo.h"
#include "loop.h"

#define oi(N) cout << "oi "<< N << endl

using namespace std;

typedef struct atributos
{
	string label;
	string traducao;
	string tipo;
} atributos;

typedef struct SwitchLabelStacks{
	string endLabel;
	string nextLabel;
	caracteristicas variavel;
	int nSwitch;
} SwitchLabels;

struct coercao{
	string retornoTipo, conversaoTipo;
};



typedef std::tuple<string, string, string> KeyTriple;

int yylex(void);
void yyerror(string);
string gerarLabel();
string labelUsuario();
string declararVars();
void inserirTabela(string);
void inserirTemporaria(string, string);
struct coercao verificarCoercao(string , string  ,string );
KeyTriple genKey(string , string, string);
struct atributos conversaoImplicita(struct atributos, struct atributos, string);
struct atributos declaracaoVariavel(string, string);
struct atributos declaracaoVariavelAtribuicao(string, string, atributos);
struct atributos operacaoRelacional(struct atributos, struct atributos, string);
string gerarGotoLabel();
Loop gerarGotoDoLabel();
Loop gerarGotoWhileLabel();
Loop gerarGotoForLabel();
string gerarGotoCaseLabel(int);
string gerarGotoSwitchLabel();
int getN();
vector<string> split(const string&, const string&);
void inicializarTabelaCoercao();
caracteristicas buscarVariavel(string);
caracteristicas buscarVariavelTopo(string);
atributos caracteristicasToAtributos(caracteristicas);
bool operator<(KeyTriple, KeyTriple);
string gerarLabelStringSize(string);
int contarTamanhoString(string);
atributos leituraString(caracteristicas);
atributos codigoAtribuicao(atributos,atributos);
atributos converterStringInteiro(atributos);

extern int nTemp;
extern int nUser;
extern int nGoto;
extern int nGotoIf;
extern int nGotoSwitch;
extern int nGotoCase;
extern int nGotoWhile;
extern int nGotoDo;
extern int nGotoFor;
extern int lineCount;

extern stack <SwitchLabels> gambiarraSwitch ;

extern string tipoDaDeclaracao;

extern string erros;
extern bool temErro ;

extern pilhaMapaPtr pilhaContexto;
extern pilhaLoopPtr loops;

extern std::unordered_map<std::string, string> temporarias;

extern std::map<KeyTriple, struct coercao> tabelaCoercao;

#endif