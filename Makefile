DEFINE = -DCPLUSPLUS
COMP_OPTS = -std=c++14
LIBRARIES = -lm
INCLUDES = -Ihepers -I.

BISON_OPTS = -v -t -d

OBJECTS = build/node.o \
					build/error.o \
          build/program_node.o \
          build/getopt.o \
          build/parser.tab.o \
					build/helpers/util.o \
					build/helpers/token.o

COMP = g++

EXECUTABLE = c--

$(EXECUTABLE):	 flex bison $(OBJECTS)
		$(COMP) $(DEFINE) $(COMP_OPTS) lex.yy.c build/*.o $(LIBRARIES) -o $(EXECUTABLE)

flex:	scanner.lex
	flex $(FLEX_OPTS) scanner.lex

bison:	parser.y
	bison $(BISON_OPTS) parser.y

build/%.o:	%.cpp %.h
	$(COMP) $(DEFINE) $(COMP_OPTS) $(INCLUDES) -c $*.cpp -o build/$*.o

build/helpers/%.o:	helpers/%.cpp helpers/%.h
	$(COMP) $(DEFINE) $(COMP_OPTS) $(INCLUDES) -c helpers/$*.cpp -o build/$*.o

build/parser.tab.o:	parser.tab.c parser.tab.h
	$(COMP) $(DEFINE) $(COMP_OPTS) $(INCLUDES) -c parser.tab.c -o build/parser.tab.o

clean:
	-rm -f scanner.output scanner.tab.c parser.tab.h lex.yy.c build/*
	-rm -f $(EXECUTABLE)
