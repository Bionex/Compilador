Starting parse
Entering state 0
Reading a token: Next token is token TK_TIPO_INT ()
Shifting token TK_TIPO_INT ()
Entering state 1
Reading a token: Next token is token TK_MAIN ()
Shifting token TK_MAIN ()
Entering state 3
Reading a token: Next token is token '(' ()
Shifting token '(' ()
Entering state 5
Reading a token: Next token is token ')' ()
Shifting token ')' ()
Entering state 6
Reading a token: Next token is token '{' ()
Shifting token '{' ()
Entering state 7
Reading a token: Next token is token TK_NUM ()
Shifting token TK_NUM ()
Entering state 9
Reducing stack by rule 26 (line 227):
   $1 = token TK_NUM ()
-> $$ = nterm E ()
Stack now 0 1 3 5 6 7
Entering state 22
Reading a token: Next token is token TK_NOT_EQ ()
Shifting token TK_NOT_EQ ()
Entering state 34
Reading a token: Next token is token TK_NUM ()
Shifting token TK_NUM ()
Entering state 9
Reducing stack by rule 26 (line 227):
   $1 = token TK_NUM ()
-> $$ = nterm E ()
Stack now 0 1 3 5 6 7 22 34
Entering state 50
Reading a token: Next token is token ';' ()
Reducing stack by rule 25 (line 219):
   $1 = nterm E ()
   $2 = token TK_NOT_EQ ()
   $3 = nterm E ()
-> $$ = nterm E ()
Stack now 0 1 3 5 6 7
Entering state 22
Next token is token ';' ()
Shifting token ';' ()
Entering state 45
Reducing stack by rule 5 (line 112):
   $1 = nterm E ()
   $2 = token ';' ()
-> $$ = nterm COMANDO ()
Stack now 0 1 3 5 6 7
Entering state 19
Reading a token: Next token is token '}' ()
Reducing stack by rule 4 (line 109):
-> $$ = nterm COMANDOS ()
Stack now 0 1 3 5 6 7 19
Entering state 30
Reducing stack by rule 3 (line 108):
   $1 = nterm COMANDO ()
   $2 = nterm COMANDOS ()
-> $$ = nterm COMANDOS ()
Stack now 0 1 3 5 6 7
Entering state 18
Next token is token '}' ()
Shifting token '}' ()
Entering state 29
Reducing stack by rule 2 (line 102):
   $1 = token '{' ()
   $2 = nterm COMANDOS ()
   $3 = token '}' ()
-> $$ = nterm BLOCO ()
Stack now 0 1 3 5 6
Entering state 8
Reducing stack by rule 1 (line 96):
   $1 = token TK_TIPO_INT ()
   $2 = token TK_MAIN ()
   $3 = token '(' ()
   $4 = token ')' ()
   $5 = nterm BLOCO ()
-> $$ = nterm S ()
Stack now 0
Entering state 2
Reading a token: Now at end of input.
Shifting token $end ()
Entering state 4
Stack now 0 2 4
Cleanup: popping token $end ()
Cleanup: popping nterm S ()
