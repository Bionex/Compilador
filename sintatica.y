
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
#include "headers/main.h"
#include "headers/funcao.h"

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
%token TK_PRINT TK_SCAN TK_ATON
%token TK_GLOBAL
%token TK_RETURN


%start S


%left TK_AND
%left TK_OR
%left TK_NOT
%precedence PREC_VETOR
%left '[' ']'
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
S:			COMANDOS
			{
				if(temErro){
					cout << erros;
				}
				else
					cout << "/*Compilador FOCA*/\n" << "#include <iostream>\n#include <string.h>\n#include <stdio.h>\n\n#define BOOL int\n#define True 1\n#define False 0\n#define STRING char*\n\nusing namespace std;\n\n"<< prototipos <<"\n"<< declararVars() << "\nint main(void)\n{\n"<< declaracoesNull << "\n" <<$1.traducao << "\n\treturn 0;\n}"<< "\n\n" + funcoes << endl; 
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

COMANDO:	STATEMENT PTO_VIRGULA {$$.traducao = $1.traducao;}
			| DECLARACAO PTO_VIRGULA {$$.traducao = $1.traducao;}
			| IF {$$.traducao = $1.traducao;}
			/*| WHILE { $$.traducao = $1.traducao;}
			| DO PTO_VIRGULA{$$.traducao = $1.traducao;}*/
			| SWITCH { $$.traducao = $1.traducao;}
			| LOOP_AUX LOOP {$$.traducao = $2.traducao;}
			| BREAK PTO_VIRGULA {$$.traducao = $1.traducao;}
			| CONTINUE PTO_VIRGULA{ $$.traducao = $1.traducao;}
			| PTO_VIRGULA {$$.traducao = "";}
			| BLOCO {$$.traducao = $1.traducao;}
			//| GLOBAL PTO_VIRGULA {$$.traducao = $1.traducao;}
			| FUNCAO {$$.traducao = "";}
			| RETURN PTO_VIRGULA{$$.traducao = $1.traducao;}
			;

STATEMENT: 	E {$$.traducao = $1.traducao;}
			| ATRIBUICAO {$$.traducao = $1.traducao;}
			| PRINT  {$$.traducao = $1.traducao;}
			| SCAN {$$.traducao = $1.traducao;}
			| ATON{$$.traducao = $1.traducao;}
			;

COMANDOALT:	E PTO_VIRGULA { $$.traducao = $1.traducao; }
			| ATRIBUICAO PTO_VIRGULA { $$.traducao =$1.traducao;}
			| DECLARACAO PTO_VIRGULA {$$.traducao = $1.traducao;}
			| PRINT PTO_VIRGULA {$$.traducao = $1.traducao;}
			| IF {$$.traducao = $1.traducao;}
			/*| WHILE { $$.traducao = $1.traducao;}
			| DO PTO_VIRGULA{$$.traducao = $1.traducao;}*/
			| SWITCH { $$.traducao = $1.traducao;}
			| LOOP_AUX LOOP {$$.traducao = $2.traducao;}
			| BREAK PTO_VIRGULA {$$.traducao = $1.traducao;}
			| CONTINUE PTO_VIRGULA{ $$.traducao = $1.traducao;}
			| SCAN PTO_VIRGULA {$$.traducao = $1.traducao;}
			| PTO_VIRGULA {$$.traducao = "";}
			| RETURN PTO_VIRGULA{$$.traducao = $1.traducao;}
			;

PTO_VIRGULA: ';' {}
			;

ATON:		TK_ATON '(' E ')'
			{
				$$ = converterStringInteiro($3);
			}
			;

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

LOOP: 		DO PTO_VIRGULA 
			{
				$$.traducao = $1.traducao; 
				popEscopo(pilhaContexto);
				popLoop(loops);
			}
			| WHILE 
			{ 
				$$.traducao = $1.traducao; 
				popEscopo(pilhaContexto); 
				popLoop(loops);}
			| FOR 
			{
				$$.traducao = $1.traducao; 
				popEscopo(pilhaContexto); 
				popLoop(loops);
			}
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
			| STATEMENT ',' FOR_ARG1_AUX {$$.traducao = $1.traducao + $3.traducao;}
			| /* VAZIO */ { $$.traducao = "";}
			;

FOR_ARG1_AUX: STATEMENT ',' FOR_ARG1_AUX {$$.traducao = $1.traducao + $3.traducao;}
			| STATEMENT {$$.traducao = $1.traducao;}
			;

FOR_ARG2:	/* vazio */
			{ 
				$$.label = gerarLabel();
				inserirTemporaria($$.label, "bool");
				$$.traducao = "\t" + $$.label + " = True;\n";
			}
			| STATEMENT 
			{
				$$.traducao = $1.traducao;
			}
			| STATEMENT ',' FOR_ARG2_AUX 
			{
				$$.traducao = $1.traducao + $3.traducao;
				$$.label = $3.label;
			}
			;

FOR_ARG2_AUX: STATEMENT {$$.label = $1.label; $$.traducao = $1.traducao;}
			| STATEMENT ',' FOR_ARG2_AUX {$$.traducao = $1.traducao + $3.traducao; $$.label = $3.label;}
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

PRINT: 		TK_PRINT '('FN_ARGS')' {$$.traducao = $3.traducao + "\tcout <<endl;\n";}
			;

FN_ARGS:	E FN_ARGS_AUX 
			{
				$$.traducao = $1.traducao;
				$$.traducao += "\tcout<<" + $1.label + ";\n";
				$$.traducao += $2.traducao;
			}
			| /* empty */{$$.traducao = ""; $$.label = "";}
			;

FN_ARGS_AUX: ',' E  FN_ARGS_AUX
			{
				$$.traducao = $2.traducao + "\tcout<<\", \";\n";
				$$.traducao += "\tcout<<" + $2.label + ";\n";
				$$.traducao += $3.traducao;
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
				if(variavel.tipo != "STRING")
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
				if($1.traducao != "STRING")
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

ATRIBUICAO:	ATR_AUX '=' E 
			{
				$$.traducao = $1.traducao;
				for(int i = 1; i < gambiarra.size(); i++){
					$$.traducao += "\t" + gambiarra[i].label + " = " + gambiarra[i].atr + ";\n";
				}
				atributos aux;
				aux.tipo = $1.tipo;
				aux.label = gambiarra[gambiarra.size() - 1].atr;

				aux = codigoAtribuicao(aux, $3);
				$$.traducao += aux.traducao;
				gambiarra.clear();
			}
			| ATR_AUX '+' '=' E
			{
				$$ = codigoAtribuicaoComposta($1, $4 , "+");
			}
			| ATR_AUX '-' '=' E
			{
				$$ = codigoAtribuicaoComposta($1, $4 , "-");
			}
			| ATR_AUX '*' '=' E
			{
				$$ = codigoAtribuicaoComposta($1, $4 , "*");
			}
			| ATR_AUX '/' '=' E
			{
				$$ = codigoAtribuicaoComposta($1, $4 , "/");
			}
			;

ATR_AUX: 	ATR_AUX '[' E ']'  
			{
				if($1.tipo[$1.tipo.size() - 1] == '*' || $1.tipo == "STRING")
				{
					string tmp = gerarLabel();
					$$.tipo = $1.tipo.substr(0, $1.tipo.size() - 1);
					inserirTemporaria(tmp, $$.tipo);
					gambiarraAtribuicao a;
					$$.label = tmp;
					a.label = tmp;
					$$.traducao = $1.traducao + $3.traducao;
					a.atr = $1.label + "[" + $3.label +"]";
					gambiarra.push_back(a);
					

				}
				else{
					yyerror("O operador [] nao esta definido para o tipo " + $1.tipo);
				}
			}
			| TK_ID 
			{
				caracteristicas c = buscarVariavel($1.label);
				$$.label = c.localVar;
				$$.traducao = "";
				$$.tipo = c.tipo;
				gambiarraAtribuicao a;
				a.atr = c.localVar;
				gambiarra.push_back(a);
			}

DECLARACAO:	TIPO TK_ID DECLARACAO_AUX
			{
				$$ = declaracaoVariavel($2.label, $1.traducao);
				$$.traducao += $3.traducao;
			}
			| TIPO TK_ID '=' E DECLARACAO_AUX
			{
				$$ = declaracaoVariavelAtribuicao($2.label, $1.traducao, $4);
				//cout<< "label aq" + $4.label;
				$$.traducao += $5.traducao;
			}
			| TIPO TK_ID MATRIZ DECLARACAO_AUX
			{
				$$ = declaracaoMatriz($2.label,$1.traducao ,$3.tipo);
				$$.traducao += $4.traducao;
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
			| ',' TK_ID MATRIZ DECLARACAO_AUX
			{
				$$ = declaracaoMatriz($2.label, tipoDaDeclaracao, $3.tipo);
				$$.traducao += $4.traducao;
				
			}
			| /*vazio */ {$$.traducao = "";}
			;

MATRIZ:		'[' E ']' MATRIZ
			{
				labelsMatriz.push_back($2);
				if($2.tipo == "int"){
					$$.tipo = "*" + $4.tipo;

				}
				else{
					yyerror("O numero de posicoes a ser alocada precisa ser um inteiro");
				}
			}
			| /* */{
				$$.traducao = "";
				$$.tipo = "";
				$$.label = "";
			}
			;

FUNCAO:		FUNCAO_AUX '{' COMANDOS '}'
			{
				$$.traducao = $1.traducao + "{\n" + $3.traducao + "}\n";

				funcoes += $$.traducao;
					
				//yyerror("Funcao espera retorno " + $1.tipo + " e o retorno dado foi " + $5.tipo);
				
				popFunction();
				popEscopo(pilhaContexto);

			}
			;

FUNCAO_AUX:	TIPO TK_ID BLOCO_AUX '(' ATRIBUTOS ')'
			{
				caracteristicas c;
				c.tipo = "function";
				c.localVar = gerarFuncaoLabel();
				c.nomeVar = $2.label;

				Function f = createFunction(numeroAtributos);
				f.atributos = tipoAtributos;
				f.nomeFuncao = $2.label;
				f.nomeLocal = c.localVar;
				f.tipoRetorno = $1.traducao;
				pushFunction(f.tipoRetorno);
				bool conseguiu = inserirFuncao(f);

				if(conseguiu){

					prototipos += f.tipoRetorno + " "+ f.nomeLocal +"( ";
					for(int i = 0; i < numeroAtributos; i++){
						if(i == 0){
							prototipos += tipoAtributos[i];
						}
						else
							prototipos += ", " + tipoAtributos[i];
					}
					prototipos += " );\n";

					numeroAtributos = 0;
					tipoAtributos.clear();

					addVar2EscopoSuperior(pilhaContexto, c);
					
					$$.tipo = $1.traducao;
					$$.traducao = $1.traducao + " " + c.localVar + "( " + $5.traducao + ")\n";

				}
				else{
					yyerror("Não foi possivel fazer sobrecarga da funcao " + $1.traducao + " " + $2.label + "( " + $5.traducao + ")");
				}
			}

RETURN:		TK_RETURN E
			{
				$$.traducao = $2.traducao + "\treturn " + $2.label+ ";\n";
				$$.tipo = $2.tipo;
				string tipoFuncao = getTopFunction();
				if($2.tipo != tipoFuncao){
					//verifica se eh possivel fazer coercao se não for erro

					yyerror("A funcao espera retorno " + tipoFuncao + " e nao eh possivel fazer a conversao de " + $2.tipo  + " para " + tipoFuncao);
				}
			}

ATRIBUTOS:	AUX_ATRIBUTOS ',' TIPO TK_ID
			{
				numeroAtributos++;
				caracteristicas c = buscarVariavel($4.label);
				if(c.localVar == ""){
					c.tipo = $3.traducao;
					c.localVar = labelUsuario();
					c.nomeVar = $4.label;
					$$.traducao = $1.traducao +", " + c.tipo + " "+  c.localVar;
					inserirTemporaria(c.localVar, c.tipo);
					addVar2Escopo(pilhaContexto, c);
					tipoAtributos.push_back($3.traducao);
				}
				else
					yyerror("Variavel " + c.nomeVar + " ja foi usada na declaracao da funcao anteriormente");
				
				
			}
			| TIPO TK_ID
			{
				numeroAtributos++;
				caracteristicas c = buscarVariavel($2.label);
				if(c.localVar == ""){
					c.tipo = $1.traducao;
					c.localVar = labelUsuario();
					c.nomeVar = $2.label;
					$$.traducao = c.tipo + " " + c.localVar;
					inserirTemporaria(c.localVar, c.tipo);
					addVar2Escopo(pilhaContexto, c);
					tipoAtributos.push_back($1.traducao);
				}
				else
					yyerror("Variavel " + c.nomeVar + " ja foi usada na declaracao da funcao anteriormente");
				
			}
			|/*VAZIO */ {$$.traducao = "";};
			;

AUX_ATRIBUTOS: AUX_ATRIBUTOS ',' TIPO TK_ID 
			{
				numeroAtributos++;
				caracteristicas c = buscarVariavel($4.label);
				if(c.localVar == ""){
					c.tipo = $3.traducao;
					c.localVar = labelUsuario();
					c.nomeVar = $4.label;
					$$.traducao = $1.traducao +", " + c.tipo + " "+  c.localVar;
					inserirTemporaria(c.localVar, c.tipo);
					addVar2Escopo(pilhaContexto, c);
					tipoAtributos.push_back($3.traducao);
				}
				else
					yyerror("Variavel " + c.nomeVar + " ja foi usada na declaracao da funcao anteriormente");
				
			}
			| TIPO TK_ID
			{
				numeroAtributos++;
				caracteristicas c = buscarVariavel($2.label);
				if(c.localVar == ""){
					c.tipo = $1.traducao;
					c.localVar = labelUsuario();
					c.nomeVar = $2.label;
					$$.traducao = c.tipo + " " + c.localVar;
					inserirTemporaria(c.localVar, c.tipo);
					addVar2Escopo(pilhaContexto, c);
					tipoAtributos.push_back($1.traducao);
				}
				else
					yyerror("Variavel " + c.nomeVar + " ja foi usada na declaracao da funcao anteriormente");
			
			}
			;

/*GLOBAL: 	TK_GLOBAL TIPO TK_ID GLOBAL_AUX 
			{
				//cout<< "AAAAAAAAAAAAAAAAAAA" << endl;
				$$ = declaracaoVariavelGlobal($3.label,tipoDaDeclaracao);
				$$.traducao += $4.traducao;
			}
			| TK_GLOBAL TIPO TK_ID '=' E GLOBAL_AUX 
			{
				$$ = declaracaoVariavelAtribuicaoGlobal($3.label, tipoDaDeclaracao, $5);
				$$.traducao += $6.traducao;
			}
			;

GLOBAL_AUX:	',' TK_ID GLOBAL_AUX 
			{
				$$ = declaracaoVariavelGlobal($3.label,tipoDaDeclaracao);
			}
			| ',' TK_ID '=' E GLOBAL_AUX 
			{
				$$ = declaracaoVariavelAtribuicaoGlobal($2.label, tipoDaDeclaracao, $4);
			}
			| /* vazio *//*{$$.traducao = "";}
			;
*/

//        ----------------	ARITMETICA -----------------------
E:			E '+' E
			{
				$$ = conversaoImplicita($1, $3 , "+");
				//cout << "/*traducao = " + $$.traducao + "*/";
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
				if($4.tipo != "STRING"){
					$$.label = gerarLabel();
					$$.tipo = $2.traducao;
					inserirTemporaria($$.label, $$.tipo);
					$$.traducao = $4.traducao + "\t" + $$.label + " = (" + $2.traducao + ") " + $4.label + ";\n";
				}
				else{
					yyerror("Não é possivel converter string para " + $2.traducao + ", use a funcao: \n\t\tfloat aton(string)");
				}
			}

			| E VETOR
			{
				
				if($1.tipo == "STRING"){
					string temporaria = gerarLabel();
					inserirTemporaria(temporaria, "char");
					//cout << temporaria << endl;
					$$.traducao = $1.traducao;
					$$.traducao += $2.traducao;
					$$.traducao += "\t" + temporaria + " = "+ $1.label + "[" + $2.label + "];\n";
					$$.label = temporaria;
					$$.tipo = "char";
				}
				if($1.tipo[$1.tipo.size() - 1] == '*')
				{
					string tipo = $1.tipo.substr(0, $1.tipo.size()-1);
					string temporaria = gerarLabel();
					inserirTemporaria(temporaria,tipo);
					//cout << temporaria << endl;
					$$.traducao = $1.traducao;
					$$.traducao += $2.traducao;
					$$.traducao += "\t" + temporaria + " = "+ $1.label + "[" + $2.label + "];\n";
					$$.label = temporaria;
					$$.tipo = tipo;
				}
				else{
					yyerror("O operador [] nao esta definido para " + $1.tipo);
				}
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
			| TK_GLOBAL TK_ID
			{
				caracteristicas variavel = buscarVariavelGlobal($2.label);
				if(variavel.localVar == ""){
					yyerror("A variavel global \"" + $2.label +"\" foi usada e não foi declarada ainda ");
				}
				$$.label = variavel.localVar;
				$$.traducao = "";
				$$.tipo = variavel.tipo;
				//cout << "$1.tipo = " << $1.tipo << endl;
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
				inserirTemporaria($$.label, "STRING");
				string labelTamanho = gerarLabelStringSize($$.label);
				inserirTemporaria(labelTamanho, "int");
				$$.tipo = "STRING";
				$$.traducao += "\t" + labelTamanho +  " = " + to_string(contarTamanhoString($1.traducao) + 1) + ";\n";
				$$.traducao += "\t" + $$.label + " = (STRING) realloc(" + $$.label + ", " + labelTamanho  + ");\n";
				$$.traducao += "\tstrcpy( " + $$.label + ", \"" + $1.traducao + "\" );\n"; 
				//cout <<"a string encontrada foi " +  $1.traducao << endl;
			}
			| TK_ID '(' PARAMETROS ')' 
			{
				caracteristicas c = buscarVariavel($1.label);
				if(c.tipo == "function"){
					vector<Function> f = buscarFuncao($1.label);
					if(!f.empty())
					{
						bool achou = false;
						for(int x = 0; x < f.size();x++)
						{
							if(numeroAtributosChamada == f[x].numeroAtributos){
								if(tipoAtributosChamada == f[x].atributos)
								{
									string labelTmp = gerarLabel();
									string tipo = f[x].tipoRetorno;
									$$.tipo = tipo;
									$$.label = labelTmp;
									inserirTemporaria(labelTmp, tipo);
									achou = true;
									$$.traducao = $3.traducao + "\t" + labelTmp +" = " + f[x].nomeLocal + "(" + $3.label + ");\n";
									break;
								}
							}
						}
						if(achou == false){	
							string errorMessage;
							for(int i = 0; i < numeroAtributosChamada; i++){
								if(i == 0)
									errorMessage += tipoAtributosChamada[i];
								else
									errorMessage += ", "+ tipoAtributosChamada[i];
							}
							yyerror("Nao foi possivel achar uma funcao com o nome " + $1.label + " e os atributos ("+ errorMessage + ")");
						}
						
						
					
					}
				}
				else if(c.tipo != "")
					yyerror("Tentativa de chamar " + $1.label + " que não eh uma funcao.");	
				else
					yyerror($2.label + " não foi declarado ainda");
				
				numeroAtributosChamada = 0;
				tipoAtributosChamada.clear();
			}
			;

PARAMETROS:	E 
			{
				numeroAtributosChamada++;
				tipoAtributosChamada.push_back($1.tipo);
				$$.traducao = $1.traducao;
				$$.label = $1.label;
			}
			| AUX_PARAMETROS ',' E
			{
				numeroAtributosChamada++;
				tipoAtributosChamada.push_back($3.tipo);
				$$.traducao = $1.traducao + $3.traducao;
				$$.label = $1.label + ", " + $3.label;
			}
			| /*VAZIO */{$$.traducao = ""; $$.label = "";}
			;

AUX_PARAMETROS:	E
			{
				numeroAtributosChamada++;
				tipoAtributosChamada.push_back($1.tipo);
				$$.traducao = $1.traducao;
				$$.label = $1.label;
			}
			| AUX_PARAMETROS ',' E
			{
				numeroAtributosChamada++;
				tipoAtributosChamada.push_back($3.tipo);
				$$.traducao = $1.traducao + $3.traducao;
				$$.label = $1.label + ", " + $3.label;
			}

VETOR:		'[' E ']'
			{
				if($2.tipo == "int"){
					$$.traducao = $2.traducao;
					$$.label = $2.label;
					$$.tipo = $2.tipo;
				}
				else
					yyerror("O indice precisa ser um inteiro");

			}
			;

TIPO:		TK_TIPO_BOOL	{$$.traducao = "BOOL"; tipoDaDeclaracao = "BOOL";}
			| TK_TIPO_INT	{$$.traducao = "int"; tipoDaDeclaracao = "int";}
			| TK_TIPO_CHAR	{$$.traducao = "char"; tipoDaDeclaracao = "char";}
			| TK_TIPO_FLOAT	{$$.traducao = "float"; tipoDaDeclaracao = "float";}
			| TK_TIPO_STRING {$$.traducao = "STRING"; tipoDaDeclaracao = "STRING";}
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