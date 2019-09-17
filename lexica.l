%{
#include <string>


%}

ESPACO [ \t]
DIGITO [0-9]
LETRA [A-Za-z_]

DELIM {ESPACO}+
NUM {DIGITO}+
REAL {NUM}+("."{NUM}+)?
CHAR \'({LETRA}|{NUM})\'
ID {LETRA}({LETRA}|{NUM})*

%%

"\n"		{lineCount += 1;}

{DELIM} 	{}

"main"		{return TK_MAIN;}

"int"		{return TK_TIPO_INT;}
"float"		{return TK_TIPO_FLOAT;}
"char"		{return TK_TIPO_CHAR;}

[(){}[\];,]	{ return *yytext; }

[+\-*/=]	{ return *yytext; }

[<>]		{return *yytext; }

"!="		{return TK_NOT_EQ;}
">="		{return TK_BIG_EQ;}
"<="		{return TK_SMALL_EQ;}
"=="		{return TK_EQ;}

{NUM}		{yylval.traducao = yytext; return TK_NUM; }
{REAL}		{yylval.traducao = yytext; return TK_REAL;}
{CHAR}		{yylval.traducao = yytext; return TK_CHAR;}
{ID}		{
				if ( tabela.find(yytext) != tabela.end() )
				{
					yylval.label = (tabela[yytext].localVar);
					
					
				}
				else{

					inserirTabela(yytext);
					yylval.label = tabela[yytext].localVar;
				}


				return TK_ID; 
				
	}

.			{*yytext; }


%%
