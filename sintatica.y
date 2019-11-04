
%{
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <map>
#include <vector>
#include <stack>
#include "headers/escopo.h"
#include "headers/loop.h"
#include "headers/funcoes.h"

#define YYSTYPE atributos

using namespace std;




// --------------------------------------------LEFTS E TOKENS -------------------------------


%}

%token TK_NUM TK_REAL TK_CHAR
%token TK_MAIN TK_ID
%token TK_FIM TK_ERROR
%token TK_TIPO_FLOAT TK_TIPO_INT TK_TIPO_CHAR TK_TIPO_BOOL
%token TK_EQ TK_NOT_EQ TK_BIG_EQ TK_SMALL_EQ
%token TK_AND TK_OR TK_NOT
%token TK_LOGICO
%token TK_IF TK_WHILE TK_FOR TK_ELSE TK_SWITCH TK_CASE TK_DEFAULT TK_DO 
%token TK_BREAK TK_CONTINUE TK_ALL
%token TK_PRINT TK_SCAN


%start S

%left TK_IF
%left TK_AND
%left TK_OR
%left TK_NOT
%left '<' '>' TK_NOT_EQ TK_EQ TK_BIG_EQ TK_SMALL_EQ
%left '%'
%left '+' '-'
%left '*' '/'
%left '(' ')'




%%
//{          ---------------- REGRAS ---------------------
S:			TK_TIPO_INT TK_MAIN '(' ')' BLOCO
			{
				if(temErro){
					cout << erros;
				}
				else
					cout << "/*Compilador FOCA*/\n" << "#include <iostream>\n#include <string.h>\n#include <stdio.h>\n\n#define BOOL int\n\nint main(void)\n{\n" << declararVars() << "\n" << $5.traducao << "\n\treturn 0;\n}" << endl; 
			}
			;

BLOCO:		BLOCO_AUX '{' COMANDOS '}'
			{
				$$.traducao = $3.traducao;
				popEscopo(pilhaContexto);
				//cout <<"teste3"<< endl;
			}
			;

BLOCO_AUX:	/* vazio */ {
				tabelaVariavel table;
				pushEscopo(pilhaContexto,table);
				
			}
			;

COMANDOS:	COMANDO COMANDOS {$$.traducao = $1.traducao + $2.traducao;}
			| {  $$.traducao = "" ;}
			;

COMANDO:	E PTO_VIRGULA { $$.traducao = $1.traducao; }
			| ATRIBUICAO PTO_VIRGULA { $$.traducao =$1.traducao;}
			| DECLARACAO PTO_VIRGULA {$$.traducao = $1.traducao;}
			| TK_PRINT '('FN_ARGS')' PTO_VIRGULA {$$.traducao = $3.traducao + "\t" + "std::cout <<" + $3.label + "<<std::endl;\n";}
			| IF {$$.traducao = $1.traducao;}
			| WHILE { $$.traducao = $1.traducao;}
			| SWITCH { $$.traducao = $1.traducao;}
			| DO PTO_VIRGULA{$$.traducao = $1.traducao;}
			| BREAK PTO_VIRGULA {$$.traducao = $1.traducao;}
			| CONTINUE PTO_VIRGULA{ $$.traducao = $1.traducao;}
			| SCAN PTO_VIRGULA {$$.traducao = $1.traducao;}
			| PTO_VIRGULA
			;

PTO_VIRGULA: ';' {}
			| error {yyerror("Falta de ponto e virgula");}


BREAK:		TK_BREAK
			{
				if(!hasLoop(loops))
					yyerror("Break fora de um loop");
				$$.traducao = "\tgoto " + getLoop(loops).endLabel + ";\n";		
			}
			| TK_BREAK TK_NUM
			{
				int size = hasLoop(loops);
				int N = stoi($2.traducao);
				if(N == 0){
					yyerror("O valor do break precisa ser >= 1 ");
				}
				//cout << "N = " << N << " size = " << size << endl;
				if(N > size)
					yyerror("Break com N maior que numero de lacos");
				$$.traducao = "\tgoto " + getLoopAt(loops,size - N).endLabel + ";\n";
			}
			| TK_BREAK TK_ALL
			{
				if(!hasLoop(loops)){
					yyerror("Break fora de um loop");
				}
				$$.traducao = "\tgoto " + getLoopAt(loops, 0).endLabel + ";\n";
			}
			;

CONTINUE: 	TK_CONTINUE
			{
				if(!hasLoop(loops))
					yyerror("Continue fora de um loop");
				$$.traducao = "\tgoto " + getLoop(loops).continueLabel + ";\n";
			}
			| TK_CONTINUE TK_NUM
			{
				int size = hasLoop(loops);
				int N = stoi($2.traducao);
				if(N == 0){
					yyerror("O valor do continue precisa ser >= 1 ");
				}
				//cout << "N = " << N << " size = " << size << endl;
				if(N > size)
					yyerror("Continue com N maior que numero de lacos");
				$$.traducao = "\tgoto " + getLoopAt(loops, size - N).continueLabel + ";\n";
			}
			| TK_CONTINUE TK_ALL
			{
				if(!hasLoop(loops)){
					yyerror("Continue fora de um loop");
				}
				$$.traducao = "\tgoto " + getLoopAt(loops, 0).continueLabel + ";\n";
			}
			;

DO:			DO_AUX TK_DO BLOCO TK_WHILE '(' E ')'
			{
				Loop loopinho = getLoop(loops);

				$$.traducao = "\t" + loopinho.startLabel + ":\n" + $3.traducao;
				$$.traducao += "\t" + loopinho.continueLabel + ":\n";
				$$.traducao += $6.traducao;
				$$.traducao += "\t" + $6.label + " = !" + $6.label + ";\n";
				$$.traducao += "\tif( " + $6.label + " ) goto " + loopinho.endLabel + ";\n";
				$$.traducao += "\tgoto " + loopinho.startLabel + ";\n";
				$$.traducao += "\t" + loopinho.endLabel + ":\n";

				popLoop(loops);

			}
DO_AUX:		/*vazio */
			{
				string startLabel = gerarGotoLabel();
				string endLabel = gerarGotoLabel();
				string continueLabel = gerarGotoLabel();

				Loop loopinho = {startLabel, endLabel, continueLabel};
				pushLoop(loopinho, loops);
			}

SWITCH:		TK_SWITCH '(' SWITCH_AUX ')' '{' caseRecursao TK_DEFAULT':' BLOMANDO '}'
			{
					$$.traducao = $6.traducao + $9.traducao + "\t" + gambiarraSwitch.top().endLabel + ":\n";
					nGoto -= 1;
					gambiarraSwitch.pop();
			}
			;
			

SWITCH_AUX: TK_ID
			{
				SwitchLabels a;
				a.endLabel = gerarGotoLabel();
				a.nextLabel = gerarGotoLabel();
				a.variavel = buscarVariavel($1.label);
				gambiarraSwitch.push(a);
				
			};

caseRecursao: /*vazio */{ $$.traducao = "";}
			| TK_CASE MULTI_E ':' BLOMANDO caseRecursao 
			{
				SwitchLabels topoDaPilha = gambiarraSwitch.top();
				$$.traducao = "";
				//cout << "a traducao disso é " + $$.traducao + "fiim" << endl;
				$$.traducao += $2.traducao;
				$$.traducao += "\t" + $2.label + " = !" + $2.label + ";\n";
				$$.traducao +=  "\tif( "+ $2.label + " ) goto " + topoDaPilha.nextLabel + ";\n";
				$$.traducao += $4.traducao;

				$$.traducao += "\tgoto " + topoDaPilha.endLabel+ ";\n\t" + topoDaPilha.nextLabel + ":\n" +$5.traducao ;
				gambiarraSwitch.top().nextLabel = gerarGotoLabel();
			}
			;

MULTI_E: 	MULTI_E ',' E  
			{
				SwitchLabels topoDaPilha = gambiarraSwitch.top();
				//cout<< "AAAAAAAAAAAAAAAAAA" << endl;
				struct atributos auxiliar;
				auxiliar.tipo = topoDaPilha.variavel.tipo;
				auxiliar.label = topoDaPilha.variavel.localVar;

				struct atributos temporaria = conversaoImplicita($3, auxiliar, "==");
				$$ = conversaoImplicita($1, temporaria, "||");
				
			}
			| E 
			{
				SwitchLabels topoDaPilha = gambiarraSwitch.top();
				struct atributos auxiliar;
				auxiliar.tipo = topoDaPilha.variavel.tipo;
				auxiliar.label = topoDaPilha.variavel.localVar;
				$$ = conversaoImplicita($1,auxiliar, "==");
			}

			;



IF:			TK_IF '(' E ')' BLOMANDO
			{
				string endLabel = gerarGotoLabel();
				$$.traducao = $3.traducao + "\t" + $3.label + " = !" + $3.label + ";\n" + "\tif( " + $3.label + " ) goto " + endLabel + ";\n" + $5.traducao + "\t" + endLabel + ":\n"; 
			}
			| TK_IF '(' E ')' BLOMANDO TK_ELSE BLOMANDO
			{
				string midLabel = gerarGotoLabel();
				string endLabel = gerarGotoLabel();
				$$.traducao = $3.traducao + "\t" + $3.label + " = !" + $3.label + ";\n" + "\tif( " + $3.label + " ) goto " + midLabel + ";\n" + $5.traducao + "\tgoto " + endLabel+ ";\n\t"+ midLabel + ":\n" + $7.traducao + "\t" +endLabel + ":\n"; 
			}
			;

/* ----------------JUNCAO DE BLOCO COM COMANDO ------------------------*/
BLOMANDO: BLOCO 
		| COMANDO
		;


WHILE:		WHILE_AUX TK_WHILE '(' E ')' BLOMANDO 
			{
				Loop loopinho = getLoop(loops);
				$$.traducao = "\t"+ loopinho.startLabel + ":\n" +$4.traducao + "\t" + $4.label + " = !" + $4.label + ";\n" + "\tif( " + $4.label + " ) goto " + loopinho.endLabel + ";\n" + $6.traducao + "\tgoto "+ loopinho.startLabel + ";\n\t" + loopinho.endLabel + ":\n";
				popLoop(loops);
				//cout<< "teste2" << endl; 
			}
			;

WHILE_AUX:	/*VAZIO */
			{
				string startLabel = gerarGotoLabel();
				string endLabel = gerarGotoLabel();
				Loop loopinho = {startLabel, endLabel, startLabel};
				pushLoop(loopinho, loops);
			} 
			;

FN_ARGS:	E FN_ARGS_AUX 
			{
				$$.traducao = $1.traducao + $2.traducao; $$.label = $1.label + $2.label;
			}
			| /* empty */{$$.traducao = ""; $$.label = "";}
			;

FN_ARGS_AUX: ',' E  FN_ARGS_AUX
			{
				$$.traducao = $2.traducao + $3.traducao;
				$$.label = "<<\" , \"<<" + $2.label + $3.label;
			}
			| /* empty */{$$.traducao = ""; $$.label = ""; }
			;

SCAN:		TK_SCAN '(' SCAN_ARGS ')' 
			{
				$$.traducao = "\tstd::cin" + $3.traducao + ";\n";
			}
			;

SCAN_ARGS:	TIPO ':' TK_ID ',' SCAN_ARGS
			{
				caracteristicas variavel = buscarVariavel($3.label);
				if($1.traducao != variavel.tipo)
					yyerror("A variavel \""+variavel.nomeVar + "\" eh do tipo " + variavel.tipo + " e o tipo requisitado eh "+ $1.traducao);
				
				$$.traducao = " >> " + variavel.localVar + $5.traducao;

			}
			| TIPO ':' TK_ID
			{
				caracteristicas variavel = buscarVariavel($3.label);
				if($1.traducao != variavel.tipo)
					yyerror("A variavel \""+variavel.nomeVar + "\" eh do tipo " + variavel.tipo + " e o tipo requisitado eh "+ $1.traducao);
				
				$$.traducao = " >> " + variavel.localVar;
			}
			;

ATRIBUICAO:	TK_ID '=' E 
			{

				caracteristicas variavel = buscarVariavel($1.label);
				
				if(variavel.tipo == $3.tipo){
					$$.traducao = $3.traducao +  "\t" + variavel.localVar + " = " + $3.label + ";\n";
				}
				else{
					struct coercao correcao = verificarCoercao(variavel.tipo, "=", $3.tipo);
					if(correcao.retornoTipo != "NULL"){
						$$.traducao = $3.traducao +  "\t" + variavel.localVar + " = " + "(" + correcao.conversaoTipo + ")" + $3.label + ";\n";
					}
					else{
						yyerror("a operacao = nao esta definida para " + variavel.tipo + " e " + $3.tipo);
					}

				}
			}
			;



DECLARACAO:	TIPO TK_ID
			{
				$$ = declaracaoVariavel($2.label, $1.traducao);
			}
			| TIPO TK_ID '=' E
			{
				$$ = declaracaoVariavelAtribuicao($2.label, $1.traducao, $4); 
			}

			;

//        ----------------	ARITMETICA -----------------------
E:			E '+' E
			{
				$$ = conversaoImplicita($1, $3 , "+");
			}
			| E '-' E
			{
				$$ = conversaoImplicita($1, $3 , "-");
			}
			| E '*' E
			{
				$$ = conversaoImplicita($1, $3 , "*");
			}
			| E '/' E
			{
				$$ = conversaoImplicita($1, $3 , "/");
			}
			| E '%' E
			{
				$$ = conversaoImplicita($1, $3 , "%");
			}
			| '(' E ')' 
			{
				$$.label = $2.label;
				$$.traducao = $2.traducao;
				$$.tipo = $2.tipo;

			}
			| '-' E
			{
				$$.label = $2.label;
				$$.traducao = $2.traducao + "\t" + $2.label + " = - " + $2.label + ";\n" ;
				$$.tipo = $2.tipo;
			}
			// ---------------------- PARTE LOGICA ---------------------------

			| E TK_AND E {
				$$ = conversaoImplicita($1, $3, "&&");

			}
			| E TK_OR E {
				$$ = conversaoImplicita($1, $3, "||");

			}
			| TK_NOT E{
				$$.label = gerarLabel();
				$$.tipo = "bool";
				inserirTemporaria($$.label, $$.tipo);
				$$.traducao = $2.traducao + "\t" + $$.label + " = !" + $2.label + ";\n";
			}

			//---------------------------- RELACIONAL ------------------------
			| E '<' E{
				$$ = conversaoImplicita($1, $3, "<");
			}

			| E '>' E{
				$$ = conversaoImplicita($1, $3, ">");
			}
			| E TK_BIG_EQ E{
				$$ = conversaoImplicita($1, $3, ">=");
			}

			| E TK_SMALL_EQ E{
				$$ = conversaoImplicita($1, $3, "<=");
			}

			| E TK_EQ E{
				$$ = conversaoImplicita($1, $3, "==");
			}
			| E TK_NOT_EQ E{
				$$ = conversaoImplicita($1, $3, "!=");
			}

			//------------------ CONVERSAO EXPLICITA -------------------------
			| '(' TIPO ')' E {
				$$.label = gerarLabel();
				$$.tipo = $2.traducao;
				inserirTemporaria($$.label, $$.tipo);
				$$.traducao = $4.traducao + "\t" + $$.label + " = (" + $2.traducao + ") " + $4.label + ";\n";
			}

			//}
			// ----------------------- FINAIS ---------------------------------

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
				caracteristicas variavel = buscarVariavel($1.label);
				if(variavel.localVar == ""){
					yyerror("A variavel \"" + $1.label +"\" foi usada e não foi declarada ainda ");
				}
				$$.label = variavel.localVar;
				$$.traducao = "";
				$$.tipo = variavel.tipo;
				//cout << "$1.tipo = " << $1.tipo << endl;
			}
			| TK_LOGICO{
				$$.label = gerarLabel();
				inserirTemporaria($$.label, "bool");
				$$.tipo = "bool";
				$$.traducao = "\t" + $$.label + " = " + $1.traducao + ";\n";

			}
			;

TIPO:		TK_TIPO_BOOL	{$$.traducao = "bool";}
			| TK_TIPO_INT	{$$.traducao = "int";}
			| TK_TIPO_CHAR	{$$.traducao = "char";}
			| TK_TIPO_FLOAT	{$$.traducao = "float";}
//}
%%

#include "lex.yy.c"

int yyparse();

int main( int argc, char* argv[] )
{
	yydebug = 1;

	inicializarTabelaCoercao();

	yyparse();

	return 0;
}