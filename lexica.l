%{
#include <string>


%}

ESPACO [ \t]
DIGITO [0-9]
LETRA [A-Za-z_]
CARACTER_ESCAPE \\(t|0|n|r|e|a|b|f|v|\\|\'|\"|\?)


DELIM {ESPACO}+
NUM {DIGITO}+
REAL {NUM}+("."{NUM}+)?
CHAR \'({LETRA}|{NUM}|{CARACTER_ESCAPE}|"-"|"+")\'
ID {LETRA}({LETRA}|{NUM})*
ESCAPE {CARACTER_ESCAPE}

%x SINGLE_STRING

%%

\"                          BEGIN(SINGLE_STRING);
<SINGLE_STRING>{
  \n                        yyerror("the string misses \" to termiate before newline");
  <<EOF>>                   yyerror("the string misses \" to terminate before EOF");
  ([^\\\"]|\\.)*            {yylval.traducao = yytext; return TK_STRING;}
  \"                        BEGIN(INITIAL);
  .                         ;
}


"\n"		{lineCount += 1;}

{DELIM} 	{}

"main"		{return TK_MAIN;}

"int"		{return TK_TIPO_INT;}
"float"		{return TK_TIPO_FLOAT;}
"char"		{return TK_TIPO_CHAR;}
"bool"		{return TK_TIPO_BOOL;}
"string"    {return TK_TIPO_STRING;}


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

"True"		{yylval.traducao = "True"; return TK_LOGICO;}

"False"		{yylval.traducao = "False"; return TK_LOGICO;}

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
"all"       {return TK_ALL;}
"do"		{return TK_DO;}
"scan"      {return TK_SCAN;}

{NUM}		{yylval.traducao = yytext; return TK_NUM; }
{REAL}		{yylval.traducao = yytext; return TK_REAL;}
{CHAR}		{yylval.traducao = yytext; return TK_CHAR;}


{ID}		{ yylval.label = yytext; return TK_ID;}

.			{*yytext; }


%%
