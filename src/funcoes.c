#include "../headers/funcoes.h"
#include "../headers/escopo.h"
#include "../headers/loop.h"

using namespace std;

int nTemp = 0;
int nUser = 0;
int nGoto = 0;
int lineCount = 1;

stack <SwitchLabels> gambiarraSwitch ;

string erros = "\n";
bool temErro = 0;

pilhaMapaPtr pilhaContexto = createMapStack();
pilhaLoopPtr loops = createLoopStack();

std::unordered_map<std::string, string> temporarias;

std::map<KeyTriple, struct coercao> tabelaCoercao;

void yyerror( string MSG )
{
	if(MSG == "syntax error")
		cout << MSG << " aa" << endl;

	erros += "linha " + to_string(lineCount) + ": " + MSG + "\n";
	temErro = true;
	return;
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
		yyerror("A variavel \"" + var  + "\" ja foi declada como "+ varCaracteristicas.tipo + " anteriormente");
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
			varCaracteristicas.localVar = labelUsuario();
			varCaracteristicas.nomeVar = var;
			addVar2Escopo(pilhaContexto,varCaracteristicas);
			temporarias[varCaracteristicas.localVar] = tipo;
			$$.traducao += expressao.traducao +"\t" + varCaracteristicas.localVar + " = " + expressao.label + ";\n";
		}
	}
	else{
		yyerror("A variavel \"" + var  + "\" ja foi declada como "+ varCaracteristicas.tipo + " anteriormente");
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