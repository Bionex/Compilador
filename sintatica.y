
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
%token TK_TIPO_FLOAT TK_TIPO_INT TK_TIPO_CHAR TK_TIPO_BOOL TK_TIPO_STRING
%token TK_EQ TK_NOT_EQ TK_BIG_EQ TK_SMALL_EQ
%token TK_AND TK_OR TK_NOT
%token TK_LOGICO TK_STRING
%token TK_IF TK_WHILE TK_FOR TK_ELSE TK_SWITCH TK_CASE TK_DEFAULT TK_DO 
%token TK_BREAK TK_CONTINUE TK_ALL
%token TK_PRINT TK_SCAN


%start S

%left TK_AND
%left TK_OR
%left TK_NOT
%left '<' '>' TK_NOT_EQ TK_EQ TK_BIG_EQ TK_SMALL_EQ
%left '%'
%left '+' '-'
%left '*' '/'
%left '(' ')'
%right UMINUS

%nonassoc NO_ELSE
%nonassoc TK_ELSE





%%
//{          ---------------- REGRAS ---------------------
S:			TK_TIPO_INT TK_MAIN '(' ')' BLOCO
			{
				if(temErro){
					cout << erros;
				}
				else
					cout << "/*Compilador FOCA*/\n" << "#include <iostream>\n#include <string.h>\n#include <stdio.h>\n\n#define BOOL int\n#define True 1\n#define False 0\n#define STRING char*\n\nint main(void)\n{\n" << declararVars() << "\n" << $5.traducao << "\n\treturn 0;\n}" << endl; 
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
			/*| WHILE { $$.traducao = $1.traducao;}
			| DO PTO_VIRGULA{$$.traducao = $1.traducao;}*/
			| SWITCH { $$.traducao = $1.traducao;}
			| LOOP_AUX LOOP {$$.traducao = $2.traducao;}
			| BREAK PTO_VIRGULA {$$.traducao = $1.traducao;}
			| CONTINUE PTO_VIRGULA{ $$.traducao = $1.traducao;}
			| SCAN PTO_VIRGULA {$$.traducao = $1.traducao;}
			| PTO_VIRGULA {$$.traducao = "";}
			| BLOCO {$$.traducao = $1.traducao;}
			;

COMANDOALT:	E PTO_VIRGULA { $$.traducao = $1.traducao; }
			| ATRIBUICAO PTO_VIRGULA { $$.traducao =$1.traducao;}
			| DECLARACAO PTO_VIRGULA {$$.traducao = $1.traducao;}
			| TK_PRINT '('FN_ARGS')' PTO_VIRGULA {$$.traducao = $3.traducao + "\t" + "std::cout <<" + $3.label + "<<std::endl;\n";}
			| IF {$$.traducao = $1.traducao;}
			/*| WHILE { $$.traducao = $1.traducao;}
			| DO PTO_VIRGULA{$$.traducao = $1.traducao;}*/
			| SWITCH { $$.traducao = $1.traducao;}
			| LOOP_AUX LOOP {$$.traducao = $2.traducao;}
			| BREAK PTO_VIRGULA {$$.traducao = $1.traducao;}
			| CONTINUE PTO_VIRGULA{ $$.traducao = $1.traducao;}
			| SCAN PTO_VIRGULA {$$.traducao = $1.traducao;}
			| PTO_VIRGULA {$$.traducao = "";}
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

LOOP: 		DO PTO_VIRGULA {$$.traducao = $1.traducao; popEscopo(pilhaContexto);}
			| WHILE { $$.traducao = $1.traducao; popEscopo(pilhaContexto);}
			| FOR {$$.traducao = $1.traducao; popEscopo(pilhaContexto);}
			;

LOOP_AUX:	TK_DO 
			{
				Loop loopinho= createLoop("do") ;
				pushLoop(loopinho, loops);
				tabelaVariavel tabela;
				pushEscopo(pilhaContexto, tabela);
			}
			| TK_WHILE '('
			{ 
				Loop loopinho= createLoop("while") ; 
				pushLoop(loopinho, loops);
				tabelaVariavel tabela;
				pushEscopo(pilhaContexto, tabela);
			}
			| TK_FOR 
			{
				Loop loopinho = createLoop("for");
				 pushLoop(loopinho, loops);
				 tabelaVariavel tabela;
				pushEscopo(pilhaContexto, tabela);
			}
			;

FOR: 		'(' FOR_ARG1 ';' FOR_ARG2 ';' FOR_ARG3 ')' BLOMANDO
			{
				Loop loopinho = getLoop(loops);
				$$.traducao = $2.traducao + "\t" +loopinho.startLabel+ ":\n" +$4.traducao;
				$$.traducao += "\t" + $4.label + " = !" + $4.label + ";\n";
				$$.traducao += "\tif( " + $4.label + ") goto " + loopinho.endLabel + ";\n";
				$$.traducao += $8.traducao + "\t" + loopinho.continueLabel + ":\n";
				$$.traducao += $6.traducao;
				$$.traducao += "\tgoto " + loopinho.startLabel + ";\n";
				$$.traducao += "\t" + loopinho.endLabel + ":\n";
			}
			;

FOR_ARG1:	DECLARACAO {$$.traducao = $1.traducao;}
			| ATRIBUICAO ',' FOR_ARG1_AUX {$$.traducao = $1.traducao + $3.traducao;}
			| /* VAZIO */ { $$.traducao = "";}
			;

FOR_ARG1_AUX: ATRIBUICAO ',' FOR_ARG1_AUX {$$.traducao = $1.traducao + $3.traducao;}
			| ATRIBUICAO {$$.traducao = $1.traducao;}
			;

FOR_ARG2:	/* vazio */
			{ 
				$$.label = gerarLabel();
				inserirTemporaria($$.label, "bool");
				$$.traducao = "\t" + $$.label + " = True;\n";
			}
			| E 
			{
				$$.traducao = $1.traducao;
			}
			| E ',' FOR_ARG2_AUX 
			{
				$$.traducao = $1.traducao + $3.traducao;
				$$.label = $3.label;
			}
			;

FOR_ARG2_AUX: E {$$.label = $1.label; $$.traducao = $1.traducao;}
			| E ',' FOR_ARG2_AUX {$$.traducao = $1.traducao + $3.traducao; $$.label = $3.label;}
			;

FOR_ARG3:	E {$$.traducao = $1.traducao;}
			| E ',' FOR_ARG3_AUX {$$.traducao = $1.traducao + $3.traducao;}
			| ATRIBUICAO {$$.traducao = $1.traducao;}
			| ATRIBUICAO ',' FOR_ARG3_AUX {$$.traducao = $1.traducao + $3.traducao;}
			| /*vazio */ {$$.traducao = "";}
			;

FOR_ARG3_AUX: E {$$.traducao = $1.traducao;}
			| E ',' FOR_ARG3_AUX {$$.traducao = $1.traducao + $3.traducao;}
			| ATRIBUICAO {$$.traducao = $1.traducao;}
			| ATRIBUICAO ',' FOR_ARG3_AUX {$$.traducao = $1.traducao + $3.traducao;}
			;

DO:			BLOMANDO TK_WHILE '(' E ')'
			{
				Loop loopinho = getLoop(loops);

				$$.traducao = "\t" + loopinho.startLabel + ":\n" + $1.traducao;
				$$.traducao += "\t" + loopinho.continueLabel + ":\n";
				$$.traducao += $4.traducao;
				$$.traducao += "\t" + $4.label + " = !" + $4.label + ";\n";
				$$.traducao += "\tif( " + $4.label + " ) goto " + loopinho.endLabel + ";\n";
				$$.traducao += "\tgoto " + loopinho.startLabel + ";\n";
				$$.traducao += "\t" + loopinho.endLabel + ":\n";

				popLoop(loops);

			}

SWITCH:		TK_SWITCH '(' SWITCH_AUX ')' '{' caseRecursao TK_DEFAULT':' COMANDOS '}'
			{
					$$.traducao = $6.traducao + $9.traducao + "\t" + gambiarraSwitch.top().endLabel + ":\n";
					//nGoto -= 1;
					gambiarraSwitch.pop();
					nGotoCase = 0;
			}
			;
			

SWITCH_AUX: TK_ID
			{
				SwitchLabels a;
				a.endLabel = gerarGotoSwitchLabel();
				a.nextLabel = gerarGotoCaseLabel(a.nSwitch);
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
				gambiarraSwitch.top().nextLabel = gerarGotoCaseLabel(topoDaPilha.nSwitch);
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



IF:			TK_IF '(' E ')' BLOMANDO2 %prec NO_ELSE
			{
				string endLabel = gerarGotoLabel();
				$$.traducao = $3.traducao + "\t" + $3.label + " = !" + $3.label + ";\n" + "\tif( " + $3.label + " ) goto " + endLabel + ";\n" + $5.traducao + "\t" + endLabel + ":\n"; 
			}
			| TK_IF '(' E ')' BLOMANDO2 TK_ELSE BLOMANDO2
			{
				string midLabel = gerarGotoLabel();
				string endLabel = gerarGotoLabel();
				$$.traducao = $3.traducao + "\t" + $3.label + " = !" + $3.label + ";\n" + "\tif( " + $3.label + " ) goto " + midLabel + ";\n" + $5.traducao + "\tgoto " + endLabel+ ";\n\t"+ midLabel + ":\n" + $7.traducao + "\t" +endLabel + ":\n"; 
			}
			;

/* ----------------JUNCAO DE BLOCO COM COMANDO ------------------------*/
BLOMANDO:	'{' COMANDOS '}' {$$.traducao = $2.traducao;}
			| COMANDOALT
			;

BLOMANDO2: 	BLOCO {$$.traducao = $1.traducao;}
			| COMANDOALT{ $$.traducao = $1.traducao;}

WHILE:		E ')' BLOMANDO // removido o abre parenteses dessa regra devido a conflito de shift/reduce com a regra '(' E ')'
			// parenteses movido para a contra-parte em LOOP_AUX;
			{
				Loop loopinho = getLoop(loops);
				$$.traducao = "\t"+ loopinho.startLabel + ":\n" +$1.traducao + "\t" + $1.label + " = !" + $1.label + ";\n" + "\tif( " + $1.label + " ) goto " + loopinho.endLabel + ";\n" + $3.traducao + "\tgoto "+ loopinho.startLabel + ";\n\t" + loopinho.endLabel + ":\n";
				popLoop(loops);
				//cout<< "teste2" << endl; 
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
				$$.traducao = $3.traducao;
			}
			;

SCAN_ARGS:	TIPO ':' TK_ID ',' SCAN_ARGS
			{
				caracteristicas variavel = buscarVariavel($3.label);
				if($1.traducao != variavel.tipo)
					yyerror("A variavel \""+variavel.nomeVar + "\" eh do tipo " + variavel.tipo + " e o tipo requisitado eh "+ $1.traducao);
				if(variavel.tipo != "string")
				{
					$$.traducao = "\tcin >> " + variavel.localVar + ";\n" + $5.traducao;
				}
				else{
					$$ = leituraString(variavel);
					$$.traducao += $5.traducao;

				}

			}
			| TIPO ':' TK_ID
			{

				caracteristicas variavel = buscarVariavel($3.label);
				if($1.traducao != variavel.tipo)
					yyerror("A variavel \""+variavel.nomeVar + "\" eh do tipo " + variavel.tipo + " e o tipo requisitado eh "+ $1.traducao);
				if($1.traducao != "string")
				{
					$$.traducao = "\tcin >> " + variavel.localVar + ";\n";
				}
				else{
					$$ = leituraString(variavel);
				}
			}
			| error ':' 
			{
				yyerror("tipo do scan nao declarado");
			}
			;

ATRIBUICAO:	TK_ID '=' E 
			{
				$$ = codigoAtribuicao($1, $3);
			}
			;



DECLARACAO:	TIPO TK_ID DECLARACAO_AUX
			{
				$$ = declaracaoVariavel($2.label, $1.traducao);
			}
			| TIPO TK_ID '=' E DECLARACAO_AUX
			{
				$$ = declaracaoVariavelAtribuicao($2.label, $1.traducao, $4);
				//cout<< "label aq" + $4.label;
				$$.traducao += $5.traducao;
			}
			;

DECLARACAO_AUX:',' TK_ID DECLARACAO_AUX 
			{
				$$ = declaracaoVariavel($2.label,tipoDaDeclaracao);
				$$.traducao += $3.traducao;
			}
			| ',' TK_ID '=' E  DECLARACAO_AUX 
			{
				$$ = declaracaoVariavelAtribuicao($2.label, tipoDaDeclaracao, $4);
				//cout<< "label aq" + $4.label;
				$$.traducao += $5.traducao;
			}
			| /*vazio */ {$$.traducao = "";}
			;

//        ----------------	ARITMETICA -----------------------
E:			E '+' E
			{
				$$ = conversaoImplicita($1, $3 , "+");
				cout << "/*traducao = " + $$.traducao + "*/";
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
			| '-' E %prec UMINUS
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
			| TK_STRING{
				$$.traducao = "";
				$$.label = gerarLabel();
				inserirTemporaria($$.label, "string");
				string labelTamanho = gerarLabelStringSize($$.label);
				inserirTemporaria(labelTamanho, "int");
				$$.tipo = "string";
				$$.traducao += "\t" + labelTamanho +  " = " + to_string(contarTamanhoString($1.traducao) + 1) + ";\n";
				$$.traducao += "\t" + $$.label + " = (STRING) malloc(sizeof(char) * " + labelTamanho  + ");\n";
				$$.traducao += "\tstrcpy( " + $$.label + ", \"" + $1.traducao + "\" );\n"; 
				//cout <<"a string encontrada foi " +  $1.traducao << endl;
			}
			;


TIPO:		TK_TIPO_BOOL	{$$.traducao = "bool"; tipoDaDeclaracao = "bool";}
			| TK_TIPO_INT	{$$.traducao = "int"; tipoDaDeclaracao = "int";}
			| TK_TIPO_CHAR	{$$.traducao = "char"; tipoDaDeclaracao = "char";}
			| TK_TIPO_FLOAT	{$$.traducao = "float"; tipoDaDeclaracao = "float";}
			| TK_TIPO_STRING {$$.traducao = "string"; tipoDaDeclaracao = "string";}
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