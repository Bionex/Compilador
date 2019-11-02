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
Reducing stack by rule 3 (line 140):
-> $$ = nterm BLOCO_AUX ()
Stack now 0 1 3 5 6
Entering state 8
Reading a token: Next token is token '{' ()
Shifting token '{' ()
Entering state 9
Reading a token: Next token is token TK_TIPO_INT ()
Shifting token TK_TIPO_INT ()
Entering state 15
Reading a token: Next token is token TK_ID ()
Shifting token TK_ID ()
Entering state 36
Reading a token: Next token is token ';' ()
Reducing stack by rule 29 (line 271):
   $1 = token TK_TIPO_INT ()
   $2 = token TK_ID ()
-> $$ = nterm DECLARACAO ()
Stack now 0 1 3 5 6 8 9
Entering state 32
Next token is token ';' ()
Shifting token ';' ()
Entering state 54
Reducing stack by rule 8 (line 153):
   $1 = nterm DECLARACAO ()
   $2 = token ';' ()
-> $$ = nterm COMANDO ()
Stack now 0 1 3 5 6 8 9
Entering state 27
Reading a token: Next token is token TK_TIPO_INT ()
Shifting token TK_TIPO_INT ()
Entering state 15
Reading a token: Next token is token TK_ID ()
Shifting token TK_ID ()
Entering state 36
Reading a token: Next token is token ';' ()
Reducing stack by rule 29 (line 271):
   $1 = token TK_TIPO_INT ()
   $2 = token TK_ID ()
-> $$ = nterm DECLARACAO ()
Stack now 0 1 3 5 6 8 9 27
Entering state 32
Next token is token ';' ()
Shifting token ';' ()
Entering state 54
Reducing stack by rule 8 (line 153):
   $1 = nterm DECLARACAO ()
   $2 = token ';' ()
-> $$ = nterm COMANDO ()
Stack now 0 1 3 5 6 8 9 27
Entering state 27
Reading a token: Next token is token TK_ID ()
Shifting token TK_ID ()
Entering state 13
Reading a token: Next token is token '+' ()
Reducing stack by rule 53 (line 402):
   $1 = token TK_ID ()
-> $$ = nterm E ()
Stack now 0 1 3 5 6 8 9 27 27
Entering state 33
Next token is token '+' ()
Shifting token '+' ()
Entering state 64
Reading a token: Next token is token TK_NUM ()
Shifting token TK_NUM ()
Entering state 10
Reducing stack by rule 50 (line 381):
   $1 = token TK_NUM ()
-> $$ = nterm E ()
Stack now 0 1 3 5 6 8 9 27 27 33 64
Entering state 88
Reading a token: Next token is token ';' ()
Reducing stack by rule 34 (line 303):
   $1 = nterm E ()
   $2 = token '+' ()
   $3 = nterm E ()
