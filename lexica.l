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
"bool"		{return TK_TIPO_BOOL;}


[(){}[\];:,\']	{ return *yytext; }

[+\-*/=%]	{ return *yytext; }

[<>]		{return *yytext; }

"!="		{return TK_NOT_EQ;}
">="		{return TK_BIG_EQ;}
"<="		{return TK_SMALL_EQ;}
"=="		{return TK_EQ;}

"and"		{return TK_AND;}
"or"		{return TK_OR;}
"not"		{return TK_NOT;}

"True"		{yylval.traducao = "1"; return TK_LOGICO;}

"False"		{yylval.traducao = "0"; return TK_LOGICO;}

"print"		{return TK_PRINT;}
"if"		{return TK_IF;}
"else"		{return TK_ELSE;}
"while"		{return TK_WHILE;}
"for"		{return TK_FOR;}
"switch"	{return TK_SWITCH;}
"case"		{return TK_CASE;}
"taylor"	{return TK_DEFAULT;}
"break"		{return TK_BREAK;}
"continue"	{return TK_CONTINUE;}


{NUM}		{yylval.traducao = yytext; return TK_NUM; }
{REAL}		{yylval.traducao = yytext; return TK_REAL;}
{CHAR}		{yylval.traducao = yytext; return TK_CHAR;}


{ID}		{ yylval.label = yytext; return TK_ID;}

.			{*yytext; }


%%
