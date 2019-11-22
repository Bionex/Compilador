#include "../headers/main.h"
#include "../headers/escopo.h"
#include "../headers/loop.h"

using namespace std;

int nTemp = 0;
int nUser = 0;
int nGoto = 0;
int nGotoIf = 0;
int nGotoSwitch = 0;
int nGotoCase = 0;
int nGotoWhile = 0;
int nGotoDo = 0;
int nGotoFor = 0;
int lineCount = 1;
int nFuncao = 0;

stack <SwitchLabels> gambiarraSwitch ;

string tipoDaDeclaracao = "";

string erros = "\n";
string funcoes = "\n//funcoes\n";
string prototipos = "\n//prototipos\n";
int numeroAtributos = 0;
vector<string> tipoAtributos;

int numeroAtributosChamada = 0;
vector<string> tipoAtributosChamada;

bool temErro = 0;

string declaracoesNull;

pilhaMapaPtr pilhaContexto = createMapStack();
pilhaLoopPtr loops = createLoopStack();

std::unordered_map<std::string, string> temporarias;

std::map<KeyTriple, struct coercao> tabelaCoercao;

void yyerror( string MSG )
{
	if(MSG == "syntax error"){
		cout << "linha "<<lineCount<<": "<<MSG << endl;
		exit(-1);
	}
	//cout << "erro -> " + MSG << endl;
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

string gerarFuncaoLabel(){
	return "FUNCTION" + to_string(nFuncao++);
}
Loop gerarGotoDoLabel(){
	string startLabel = "do_inicio_" + to_string(nGotoDo);
	string endLabel = "do_fim_" + to_string(nGotoDo);
	string continueLabel = "do_continue_" + to_string(nGotoDo++);

	Loop loopinho = {startLabel, endLabel, continueLabel};
	return loopinho;
}

Loop gerarGotoWhileLabel(){
	string startLabel = "while_inicio_continue_" + to_string(nGotoWhile);
	string endLabel = "while_fim_" + to_string(nGotoWhile++);

	Loop loopinho = {startLabel, endLabel, startLabel};

	return loopinho;

}

Loop gerarGotoForLabel(){
	string startLabel = "for_inicio_" + to_string(nGotoFor);
	string endLabel = "for_fim_" + to_string(nGotoFor);
	string continueLabel = "for_continue_" + to_string(nGotoFor++);

	Loop loopinho = {startLabel, endLabel, continueLabel};
	return loopinho;
}

string gerarGotoCaseLabel(int nSwitch){
	return "switch_"+to_string(nSwitch) + "_case_" + to_string(nGotoCase++);
}
string gerarGotoSwitchLabel(){
	return "switch_" + to_string(nGotoSwitch++) + "_fim";
}

string labelUsuario(){
	return string("USRVAR") + to_string(nUser++);
	
}

string declararVars(){
	string retorno = "";
	for(auto &x: temporarias){
		retorno = retorno + "" + x.second + " " +x.first + ";\n";
		if(x.second == "STRING")
			declaracoesNull +=  x.first + " = NULL;\n";
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

	tabelaCoercao[genKey("char" , "+", "char")] = {"char", "char"};
	tabelaCoercao[genKey("char" , "-", "char")] = {"char", "char"};


	
	



	tabelaCoercao[genKey("int", "=", "float")] = {"int","int"};
	tabelaCoercao[genKey("float", "=", "int")] = {"float","float"};


	tabelaCoercao[genKey("BOOL" , "&&", "BOOL")] = {"BOOL","BOOL"};
	tabelaCoercao[genKey("BOOL" , "||", "BOOL")] = {"BOOL","BOOL"};

	//tabelaCoercao[genKey("BOOL" , "<", "BOOL")] = "BOOL";
	tabelaCoercao[genKey("int" , "<", "int")] = {"BOOL","int"};
	tabelaCoercao[genKey("float" , "<", "float")] = {"BOOL","float"};
	tabelaCoercao[genKey("char" , "<", "char")] = {"BOOL", "char"};
	tabelaCoercao[genKey("int" , "<", "float")] = {"BOOL","float"};

	tabelaCoercao[genKey("int" , ">", "int")] = {"BOOL","int"};
	tabelaCoercao[genKey("float" , ">", "float")] = {"BOOL","float"};
	tabelaCoercao[genKey("char" , ">", "char")] = {"BOOL", "char"};
	tabelaCoercao[genKey("int" , ">", "float")] = {"BOOL","float"};

	tabelaCoercao[genKey("int" , ">=", "int")] = {"BOOL","int"};
	tabelaCoercao[genKey("float" , ">=", "float")] = {"BOOL","float"};
	tabelaCoercao[genKey("int" , ">=", "float")] = {"BOOL","float"};
	tabelaCoercao[genKey("char" , ">=", "char")] = {"BOOL", "char"};

	tabelaCoercao[genKey("int" , "<=", "int")] = {"BOOL","int"};
	tabelaCoercao[genKey("float" , "<=", "float")] = {"BOOL","float"};
	tabelaCoercao[genKey("int" , "<=", "float")] = {"BOOL","float"};
	tabelaCoercao[genKey("char" , "<=", "char")] = {"BOOL", "char"};

	tabelaCoercao[genKey("int" , "==", "int")] = {"BOOL","int"};
	tabelaCoercao[genKey("float" , "==", "float")] = {"BOOL","float"};
	tabelaCoercao[genKey("int" , "==", "float")] = {"BOOL","float"};
	tabelaCoercao[genKey("char" , "==", "char")] = {"BOOL","char"};
	tabelaCoercao[genKey("BOOL" , "==", "BOOL")] = {"BOOL","BOOL"};

	tabelaCoercao[genKey("int" , "!=", "int")] = {"BOOL","int"};
	tabelaCoercao[genKey("float" , "!=", "float")] = {"BOOL","float"};
	tabelaCoercao[genKey("int" , "!=", "float")] = {"BOOL","float"};
	tabelaCoercao[genKey("char" , "!=", "char")] = {"BOOL","char"};
	tabelaCoercao[genKey("BOOL" , "!=", "BOOL")] = {"BOOL","BOOL"};

	tabelaCoercao[genKey("STRING" , "+" , "STRING")] = {"STRING", "STRING"};
	tabelaCoercao[genKey("STRING", "==", "STRING")] = {"BOOL", "STRING"};
	tabelaCoercao[genKey("STRING", "!=", "STRING")] = {"BOOL", "STRING"};
	tabelaCoercao[genKey("STRING", "<", "STRING")] = {"BOOL", "STRING"};
	tabelaCoercao[genKey("STRING", ">", "STRING")] = {"BOOL", "STRING"};
	tabelaCoercao[genKey("STRING", "<=", "STRING")] = {"BOOL", "STRING"};
	tabelaCoercao[genKey("STRING", ">=", "STRING")] = {"BOOL", "STRING"};






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

		if(coercaoToken.conversaoTipo != "STRING")
		{
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
		else
		{
			$$.tipo = coercaoToken.retornoTipo;
			if(operador == "+")
			{
				string sizeA = gerarLabelStringSize($1.label), sizeB = gerarLabelStringSize($3.label);
				string sizeFinal = gerarLabelStringSize($$.label);
				inserirTemporaria(sizeFinal, "int");
				$$.traducao = $1.traducao + $3.traducao;
				$$.traducao += "\t" + sizeFinal + " = " + sizeA + " + " + sizeB + ";\n";
				$$.traducao += "\t" + sizeFinal + " = " + sizeFinal + " - 1;\n";
				$$.traducao += "\t" + $$.label + " = (STRING) realloc(" + $$.label  + ", " + sizeFinal + " );\n";
				$$.traducao += "\t" + $$.label + "[0] = '\\0';\n";  
				$$.traducao += "\tstrcat("+ $$.label + ", "+ $1.label +");\n";
				$$.traducao += "\tstrcat("+ $$.label + ", "+ $3.label +");\n";
			}
			else if(operador == "=="){
				$$.traducao = $1.traducao + $3.traducao;
				string labelTMPSTRCMP = gerarLabel();
				inserirTemporaria(labelTMPSTRCMP, "int");
				$$.traducao += "\t" + labelTMPSTRCMP + " = strcmp(" + $1.label+ ", " + $3.label + " );\n";
				string labelTMPBOOL1 = gerarLabel();
				inserirTemporaria(labelTMPBOOL1, "BOOL");
				string labelTMPInt = gerarLabel();
				inserirTemporaria(labelTMPInt, "int");
				$$.traducao += "\t" + labelTMPInt + " = 0;\n";
				$$.traducao += "\t" + labelTMPBOOL1 + " = " + labelTMPSTRCMP + " == " +  labelTMPInt + ";\n";
				$$.label = labelTMPBOOL1;
			}
			else if(operador == "!="){
				$$.traducao = $1.traducao + $3.traducao;
				string labelTMPSTRCMP = gerarLabel();
				inserirTemporaria(labelTMPSTRCMP, "int");
				$$.traducao += "\t" + labelTMPSTRCMP + " = strcmp(" + $1.label+ ", " + $3.label + " );\n";
				string labelTMPBOOL1 = gerarLabel();
				inserirTemporaria(labelTMPBOOL1, "BOOL");
				string labelTMPInt = gerarLabel();
				inserirTemporaria(labelTMPInt, "int");
				$$.traducao += "\t" + labelTMPInt + " = 0;\n";
				$$.traducao += "\t" + labelTMPBOOL1 + " = " + labelTMPSTRCMP + " != " +  labelTMPInt + ";\n";
				$$.label = labelTMPBOOL1;
			}
			else if(operador == "<"){
				$$.traducao = $1.traducao + $3.traducao;
				string labelTMPSTRCMP = gerarLabel();
				inserirTemporaria(labelTMPSTRCMP, "int");
				$$.traducao += "\t" + labelTMPSTRCMP + " = strcmp(" + $1.label+ ", " + $3.label + " );\n";
				string labelTMPBOOL1 = gerarLabel();
				inserirTemporaria(labelTMPBOOL1, "BOOL");
				string labelTMPInt = gerarLabel();
				inserirTemporaria(labelTMPInt, "int");
				$$.traducao += "\t" + labelTMPInt + " = -1;\n";
				$$.traducao += "\t" + labelTMPBOOL1 + " = " + labelTMPSTRCMP + " == " +  labelTMPInt + ";\n";
				$$.label = labelTMPBOOL1;
			}
			else if(operador == ">"){
				$$.traducao = $1.traducao + $3.traducao;
				string labelTMPSTRCMP = gerarLabel();
				inserirTemporaria(labelTMPSTRCMP, "int");
				$$.traducao += "\t" + labelTMPSTRCMP + " = strcmp(" + $1.label+ ", " + $3.label + " );\n";
				string labelTMPBOOL1 = gerarLabel();
				inserirTemporaria(labelTMPBOOL1, "BOOL");
				string labelTMPInt = gerarLabel();
				inserirTemporaria(labelTMPInt, "int");
				$$.traducao += "\t" + labelTMPInt + " = 1;\n";
				$$.traducao += "\t" + labelTMPBOOL1 + " = " + labelTMPSTRCMP + " == " +  labelTMPInt + ";\n";
				$$.label = labelTMPBOOL1;
			}
			else if(operador == ">="){
				$$.traducao = $1.traducao + $3.traducao;
				string labelTMPSTRCMP = gerarLabel();
				inserirTemporaria(labelTMPSTRCMP, "int");
				$$.traducao += "\t" + labelTMPSTRCMP + " = strcmp(" + $1.label+ ", " + $3.label + " );\n";
				string labelTMPBOOL1 = gerarLabel();
				inserirTemporaria(labelTMPBOOL1, "BOOL");
				string labelTMPInt = gerarLabel();
				inserirTemporaria(labelTMPInt, "int");
				$$.traducao += "\t" + labelTMPInt + " = -1;\n";
				$$.traducao += "\t" + labelTMPBOOL1 + " = " + labelTMPSTRCMP + " != " +  labelTMPInt + ";\n";
				$$.label = labelTMPBOOL1;
			}
			else if(operador == "<="){
				$$.traducao = $1.traducao + $3.traducao;
				string labelTMPSTRCMP = gerarLabel();
				inserirTemporaria(labelTMPSTRCMP, "int");
				$$.traducao += "\t" + labelTMPSTRCMP + " = strcmp(" + $1.label+ ", " + $3.label + " );\n";
				string labelTMPBOOL1 = gerarLabel();
				inserirTemporaria(labelTMPBOOL1, "BOOL");
				string labelTMPInt = gerarLabel();
				inserirTemporaria(labelTMPInt, "int");
				$$.traducao += "\t" + labelTMPInt + " = 1;\n";
				$$.traducao += "\t" + labelTMPBOOL1 + " = " + labelTMPSTRCMP + " != " +  labelTMPInt + ";\n";
				$$.label = labelTMPBOOL1;
			}
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
			if(tipo == "int")
				$$.traducao += "\t" + varCaracteristicas.localVar + " = 0;\n";
			else if(tipo == "BOOL")
				$$.traducao += "\t" + varCaracteristicas.localVar + " = False;\n";
			else if(tipo == "float")
				$$.traducao += "\t" + varCaracteristicas.localVar + " = 0.0;\n";
			else if(tipo == "char")
				$$.traducao += "\t" + varCaracteristicas.localVar + " = 'a';\n";
			
			else if(tipo == "STRING"){
				string labelSize = gerarLabelStringSize(varCaracteristicas.localVar);
				$$.traducao += "\t" + labelSize + " = 1;\n";
				inserirTemporaria(labelSize,"int");
				$$.traducao += "\t" + varCaracteristicas.localVar + " = (STRING) realloc(" + varCaracteristicas.localVar + ", " + labelSize + ");\n";
				$$.traducao += "\t" + varCaracteristicas.localVar + "[0] = \'\\0\';\n";
			}
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
	
	if(varCaracteristicas.localVar == "")
	{
		//cout << "testando1" << endl;
		if(varCaracteristicas.tipo == "")
		{
			//cout << "testando" << endl;
			//cout << "declarando "<< var << " como " << tipo << endl;
			varCaracteristicas.tipo = tipo;
			varCaracteristicas.localVar = labelUsuario();
			varCaracteristicas.nomeVar = var;
			addVar2Escopo(pilhaContexto,varCaracteristicas);
			temporarias[varCaracteristicas.localVar] = tipo;
			atributos auxiliarVariavel = {var, "" , tipo};
			atributos attr = codigoAtribuicao(auxiliarVariavel,expressao);
			$$.traducao += attr.traducao; 
		}

	}
	else
	{
		yyerror("A variavel \"" + var  + "\" ja foi declada como "+ varCaracteristicas.tipo + " anteriormente");
	}
	return $$;
}

struct atributos declaracaoVariavelGlobal(string var, string tipo){
	struct atributos $$;
	$$.traducao = "";

	caracteristicas varCaracteristicas = buscarVariavelGlobal(var);
	
	if(varCaracteristicas.localVar == ""){
		//cout << "testando1" << endl;
		if(varCaracteristicas.tipo == ""){
			//cout << "testando" << endl;
			//cout << "declarando "<< var << " como " << tipo << endl;
			varCaracteristicas.tipo = tipo;
			varCaracteristicas.localVar = labelUsuario();
			varCaracteristicas.nomeVar = var;
			addVar2Global(pilhaContexto,varCaracteristicas);
			temporarias[varCaracteristicas.localVar] = tipo;
			if(tipo == "int")
				$$.traducao += "\t" + varCaracteristicas.localVar + " = 0;\n";
			else if(tipo == "BOOL")
				$$.traducao += "\t" + varCaracteristicas.localVar + " = False;\n";
			else if(tipo == "float")
				$$.traducao += "\t" + varCaracteristicas.localVar + " = 0.0;\n";
			else if(tipo == "char")
				$$.traducao += "\t" + varCaracteristicas.localVar + " = 'a';\n";
			else if(tipo == "STRING"){
				string labelSize = gerarLabelStringSize(varCaracteristicas.localVar);
				$$.traducao += "\t" + labelSize + " = 1;\n";
				inserirTemporaria(labelSize,"int");
				$$.traducao += "\t" + varCaracteristicas.localVar + " = (STRING) realloc(" + varCaracteristicas.localVar + ", " + labelSize + ");\n";
				$$.traducao += "\t" + varCaracteristicas.localVar + "[0] = \'\\0\';\n";
			}
		}
	}
	else{
		yyerror("A variavel \"" + var  + "\" ja foi declada como "+ varCaracteristicas.tipo + " anteriormente no escopo global");
	}

	return $$;
}

atributos declaracaoVariavelAtribuicaoGlobal(string var, string tipo, atributos expressao){
	atributos $$;
	$$.traducao = "";

	caracteristicas varCaracteristicas = buscarVariavelGlobal(var);
	
	if(varCaracteristicas.localVar == "")
	{
		//cout << "testando1" << endl;
		if(varCaracteristicas.tipo == "")
		{
			//cout << "testando" << endl;
			//cout << "declarando "<< var << " como " << tipo << endl;
			varCaracteristicas.tipo = tipo;
			varCaracteristicas.localVar = labelUsuario();
			varCaracteristicas.nomeVar = var;
			addVar2Global(pilhaContexto,varCaracteristicas);
			temporarias[varCaracteristicas.localVar] = tipo;
			atributos auxiliarVariavel = {var, "" , tipo};
			atributos attr = codigoAtribuicao(auxiliarVariavel,expressao);
			$$.traducao += attr.traducao; 
		}

	}
	else
	{
		yyerror("A variavel global \"" + var  + "\" ja foi declada como "+ varCaracteristicas.tipo + " anteriormente");
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
	$$.tipo = "BOOL";
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
	$$.tipo = "BOOL";
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

caracteristicas buscarVariavelGlobal(string var){
	tabelaVariavel posAtual = pilhaContexto->escopos[0];
	//cout << "buscando variavel " + var << endl;
	if(posAtual.find(var) != posAtual.end()){
		return (posAtual[var]);
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

string gerarLabelStringSize(string label){
	return "SIZE_" + label;
}

int contarTamanhoString(string palavra){
	int cont = 0;
	bool flag = 1;
	//std::cout << "palavra = " + palavra << std::endl;
	// abcd\\1;
	for(int i = 0; i < palavra.size(); i++){
		char c = palavra.at(i);
		//cout << "i = "<< i << endl;
		//cout << "char = " << c <<", flag = " <<flag << endl;
		if(flag)
		{
			if(c != '\\' ){
				//cout << "if 1\n";
				cont++;
			}
			else
			{
				//cout << "else 1\n";
				flag = 0;
			}
		}
		else{
			if(c == 'a' || c == 'b' || c == 'e' || c == 'f' || c == 'n' || c == 'r' \
			 	|| c == 't' || c == 'v' || c == '\\' || c == '\'' || c == '\"' || c == '\?')
			{
				//cout << "if 2\n";
				cont++;
				flag = 1;
			}
			else{
				//cout << "else 2\n";
				yyerror("string com \\ sem caracter de escape adequado" );

			}
		}
		
	}

	return cont;
}

atributos leituraString(caracteristicas variavel){
	atributos $$;
	string label = gerarLabel();
	string gotoLabel = gerarGotoLabel();
	string endGotoLabel = gerarGotoLabel();
	string tamanhoLabel = gerarLabelStringSize(variavel.localVar);
	inserirTemporaria(tamanhoLabel, "int");
	inserirTemporaria(label, "STRING");
	$$.traducao = "\t" + label + " = (STRING) realloc("+ label + ", 2000);\n";
	$$.traducao += "\tstd::cin >>" + label + ";\n";
	$$.traducao += "\t" + tamanhoLabel + " = 0;\n";
	$$.traducao +="\t" + gotoLabel + ":\n";
	string labelTMP1 = gerarLabel();
	string labelTMP2 = gerarLabel();
	inserirTemporaria(labelTMP1, "char");
	inserirTemporaria(labelTMP2, "char");
	atributos a = {labelTMP1,"\t" + labelTMP1 + " = " + label +"[ " + tamanhoLabel + " ];\n", "char"};
	atributos b = {labelTMP2,"\t" + labelTMP2 + " = '\\0';\n", "char" };

	atributos retorno = conversaoImplicita(a,b, "!=");

	$$.traducao += retorno.traducao + "\t" + retorno.label + " = !"+ retorno.label + ";\n";
	$$.traducao += "\tif( " + retorno.label + " ) goto " + endGotoLabel + ";\n";
	$$.traducao += "\t" + tamanhoLabel + " = " + tamanhoLabel + " + 1;\n";
	$$.traducao += "\tgoto " + gotoLabel + ";\n";
	$$.traducao += "\t" + endGotoLabel + ":\n";
	$$.traducao += "\t" + tamanhoLabel + " = " + tamanhoLabel + " + 1;\n";
	$$.traducao += "\t" + variavel.localVar + " = (STRING) realloc("+ variavel.localVar +", " + tamanhoLabel + " );\n";
	$$.traducao += "\tstrcpy( " + variavel.localVar + ", " + label + " );\n";
	$$.traducao += "\tfree( "+ label + ");\n";

	return $$;
}

atributos codigoAtribuicao(atributos $1, atributos $3){
	//cout << " 1.t = " + $1.tipo << " 1.l = " + $1.label << " 3.t = " + $3.tipo <<" 3.l = " + $3.label << "fim impressao";
	atributos $$;
	caracteristicas variavel = buscarVariavel($1.label);
	if(variavel.tipo != "STRING"){
		if(variavel.tipo == $3.tipo){
			$$.traducao = $3.traducao +  "\t" + variavel.localVar + " = " + $3.label + ";\n";
		}
		else
		{
			struct coercao correcao = verificarCoercao(variavel.tipo, "=", $3.tipo);
			if(correcao.retornoTipo != "NULL")
			{
				
				if(variavel.tipo == $3.tipo)
				{
					$$.traducao = $3.traducao +  "\t" + variavel.localVar + " = " + "(" + correcao.conversaoTipo + ")" + $3.label + ";\n";
				}
				else
				{
					yyerror("a operacao = nao esta definida para " + variavel.tipo + " e " + $3.tipo);
				}

			}
		}
	}
	else
	{
		if(variavel.tipo != $3.tipo){
			yyerror("Atribuicao nao esta definida para string e " + $3.tipo);
		}
		else{
			string tamanhoSource = gerarLabelStringSize($3.label), tamanhoDestino = gerarLabelStringSize(variavel.localVar);
			inserirTemporaria(tamanhoDestino, "int");
			$$.traducao += $3.traducao;
			$$.traducao += "\t" + tamanhoDestino + " = " + tamanhoSource + ";\n";
			$$.traducao += "\t" + variavel.localVar + " = (STRING) realloc( "+ variavel.localVar + ", " + tamanhoDestino + ");\n";
			$$.traducao += "\tstrcpy( "+ variavel.localVar  + ", " + $3.label + " );\n";
		}
	}
	return $$;
}

atributos codigoAtribuicaoGlobal(atributos $1, atributos $3){
	//cout << " 1.t = " + $1.tipo << " 1.l = " + $1.label << " 3.t = " + $3.tipo <<" 3.l = " + $3.label << "fim impressao";
	atributos $$;
	caracteristicas variavel = buscarVariavelGlobal($1.label);
	if(variavel.tipo != "STRING"){
		if(variavel.tipo == $3.tipo){
			$$.traducao = $3.traducao +  "\t" + variavel.localVar + " = " + $3.label + ";\n";
		}
		else
		{
			struct coercao correcao = verificarCoercao(variavel.tipo, "=", $3.tipo);
			if(correcao.retornoTipo != "NULL")
			{
				
				if(variavel.tipo == $3.tipo)
				{
					$$.traducao = $3.traducao +  "\t" + variavel.localVar + " = " + "(" + correcao.conversaoTipo + ")" + $3.label + ";\n";
				}
				else
				{
					yyerror("a operacao = nao esta definida para " + variavel.tipo + " e " + $3.tipo);
				}

			}
		}
	}
	else
	{
		if(variavel.tipo != $3.tipo){
			yyerror("Atribuicao nao esta definida para string e " + $3.tipo);
		}
		else{
			string tamanhoSource = gerarLabelStringSize($3.label), tamanhoDestino = gerarLabelStringSize(variavel.localVar);
			inserirTemporaria(tamanhoDestino, "int");
			$$.traducao += $3.traducao;
			$$.traducao += "\t" + tamanhoDestino + " = " + tamanhoSource + ";\n";
			$$.traducao += "\t" + variavel.localVar + " = (STRING) realloc( "+ variavel.localVar + ", " + tamanhoDestino + ");\n";
			$$.traducao += "\tstrcpy( "+ variavel.localVar  + ", " + $3.label + " );\n";
		}
	}
	return $$;
}

atributos converterStringInteiro(atributos variavel){
	atributos $$;
	string tmpI = gerarLabel();
	inserirTemporaria(tmpI , "int");
	$$.traducao = "\t" + tmpI + " = 0;\n";
	string chartmp = gerarLabel();
	inserirTemporaria(chartmp, "char");
	$$.traducao += "\t" + chartmp + " = " + variavel.label + "[0]\n";

	string minus = gerarLabel();
	inserirTemporaria(minus, "BOOL");
	$$.traducao += "\t" + minus + " = False;\n";

	string numero = gerarLabel();
	inserirTemporaria(numero, "int");
	$$.traducao += "\t" + numero + " = 0;\n";

	string labelInicio = gerarGotoLabel();
	$$.traducao += "\t" + labelInicio + ":\n";

	string labelFim = gerarGotoLabel();

	string tmpBarra0 = gerarLabel();
	inserirTemporaria(tmpBarra0, "char");
	$$.traducao += "\t" + tmpBarra0 + " = '\0';\n";

	string tmpComparacaoWhile = gerarLabel();
	inserirTemporaria(tmpComparacaoWhile, "BOOL");
	$$.traducao += "\t" + tmpComparacaoWhile + " = " + chartmp + " != " + tmpBarra0 + ";\n";
	$$.traducao += "\t" + tmpComparacaoWhile + " = !" + tmpComparacaoWhile + ";\n";

	$$.traducao += "\tif(" + tmpComparacaoWhile + ") goto " + labelFim + ";\n";

	string tmpIigual0 = gerarLabel();
	inserirTemporaria(tmpIigual0, "int");
	$$.traducao += "\t" + tmpIigual0 + " = 0;\n";

	string comparacaoI = gerarLabel();
	inserirTemporaria(comparacaoI, "BOOL");
	$$.traducao += "\t" + comparacaoI+ " = " + tmpI + " == " + tmpIigual0 + ";\n";

	string charMenos = gerarLabel();
	inserirTemporaria(charMenos, "char");
	$$.traducao += "\t" + charMenos + " = '-';\n";

	string comparacaoMenos = gerarLabel();
	inserirTemporaria (comparacaoMenos, "BOOL");
	$$.traducao += "\t" + comparacaoMenos + " = " + chartmp + " == "+ charMenos + ";\n";

	string comparacaoIf1 = gerarLabel();
	inserirTemporaria(comparacaoIf1, "BOOL");
	$$.traducao += "\t" + comparacaoIf1 + " = " + comparacaoI + " && " + comparacaoMenos + ";\n"; 










	return $$;

	
	
}



