all:
		@clear
		@lex lexica.l
		@yacc -t -d sintatica.y
		@g++ -o glf y.tab.c -ll -std=c++11 -DYYDEBUG

		@./glf < exemplo.foca 2> debug.cpp | tee test.cpp

		@rm y.tab.c y.tab.h lex.yy.c glf