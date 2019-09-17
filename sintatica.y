%{
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <map>

#define YYSTYPE atributos

using namespace std;

struct atributos
{
	string label;
	string traducao;
	string tipo;
};

typedef struct caracteristicas{
	string localVar, tipo;
} caracteristicas;

typedef std::tuple<string, string, string> KeyTriple;

int yylex(void);
void yyerror(string);
string gerarLabel();
string labelUsuario();
string declararVars();
void inserirTabela(string);
void inserirTemporaria(string, string);
string verificarCoercao(string , string  ,string );

void inicializarTabelaCoercao();

bool operator<(KeyTriple const & lhs, KeyTriple const & rhs) {
	/*
    if (lhs.a < rhs.a) return true;
    if (rhs.a < lhs.a) return false;
    if (lhs.b < rhs.b) return true;
    if (rhs.b < lhs.b) return false;
    if (lhs.c < rhs.c) return true;
    return false;
	*/
    // Alternatively, if you can use C++11 but don't want a tuple for a key
    return std::tie(get<0>(lhs), get<1>(lhs), get<2>(lhs) ) < std::tie(get<0>(rhs), get<1>(rhs), get<2>(rhs));
}

int getN();

int nTemp = 0;
int nUser = 0;
int lineCount = 1;



std::unordered_map<std::string, caracteristicas> tabela;
std::unordered_map<std::string, string> temporarias;
std::unordered_map<std::string, std::string> revertTable;

std::map<KeyTriple, string> tabelaCoercao;
%}

%token TK_NUM TK_REAL TK_CHAR
%token TK_MAIN TK_ID
%token TK_FIM TK_ERROR
%token TK_TIPO_FLOAT TK_TIPO_INT TK_TIPO_CHAR
%token TK_EQ TK_NOT_EQ TK_BIG_EQ TK_SMALL_EQ




%start S

%left '+' '-'
%left '*' '/'
%left '(' ')'

%%

S:			TK_TIPO_INT TK_MAIN '(' ')' BLOCO
			{
				cout << "/*Compilador FOCA*/\n" << "#include <iostream>\n#include <string.h>\n#include <stdio.h>\n\nint main(void)\n{\n" << declararVars() << $5.traducao << "\treturn 0;\n}" << endl; 
			}
			;

BLOCO:		'{' COMANDOS '}'
			{
				$$.traducao = $2.traducao;
			}
			;

COMANDOS:	COMANDO COMANDOS {$$.traducao = $1.traducao + $2.traducao;}
			| {  $$.traducao = "" ;}
			;

COMANDO:	E ';' { $$.traducao = $1.traducao; }
			| ATRIBUICAO ';' { $$.traducao =$1.traducao;}
			| DECLARACAO ';'{$$.traducao = "";} 
			;

ATRIBUICAO:	TK_ID '=' E { $$.traducao = $3.traducao +  "\t" + $1.label + " = " + $3.label + ";\n";}
			;

DECLARACAO:	TK_TIPO_INT VAR
			{
				$$.traducao = $2.traducao;
				string var = revertTable[$2.label];
				if(tabela.find(var) != tabela.end()){
					if(tabela[var].tipo == "Undefined"){
						tabela[var].tipo = "int";
						temporarias[$2.label] = "int";
					}
				}
			}
			| TK_TIPO_FLOAT VAR
			{
				$$.traducao = $2.traducao;
				string var = revertTable[$2.label];
				if(tabela.find(var) != tabela.end()){
					if(tabela[var].tipo == "Undefined"){
						tabela[var].tipo = "float";
						temporarias[$2.label] = "float";
					}
					else {
						cout << "A variavel \""<< var << "\" ja foi declada como "<< tabela[var].tipo << " anteriormente\n";
					}
				}
			}
			| TK_TIPO_CHAR VAR
			{
				$$.traducao = $2.traducao;
				string var = revertTable[$2.label];
				if(tabela.find(var) != tabela.end()){
					if(tabela[var].tipo == "Undefined"){
						tabela[var].tipo = "char";
						temporarias[$2.label] = "char";
					}
					else {
						cout << "A variavel \""<< var << "\" ja foi declada como "<< tabela[var].tipo << " anteriormente\n";
					}
				}
			}
			;

VAR:		TK_ID {$$.label = $1.label; $$.traducao = "";}
			;

E:			E '+' E
			{
				if(temporarias[$1.label] == temporarias[$3.label]){
					$$.label = "" + gerarLabel();
					inserirTemporaria($$.label, temporarias[$1.label]);
					$$.traducao = $1.traducao + $3.traducao + "\t" +  $$.label + " = "  + $1.label + " + " +  $3.label + ";\n";
				}
				else{
					yyerror("variaveis de tipos diferentes");
				}
			}
			| E '-' E
			{
				if(temporarias[$1.label] == temporarias[$3.label]){
					$$.label = "" + gerarLabel();
					inserirTemporaria($$.label, temporarias[$1.label]);
					$$.traducao = $1.traducao + $3.traducao + "\t" +  $$.label + " = "  + $1.label + " - " +  $3.label + ";\n";
				}
				else{
					yyerror("variaveis de tipos diferentes");
				}
			}
			| E '*' E
			{
				if(temporarias[$1.label] == temporarias[$3.label]){
					$$.label = "" + gerarLabel();
					inserirTemporaria($$.label, temporarias[$1.label]);
					$$.traducao = $1.traducao + $3.traducao + "\t" +  $$.label + " = "  + $1.label + " /*" +  $3.label + ";\n";
				}
				else{
					yyerror("variaveis de tipos diferentes");
				}
			}
			| E '/' E
			{
				if(temporarias[$1.label] == temporarias[$3.label]){
					$$.label = "" + gerarLabel();
					inserirTemporaria($$.label, temporarias[$1.label]);
					$$.traducao = $1.traducao + $3.traducao + "\t" +  $$.label + " = "  + $1.label + " / " +  $3.label + ";\n";
				}
				else{
					yyerror("variaveis de tipos diferentes");
				}
			}
			| '(' E ')' 
			{
				$$.label = $2.label;
				$$.traducao = $2.traducao;
				$$.tipo = $2.tipo;

			}

			| TK_NUM
			{
				$$.label = gerarLabel();
				inserirTemporaria($$.label, "int");
				$$.traducao = "\t" + $$.label + " = " + $1.traducao + ";\n";
				$$.tipo = "int";
			}
			| TK_REAL
			{
				$$.label = gerarLabel();
				inserirTemporaria($$.label, "float");
				$$.traducao = "\t" + $$.label + " = " + $1.traducao + ";\n";
				$$.tipo = "float";
			}
			| TK_CHAR
			{
				$$.label = gerarLabel();
				inserirTemporaria($$.label, "char");
				$$.traducao = "\t" + $$.label + " = " + $1.traducao + ";\n";
				$$.tipo = "char";
			}
			| TK_ID{
				$$.label = $1.label;
				$$.traducao = "";
				$$.tipo = "Undefined";}
			;

%%

#include "lex.yy.c"

int yyparse();

int main( int argc, char* argv[] )
{
	inicializarTabelaCoercao();

	cout << verificarCoercao("int", "+", "int");
	yyparse();

	return 0;
}

void yyerror( string MSG )
{
	cout << MSG << endl;
	exit (0);
}				

string gerarLabel(){
	return string("TMP") + to_string(nTemp++);
	
}

string labelUsuario(){
	return string("USRVAR") + to_string(nUser++);
	
}

string declararVars(){
	string retorno = "";
	for(auto &x: temporarias){
		retorno = retorno + "\t" + x.second + " " +x.first + ";\n";
	}
	return retorno;
}

void inserirTabela(string a){
	string aux = labelUsuario();
	tabela[a] ={
		aux,
		"Undefined"
	};
	temporarias[aux] = "Undefined";
	revertTable[aux] = a;
}
void inserirTemporaria(string label, string tipo){
	temporarias[label] = tipo;

}

/*
bool varDeclarada(){
	if(tipos.find(yytext) != tipos.end())
		return true;
	else
		return false;
}*/



string verificarCoercao(string opUm, string operador ,string opDois){

	KeyTriple chave (opUm, operador, opDois);
	if(tabelaCoercao.find(chave) != tabelaCoercao.end())
		return tabelaCoercao[chave];

	/*chave = {opDois, operador,opUm};
	if(tabelaCoercao.find(chave) != tabelaCoercao.end())
		return tabelaCoercao[chave];
	*/
}

void inicializarTabelaCoercao(){
	KeyTriple chave ("int", "+" , "int");

	tabelaCoercao[chave] = "int";

	get<2>(chave) = "float";
	tabelaCoercao[chave] = "float";


}