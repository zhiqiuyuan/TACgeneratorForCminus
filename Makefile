default:
	bison -d syntax_analyzer.y
	flex lexical_analyzer.l
	g++ -g -std=c++11 syntax_tree.cpp TACnode.cpp lex.yy.c syntax_analyzer.tab.c main.cpp -o main

clean:
	rm lex.yy.c syntax_analyzer.tab.c syntax_analyzer.tab.h
