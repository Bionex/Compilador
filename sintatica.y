
%{
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <map>
#include <vector>
#include <stack>
#include "escopo.h"

#define YYSTYPE atributos
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
int getN();
vector<string> split(const string&, const string&);
void inicializarTabelaCoercao();
caracteristicas buscarVariavel(string);
caracteristicas buscarVariavelTopo(string);
atributos caracteristicasToAtributos(caracteristicas);
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



// -------------------------variaveis ------------------------------------------------

int nTemp = 0;
int nUser = 0;
int nGoto = 0;
int lineCount = 1;

stack <SwitchLabels> gambiarraSwitch ;

pilhaMapaPtr pilhaContexto = createMapStack();

std::unordered_map<std::string, string> temporarias;

std::map<KeyTriple, struct coercao> tabelaCoercao;

// --------------------------------------------LEFTS E TOKENS -------------------------------


%}

%token TK_NUM TK_REAL TK_CHAR
%token TK_MAIN TK_ID
%token TK_FIM TK_ERROR
%token TK_TIPO_FLOAT TK_TIPO_INT TK_TIPO_CHAR TK_TIPO_BOOL
%token TK_EQ TK_NOT_EQ TK_BIG_EQ TK_SMALL_EQ
%token TK_AND TK_OR TK_NOT
%token TK_LOGICO
%token TK_PRINT TK_IF TK_WHILE TK_FOR TK_ELSE TK_SWITCH TK_CASE TK_DEFAULT
%token TK_BREAK TK_CONTINUE



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
				cout << "/*Compilador FOCA*/\n" << "#include <iostream>\n#include <string.h>\n#include <stdio.h>\n\n#define BOOL int\n\nint main(void)\n{\n" << declararVars() << "\n" << $5.traducao << "\n\treturn 0;\n}" << endl; 
			}
			;

BLOCO:		BLOCO_AUX '{' COMANDOS '}'
			{
				$$.traducao = $3.traducao;
				popEscopo(pilhaContexto);
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

COMANDO:	E ';' { $$.traducao = $1.traducao; }
			| ATRIBUICAO ';' { $$.traducao =$1.traducao;}
			| DECLARACAO ';'{$$.traducao = $1.traducao;}
			| TK_PRINT '('FN_ARGS')' ';' {$$.traducao = $3.traducao + "\t" + "std::cout <<" + $3.label + "<<std::endl;\n";}
			| IF {$$.traducao = $1.traducao;}
			| WHILE { $$.traducao = $1.traducao;}
			| SWITCH { $$.traducao = $1.traducao;}
			| ';'
			;

SWITCH:		TK_SWITCH '(' SWITCH_AUX ')' '{' caseRecursao TK_DEFAULT':' BLOMANDO '}'
			{
					$$.traducao = $6.traducao + $9.traducao + "\t" + gambiarraSwitch.top().endLabel+ ":\n";
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

WHILE:		TK_WHILE '(' E ')' COMANDO 
			{
				string startLabel = gerarGotoLabel();
				string endLabel = gerarGotoLabel();
				$$.traducao = "\t"+ startLabel + ":\n" +$3.traducao + "\t" + $3.label + " = !" + $3.label + ";\n" + "\tif( " + $3.label + " ) \n\t\t goto " + endLabel + ";\n" + $5.traducao + "\tgoto "+ startLabel + ";\n\t" + endLabel + ":\n"; 
			}
			| TK_WHILE '(' E ')' BLOCO
			{
				string startLabel = gerarGotoLabel();
				string endLabel = gerarGotoLabel();
				$$.traducao = "\t"+ startLabel + ":\n" +$3.traducao + "\t" + $3.label + " = !" + $3.label + ";\n" + "\tif( " + $3.label + " ) \n\t\t goto " + endLabel + ";\n" + $5.traducao + "\tgoto "+ startLabel + ";\n\t" + endLabel + ":\n"; 
			};

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

void yyerror( string MSG )
{
	cout << MSG << endl;
	exit (0);
}				

string gerarLabel(){
	return string("TMP") + to_string(nTemp++);
	
}

string gerarGotoLabel(){
	return string("Label") + to_string(nGoto++);
	
}

string labelUsuario(){
	return string("USRVAR") + to_string(nUser++);
	
}

string declararVars(){
	string retorno = "";
	for(auto &x: temporarias){
		if(x.second == "bool")
			x.second = "BOOL";
		retorno = retorno + "\t" + x.second + " " +x.first + ";\n";
	}
	return retorno;
}

void inserirTabela(string a){
	string aux = labelUsuario();
	pilhaContexto->escopos.back()[a] ={
		aux,
		"Undefined"
	};
	temporarias[aux] = "Undefined";
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



struct coercao verificarCoercao(string opUm, string operador ,string opDois){

	KeyTriple chave (opUm, operador, opDois);
	if(tabelaCoercao.find(chave) != tabelaCoercao.end()){
		return tabelaCoercao[chave];
	}


	if( operador != "="){
		get<0>(chave) = opDois;
		get<2>(chave) = opUm;
		if(tabelaCoercao.find(chave) != tabelaCoercao.end())
			return tabelaCoercao[chave];
	}

	struct coercao a = {"NULL","NULL"};
	return a;
}

void inicializarTabelaCoercao(){

	tabelaCoercao[genKey("int" , "+" , "int")] = {"int", "int"};
	tabelaCoercao[genKey("int" , "-" , "int")] = {"int", "int"};
	tabelaCoercao[genKey("int" , "*" , "int")] = {"int", "int"};
	tabelaCoercao[genKey("int" , "/" , "int")] = {"int", "int"};
	tabelaCoercao[genKey("int" , "%", "int")] = {"int", "int"};

	tabelaCoercao[genKey("float", "+", "float")] = {"float", "float"};
	tabelaCoercao[genKey("float", "-", "float")] = {"float", "float"};
	tabelaCoercao[genKey("float", "*", "float")] = {"float", "float"};
	tabelaCoercao[genKey("float", "/", "float")] = {"float", "float"};

	tabelaCoercao[genKey("int", "+", "float")] = {"float", "float"};
	tabelaCoercao[genKey("int", "-", "float")] = {"float", "float"};
	tabelaCoercao[genKey("int", "*", "float")] = {"float", "float"};
	tabelaCoercao[genKey("int", "/", "float")] = {"float", "float"};

	
	



	tabelaCoercao[genKey("int", "=", "float")] = {"int","int"};
	tabelaCoercao[genKey("float", "=", "int")] = {"float","float"};


	tabelaCoercao[genKey("bool" , "&&", "bool")] = {"bool","bool"};
	tabelaCoercao[genKey("bool" , "||", "bool")] = {"bool","bool"};

	//tabelaCoercao[genKey("bool" , "<", "bool")] = "bool";
	tabelaCoercao[genKey("int" , "<", "int")] = {"bool","int"};
	tabelaCoercao[genKey("float" , "<", "float")] = {"bool","float"};
	tabelaCoercao[genKey("int" , "<", "float")] = {"bool","float"};

	tabelaCoercao[genKey("int" , ">", "int")] = {"bool","int"};
	tabelaCoercao[genKey("float" , ">", "float")] = {"bool","float"};
	tabelaCoercao[genKey("int" , ">", "float")] = {"bool","float"};

	tabelaCoercao[genKey("int" , ">=", "int")] = {"bool","int"};
	tabelaCoercao[genKey("float" , ">=", "float")] = {"bool","float"};
	tabelaCoercao[genKey("int" , ">=", "float")] = {"bool","float"};

	tabelaCoercao[genKey("int" , "<=", "int")] = {"bool","int"};
	tabelaCoercao[genKey("float" , "<=", "float")] = {"bool","float"};
	tabelaCoercao[genKey("int" , "<=", "float")] = {"bool","float"};


	tabelaCoercao[genKey("int" , "==", "int")] = {"bool","int"};
	tabelaCoercao[genKey("float" , "==", "float")] = {"bool","float"};
	tabelaCoercao[genKey("int" , "==", "float")] = {"bool","float"};
	tabelaCoercao[genKey("char" , "==", "char")] = {"bool","char"};
	tabelaCoercao[genKey("bool" , "==", "bool")] = {"bool","bool"};

	tabelaCoercao[genKey("int" , "!=", "int")] = {"bool","int"};
	tabelaCoercao[genKey("float" , "!=", "float")] = {"bool","float"};
	tabelaCoercao[genKey("int" , "!=", "float")] = {"bool","float"};
	tabelaCoercao[genKey("char" , "!=", "char")] = {"bool","char"};
	tabelaCoercao[genKey("bool" , "!=", "bool")] = {"bool","bool"};





	//tabelaCoercao[] = "float";
}

KeyTriple genKey(string a , string b, string c){
	KeyTriple chave (a , b, c);
	return chave;
}

struct atributos conversaoImplicita(struct atributos $1, struct atributos $3 , string operador){
	struct atributos $$;

	struct coercao coercaoToken = verificarCoercao($1.tipo, operador, $3.tipo);

	if(coercaoToken.retornoTipo != "NULL"){

		$$.label = gerarLabel();
		inserirTemporaria($$.label , coercaoToken.retornoTipo);


		$$.tipo = coercaoToken.retornoTipo;
		if($1.tipo == coercaoToken.conversaoTipo && $3.tipo == coercaoToken.conversaoTipo)
			$$.traducao = $1.traducao + $3.traducao  + "\t" + $$.label +" = " + $1.label + " " + operador + " " + $3.label +";\n";

		else{

			string coercaoLabel = gerarLabel();
			inserirTemporaria(coercaoLabel, coercaoToken.conversaoTipo);

			string coercao = "\t"+ coercaoLabel + " = " "("+ coercaoToken.conversaoTipo +") ",resultado;

			if($1.tipo != coercaoToken.conversaoTipo){

				coercao += $1.label;
				resultado = coercaoLabel + " " + operador + " " + $3.label;
			}
			else if($3.tipo != coercaoToken.conversaoTipo){

				coercao += $3.label;
				resultado = $1.label + " " + operador + " " + coercaoLabel;
			}
			coercao += ";\n";
			$$.traducao = $1.traducao + $3.traducao + coercao +"\t" +  $$.label + " = "  + resultado + ";\n";
		}
	}
	else{
		yyerror("a operacao "+ operador + " nao esta definida para " + $1.tipo + " e " + $3.tipo);
	}

	return $$;
}

struct atributos declaracaoVariavel(string var, string tipo){
	struct atributos $$;
	$$.traducao = "";

	caracteristicas varCaracteristicas = buscarVariavelTopo(var);
	
	if(varCaracteristicas.localVar == ""){
		//cout << "testando1" << endl;
		if(varCaracteristicas.tipo == ""){
			//cout << "testando" << endl;
			//cout << "declarando "<< var << " como " << tipo << endl;
			varCaracteristicas.tipo = tipo;
			varCaracteristicas.localVar =labelUsuario();
			varCaracteristicas.nomeVar = var;
			addVar2Escopo(pilhaContexto,varCaracteristicas);
			temporarias[varCaracteristicas.localVar] = tipo;
		}
	}
	else{
		yyerror("A variavel \"" + var  + "\" ja foi declada como "+ varCaracteristicas.tipo + " anteriormente\n");
	}

	return $$;
}

atributos declaracaoVariavelAtribuicao(string var, string tipo, atributos expressao){
	atributos $$;
	$$.traducao = "";

	caracteristicas varCaracteristicas = buscarVariavelTopo(var);
	
	if(varCaracteristicas.localVar == ""){
		//cout << "testando1" << endl;
		if(varCaracteristicas.tipo == ""){
			//cout << "testando" << endl;
			//cout << "declarando "<< var << " como " << tipo << endl;
			varCaracteristicas.tipo = tipo;
			varCaracteristicas.localVar =labelUsuario();
			varCaracteristicas.nomeVar = var;
			addVar2Escopo(pilhaContexto,varCaracteristicas);
			temporarias[varCaracteristicas.localVar] = tipo;
			$$.traducao += expressao.traducao +"\t" + varCaracteristicas.localVar + " = " + expressao.label + ";\n";
		}
	}
	else{
		yyerror("A variavel \"" + var  + "\" ja foi declada como "+ varCaracteristicas.tipo + " anteriormente\n");
	}
	return $$;
}

struct atributos operacaoRelacional(struct atributos $1, struct atributos $3, string operador){	
	/*if(revertTable.find($1.label) != revertTable.end() ){
		caracteristicas atr1 = buscarVariavel(revertTable[$1.label]);
		if(atr1.localVar != "")
			$1.tipo = atr1.tipo;
	}

	if(revertTable.find($3.label) != revertTable.end() ){
		caracteristicas atr3 = buscarVariavel(revertTable[$3.label]);
		if(atr3.localVar != "")
			$3.tipo = atr3.tipo;
	}
	struct coercao aux = verificarCoercao($1.tipo , operador, $3.tipo);
	struct atributos $$;


	$$.label = gerarLabel();
	$$.tipo = "bool";
	inserirTemporaria($$.label , $$.tipo);
	if(aux.retornoTipo != "NULL"){
		$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " " + operador + " " + $3.label + ";\n";
	}
	else{
		yyerror("A operacao " + operador + " não esta definida para os tipos " + $1.tipo + " e " + $3.tipo);
	}

	return $$;*/
}

/*
struct atributos gerarCodigoRelacional(struct atributos $1, struct atributos $3, string operador){
	
	if(revertTable.find($1.label) != revertTable.end() )
		$1.tipo = tabela[revertTable[$1.label]].tipo;

	if(revertTable.find($3.label) != revertTable.end() )
		$3.tipo = tabela[revertTable[$3.label]].tipo;

	string aux = verificarCoercao($1.tipo , operador, $3.tipo);
	struct atributos $$;


	$$.label = gerarLabel();
	$$.tipo = "bool";
	inserirTemporaria($$.label , $$.tipo);
	if(aux != ""){
		$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " " + operador + " " + $3.label + ";\n";
	}
	else{
		yyerror("A operacao " + operador + " não esta definida para os tipos " + $1.tipo + " e " + $3.tipo);
	}

	return $$;
}*/


vector<string> split(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

caracteristicas buscarVariavel(string var){
	for(int i = pilhaContexto->escopoAtual;i >= 0 ;i--){
		tabelaVariavel posAtual = pilhaContexto->escopos[i];
		if(posAtual.find(var) != posAtual.end()){
			return (posAtual[var]);
		}
	}
	return createVar("","", "");

}

caracteristicas buscarVariavelTopo(string var){
	tabelaVariavel topo = pilhaContexto->escopos.back();
	if(topo.find(var) != topo.end()){
		return (topo[var]);
	}
	return createVar("","", "");
}

atributos caracteristicasToAtributos(caracteristicas c){
	atributos atr;
	atr.tipo = c.tipo;
	atr.label = c.localVar;
	atr.traducao = "";
	return atr;
}