%{
#include <iostream>
#include <string>
#include <sstream>
#include <map>

#define YYSTYPE atributos

using namespace std;

struct atributos
{
	string label;
	string traducao;
};

int yylex(void);
void yyerror(string);
string gerarLabel();
string declararVars();
void inserirTabela(string);
int getN();

int n = 0;
std::map<std::string, int> tabela;
%}

%token TK_NUM
%token TK_MAIN TK_ID TK_TIPO_INT
%token TK_FIM TK_ERROR

%start S

%left '+' '-'
%left '*' '/'
%left '(' ')'

%%

S 			: TK_TIPO_INT TK_MAIN '(' ')' BLOCO
			{
				cout << "/*Compilador FOCA*/\n" << "#include <iostream>\n#include<string.h>\n#include<stdio.h>\nint main(void)\n{\n" << declararVars() << $5.traducao << "\treturn 0;\n}" << endl; 
			}
			;

BLOCO		: '{' COMANDOS '}'
			{
				$$.traducao = $2.traducao;
			}
			;

COMANDOS	: COMANDO COMANDOS {$$.traducao = $1.traducao + $2.traducao;}
			| {  $$.traducao = "" ;}
			;

COMANDO 	: E ';' { $$.traducao = $1.traducao; }
			| TK_ID '=' E ';' { $$.traducao = $3.traducao +  "\t" + $1.label + " = " + $3.label + ";\n";}
			; 

E 			: E '+' E
			{
				$$.label = "" + gerarLabel();
				$$.traducao = $1.traducao + $3.traducao + "\t" +  $$.label + " = "  + $1.label + " + " +  $3.label + ";\n";
			}
			| E '-' E
			{
				$$.label = "" + gerarLabel();
				$$.traducao = $1.traducao + $3.traducao + "\t" +  $$.label + " = "  + $1.label + " - " +  $3.label + ";\n";
			}
			| E '*' E
			{
				$$.label = "" + gerarLabel();
				$$.traducao = $1.traducao + $3.traducao + "\t" +  $$.label + " = "  + $1.label + " * " +  $3.label + ";\n";
			}
			| E '/' E
			{
				$$.label = "" + gerarLabel();
				$$.traducao = $1.traducao + $3.traducao + "\t" +  $$.label + " = "  + $1.label + " / " +  $3.label + ";\n";
			}
			| '(' E ')' 
			{
				$$.label = gerarLabel();
				$$.traducao = $2.traducao; 

			}

			| TK_NUM
			{
				$$.label = gerarLabel();
				$$.traducao = "\t" + $$.label + " = " + $1.traducao + ";\n";
			}
			| TK_ID{
				$$.label = $1.label;
				$$.traducao = "";}
			;

%%

#include "lex.yy.c"

int yyparse();

int main( int argc, char* argv[] )
{
	yyparse();

	return 0;
}

void yyerror( string MSG )
{
	cout << MSG << endl;
	exit (0);
}				

string gerarLabel(){
	return string("TMP") + to_string(n++);
	
}

string declararVars(){
	string retorno = "";
	for(int i = 0; i < n; i++){
		retorno = retorno + "\tint TMP" + to_string(i) + ";\n";
	}
	return retorno;
}

void inserirTabela(string a){
	tabela[a] = getN();
}

int getN(){
	return n;
}