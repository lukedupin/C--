
DEFINE = -DCPLUSPLUS
COMP_OPTS = -m32
LIBRARIES = -lm

BISON_OPTS = -v -t -d

OBJECTS = build/node.o \
          build/dec_node.o \
          build/program_node.o \
          build/event_node.o \
          build/stm_node.o \
          build/type_node.o \
          build/int_node.o \
          build/exp_node.o \
          build/assign_node.o \
          build/conditional_node.o \
          build/variable_node.o \
          build/variable_ex_node.o \
          build/getopt.o \
          build/parser.tab.o

COMP = g++

EXECUTABLE = c--

$(EXECUTABLE):	 flex bison $(OBJECTS)
		$(COMP) $(DEFINE) $(COMP_OPTS) lex.yy.c $(OBJECTS) $(LIBRARIES) -o $(EXECUTABLE)

flex:	scanner.lex
	flex $(FLEX_OPTS) scanner.lex

bison:	parser.y
	bison $(BISON_OPTS) parser.y

build/%.o:	%.cpp %.h
	$(COMP) $(DEFINE) $(COMP_OPTS) -c $*.cpp -o build/$*.o

build/parser.tab.o:	parser.tab.c parser.tab.h
	$(COMP) $(DEFINE) $(COMP_OPTS) -c parser.tab.c -o build/parser.tab.o

clean:
	-rm -f scanner.output scanner.tab.c parser.tab.h lex.yy.c build/*
	-rm -f $(EXECUTABLE)
