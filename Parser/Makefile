BISON_OPTS = -v -t -d

all:	 lex.yy.c parser.tab.c

lex.yy.c:	scanner.lex
	flex $(FLEX_OPTS) scanner.lex

parser.tab.c:	parser.y
	bison $(BISON_OPTS) parser.y

clean:
	rm -f parser.output parser.tab.c parser.tab.h lex.yy.c
