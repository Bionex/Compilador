all:
		@reset
		@lex lexica.l
		@yacc -t -d sintatica.y -v -Wconflicts-sr
		@g++ -o glf y.tab.c src/loop.c src/escopo.c src/main.c -ll -std=c++11 -DYYDEBUG

		@./glf < exemplo.foca 2> debug.cpp | tee test.cpp

		@rm y.tab.c y.tab.h lex.yy.c

testar:
		@reset

		@./glf < exemplo.foca 2> debug.cpp | tee test.cpp
		@g++ test.cpp -o test
		@echo "\nExecutando o codigo intermediario\n"
		@./test | tee result.txt


no-build:
		@./glf < exemplo.foca 2> debug.cpp | tee test.cpp