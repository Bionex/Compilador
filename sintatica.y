%{
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>

#define YYSTYPE atributos

using namespace std;

struct atributos
{
	string label;
	string traducao;
};

typedef struct caracteristicas{
	string localVar, tipo;
} caracteristicas;

int yylex(void);
void yyerror(string);
string gerarLabel();
string labelUsuario();
string declararVars();
void inserirTabela(string);

void inserirTemporaria(string, string);
int getN();

int nTemp = 0;
int nUser = 0;
std::unordered_map<std::string, caracteristicas> tabela;
std::unordered_map<std::string, string> temporarias;
std::unordered_map<std::string, std::string> revertTable;
%}

%token TK_NUM TK_REAL TK_CHAR
%token TK_MAIN TK_ID
%token TK_FIM TK_ERROR
%token TK_TIPO_FLOAT TK_TIPO_INT TK_TIPO_CHAR


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
				$$.traducao = "";
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
				$$.traducao = "";
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
				$$.traducao = "";
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

VAR:		TK_ID {$$.label = $1.label;}
			| TK_ID '=' TK_NUM {}
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

			}

			| TK_NUM
			{
				$$.label = gerarLabel();
				inserirTemporaria($$.label, "int");
				$$.traducao = "\t" + $$.label + " = " + $1.traducao + ";\n";
			}
			| TK_REAL
			{
				$$.label = gerarLabel();
				inserirTemporaria($$.label, "float");
				$$.traducao = "\t" + $$.label + " = " + $1.traducao + ";\n";
			}
			| TK_CHAR
			{
				$$.label = gerarLabel();
				inserirTemporaria($$.label, "char");
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
	return string("TMP") + to_string(nTemp++);
	
}

string labelUsuario(){
	return string("USRVAR") + to_string(nUser++);
	
}

string declararVars(){
	string retorno = "";
	for(auto &x: tabela){
		retorno = retorno + "\t" + x.second.tipo +" " +  x.second.localVar + ";\n";
	}
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