
%{
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <map>

#define YYSTYPE atributos
#define oi(N) cout << "oi "<< N << endl

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

typedef struct coercao {
	int op;
	string tipo;
} Coercao;

typedef std::tuple<string, string, string> KeyTriple;

int yylex(void);
void yyerror(string);
string gerarLabel();
string labelUsuario();
string declararVars();
void inserirTabela(string);
void inserirTemporaria(string, string);
string verificarCoercao(string , string  ,string );
KeyTriple genKey(string , string, string);
struct atributos conversaoImplicita(struct atributos, struct atributos, string);
struct atributos declaracaoVariavel(struct atributos, string);
struct atributos operacaoRelacional(struct atributos, struct atributos, string);

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
%token TK_AND TK_OR
%token TK_LOGICO



%start S

%left '+' '-'
%left '*' '/'
%left '(' ')'
%left '<' '>' TK_NOT_EQ TK_EQ TK_BIG_EQ TK_SMALL_EQ
%left TK_OR
%left TK_AND

%%
//{          ---------------- REGRAS ---------------------
S:			TK_TIPO_INT TK_MAIN '(' ')' BLOCO
			{
				cout << "/*Compilador FOCA*/\n" << "#include <iostream>\n#include <string.h>\n#include <stdio.h>\n\nint main(void)\n{\n" << declararVars() << "\n" << $5.traducao << "\n\treturn 0;\n}" << endl; 
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

ATRIBUICAO:	TK_ID '=' E 
			{

				string var = revertTable[$1.label];
				$1.tipo = tabela[var].tipo;
				if($1.tipo == $3.tipo){
					$$.traducao = $3.traducao +  "\t" + $1.label + " = " + $3.label + ";\n";
				}
				else{
					string aux = verificarCoercao($1.tipo, "=", $3.tipo);
					if(aux != ""){
						$$.traducao = $3.traducao +  "\t" + $1.label + " = " + "(" + aux + ")" + $3.label + ";\n";
					}
					else{
						yyerror("a operacao = nao esta definida para " + $1.tipo + " e " + $3.tipo);
					}

				}
			}
			;

DECLARACAO:	TK_TIPO_INT TK_ID
			{
				$$ = declaracaoVariavel($2, "int");
			}
			| TK_TIPO_INT TK_ID '=' E
			{
				/*
				string var = revertTable[$2.label];
				if(tabela.find(var) != tabela.end()){
					if(tabela[var].tipo == "Undefined"){
						tabela[var].tipo = "int";
						temporarias[$2.label] = "int";
					}
				}
				*/
			}

			| TK_TIPO_FLOAT TK_ID
			{
				$$ = declaracaoVariavel($2, "float");
			}
			| TK_TIPO_CHAR TK_ID
			{
				$$ = declaracaoVariavel($2, "char");
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
			| '(' E ')' 
			{
				$$.label = $2.label;
				$$.traducao = $2.traducao;
				$$.tipo = $2.tipo;

			}
			// ---------------------- PARTE LOGICA ---------------------------

			| E TK_AND E {
				$$ = conversaoImplicita($1, $3, "&&");

			}
			| E TK_OR E {
				$$ = conversaoImplicita($1, $3, "||");

			}

			//---------------------------- RELACIONAL ------------------------
			| E '<' E{
				$$ = operacaoRelacional($1, $3, "<");
			}

			| E '>' E{
				$$ = operacaoRelacional($1, $3, ">");
			}
			| E TK_BIG_EQ E{
				$$ = operacaoRelacional($1, $3, ">=");
			}

			| E TK_SMALL_EQ E{
				$$ = operacaoRelacional($1, $3, "<=");
			}

			| E TK_EQ E{
				$$ = operacaoRelacional($1, $3, "==");
			}
			| E TK_NOT_EQ E{
				$$ = operacaoRelacional($1, $3, "!=");
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
				$$.label = $1.label;
				$$.traducao = "";
				$$.tipo = $1.tipo;
				//cout << "$1.tipo = " << $1.tipo << endl;
			}
			| TK_LOGICO{
				$$.label = gerarLabel();
				inserirTemporaria($$.label, "bool");
				$$.tipo = "bool";
				$$.traducao = "\t" + $$.label + " = " + $1.traducao + ";\n";

			}
			;
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
	if(tabelaCoercao.find(chave) != tabelaCoercao.end()){
		return tabelaCoercao[chave];
	}


	if( operador != "="){
		get<0>(chave) = opDois;
		get<2>(chave) = opUm;
		if(tabelaCoercao.find(chave) != tabelaCoercao.end())
			return tabelaCoercao[chave];
	}

	return "";
}

void inicializarTabelaCoercao(){

	tabelaCoercao[genKey("int" , "+" , "int")] = "int";
	tabelaCoercao[genKey("int" , "-" , "int")] = "int";
	tabelaCoercao[genKey("int" , "*" , "int")] = "int";
	tabelaCoercao[genKey("int" , "/" , "int")] = "float";

	tabelaCoercao[genKey("float", "+", "float")] = "float";
	tabelaCoercao[genKey("float", "-", "float")] = "float";
	tabelaCoercao[genKey("float", "*", "float")] = "float";
	tabelaCoercao[genKey("float", "/", "float")] = "float";

	tabelaCoercao[genKey("int", "+", "float")] = "float";
	tabelaCoercao[genKey("int", "-", "float")] = "float";
	tabelaCoercao[genKey("int", "*", "float")] = "float";
	tabelaCoercao[genKey("int", "/", "float")] = "float";

	
	



	tabelaCoercao[genKey("int", "=", "float")] = "int";
	tabelaCoercao[genKey("float", "=", "int")] = "float";


	tabelaCoercao[genKey("bool" , "&&", "bool")] = "bool";
	tabelaCoercao[genKey("bool" , "||", "bool")] = "bool";

	//tabelaCoercao[genKey("bool" , "<", "bool")] = "bool";
	tabelaCoercao[genKey("int" , "<", "int")] = "bool";
	tabelaCoercao[genKey("float" , "<", "float")] = "bool";
	tabelaCoercao[genKey("int" , "<", "float")] = "bool";

	tabelaCoercao[genKey("int" , ">", "int")] = "bool";
	tabelaCoercao[genKey("float" , ">", "float")] = "bool";
	tabelaCoercao[genKey("int" , ">", "float")] = "bool";

	tabelaCoercao[genKey("int" , ">=", "int")] = "bool";
	tabelaCoercao[genKey("float" , ">=", "float")] = "bool";
	tabelaCoercao[genKey("int" , ">=", "float")] = "bool";

	tabelaCoercao[genKey("int" , "<=", "int")] = "bool";
	tabelaCoercao[genKey("float" , "<=", "float")] = "bool";
	tabelaCoercao[genKey("int" , "<=", "float")] = "bool";


	tabelaCoercao[genKey("int" , "==", "int")] = "bool";
	tabelaCoercao[genKey("float" , "==", "float")] = "bool";
	tabelaCoercao[genKey("int" , "==", "float")] = "bool";
	tabelaCoercao[genKey("char" , "==", "char")] = "bool";
	tabelaCoercao[genKey("bool" , "==", "bool")] = "bool";

	tabelaCoercao[genKey("int" , "!=", "int")] = "bool";
	tabelaCoercao[genKey("float" , "!=", "float")] = "bool";
	tabelaCoercao[genKey("int" , "!=", "float")] = "bool";
	tabelaCoercao[genKey("char" , "!=", "char")] = "bool";
	tabelaCoercao[genKey("bool" , "!=", "bool")] = "bool";





	//tabelaCoercao[] = "float";
}

KeyTriple genKey(string a , string b, string c){
	KeyTriple chave (a , b, c);
	return chave;
}

struct atributos conversaoImplicita(struct atributos $1, struct atributos $3 , string operador){
	struct atributos $$;

	if(revertTable.find($1.label) != revertTable.end() )
		$1.tipo = tabela[revertTable[$1.label]].tipo;

	if(revertTable.find($3.label) != revertTable.end() )
		$3.tipo = tabela[revertTable[$3.label]].tipo;


	
	string aux = verificarCoercao($1.tipo, operador, $3.tipo);

	if(aux != ""){

		$$.label = gerarLabel();
		inserirTemporaria($$.label , aux);


		$$.tipo = aux;
		if($1.tipo == aux && $3.tipo == aux)
			$$.traducao = $1.traducao + $3.traducao  + "\t" + $$.label +" = " + $1.label + " " + operador + " " + $3.label +";\n";

		else{

			string coercaoLabel = gerarLabel();
			inserirTemporaria(coercaoLabel, aux);

			string coercao = "\t"+ coercaoLabel + " = " "("+ aux +") ",resultado;

			if($1.tipo != aux){

				coercao += $1.label;
				resultado = coercaoLabel + " " + operador + " " + $3.label;
			}
			if($3.tipo != aux){

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

struct atributos declaracaoVariavel(struct atributos $2, string tipo){
	struct atributos $$;
	$$.traducao = "";
	string var = revertTable[$2.label];
	if(tabela.find(var) != tabela.end()){
		if(tabela[var].tipo == "Undefined"){
			//cout << "declarando "<< var << " como " << tipo << endl;
			tabela[var].tipo = tipo;
			temporarias[$2.label] = tipo;
		}
	}
	else{
		yyerror("A variavel \"" + var  + "\" ja foi declada como "+ tabela[var].tipo + " anteriormente\n");
	}

	return $$;
}

struct atributos operacaoRelacional(struct atributos $1, struct atributos $3, string operador){
	
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
}