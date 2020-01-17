%{
    //C includes
    #include <stdio.h>
  #include <stack>

    //Custom includes
    #include "j_token.h"
    #include "node.h"
  #include "program_node.h"
  #include "dec_node.h"
  #include "event_node.h"
  #include "stm_node.h"
  #include "type_node.h"
  #include "exp_node.h"
  #include "assign_node.h"
  #include "conditional_node.h"
  #include "variable_node.h"
  #include "variable_ex_node.h"
  #include "int_node.h"

    #ifdef CPLUSPLUS
    extern int yylex();
    extern FILE* yyin;
    extern char* yytext;
    extern int yydebug;

    extern int lineNo;
    #endif
    void yyerror( const char *msg )
    {
        printf("ERROR Value: %s detected on line %d.\n", msg, lineNo );
    }
    int yywrap()
    {
        return 1;
    }

      //Holds my entire program
    ProgramNode* ParseTree = new ProgramNode();
%}

%union {
    Node * nodeInfo;
    JToken * tokInfo;
}

//Token list
%token <tokInfo> FUNC CLASS
%token <tokInfo> IF ELSE RETURN WHILE BREAK
%token <tokInfo> IDENT NUMBER F32 I32 VAR DOT VAR_EX
%token <tokInfo> MUL DIV MOD AND
%token <tokInfo> ADD SUBT OR
%token <tokInfo> GEQ NEQ LEQ GREAT LESS EQ NOT ASSIGN ASSIGN_CONST
%token <tokInfo> ERROR


%type <nodeInfo> program
%type <nodeInfo> declist
%type <nodeInfo> decl
%type <nodeInfo> vardec
%type <nodeInfo> fundec
%type <nodeInfo> compound
%type <nodeInfo> locvdecs
%type <nodeInfo> stmtlst
%type <nodeInfo> stmt
%type <nodeInfo> noncond
%type <nodeInfo> expression
%type <nodeInfo> var
%type <nodeInfo> simpexp
%type <nodeInfo> logop
%type <nodeInfo> relexp
%type <nodeInfo> relop
%type <nodeInfo> addexp
%type <nodeInfo> addop
%type <nodeInfo> term
%type <nodeInfo> mulop
%type <nodeInfo> unary
%type <nodeInfo> unaryop
%type <nodeInfo> fact
%type <nodeInfo> constant
%type <nodeInfo> brkstmt
%type <nodeInfo> retstmt
%type <nodeInfo> type_assign

%%
// Productions
program     :   declist
                { ParseTree->setSibling( $1 ); }
            ;

// Collection of delcarations
declist     :   decl declist
                { $1->setSibling($2); }

            |   decl
                { $$ = $1; }
            ;

// Declaration of class, functions etc
decl        :   vardec
                { $$ = $1; }

            |   fundec
                { $$ = $1; }
            ;

// Declare variables
vardec      :   VAR IDENT ';'
                {
                    $$ = new DecNode( IDENT, lineNo, $2->stringValue );
                }

            |   type_assign IDENT ';'
                {
                    $$ = new DecNode(IDENT, lineNo, $2->stringValue );
                    $$->setChild( 0, $1 );
                }
            ;

fundec      :   FN '(' expression ')' compound
                {
                    $$ = new EventNode( FN, $3->getLineNo() );
                    $$->setChild(0, $3);
                    $$->setChild(1, $5);
                }

            |   PRE_EVENT '(' expression ')' compound
				{
                	$$ = new EventNode( PRE_EVENT, $3->getLineNo() );
                    $$->setChild(0, $3);
                    $$->setChild(1, $5);
                }

            |   POST_EVENT '(' expression ')' compound
				{
                	$$ = new EventNode( POST_EVENT, $3->getLineNo() );
                    $$->setChild(0, $3);
                    $$->setChild(1, $5);
                }

            |   INIT '(' ')' compound
				{
                  	$$ = new EventNode( INIT, $1->line );
                    $$->setChild(1, $4);
                }
            ;

compound    :   STARTCURLY locvdecs stmtlst '}'
				{
                    $$ = new StmNode( STARTCURLY, $1->line, "Compound" );
                    $$->setChild(0, $2);
                    $$->setChild(1, $3);
                }

            |   STARTCURLY locvdecs '}'
				{
                    $$ = new StmNode( STARTCURLY, $1->line, "Compound" );
                    $$->setChild(0, $2);
                }

            |   STARTCURLY stmtlst  '}'
				{
                    $$ = new StmNode( STARTCURLY, $1->line, "Compound" );
                    $$->setChild(1, $2);
                }

            |   STARTCURLY '}'
				{
                    $$ = new StmNode( STARTCURLY, $1->line, "Compound" );
                }
            ;

locvdecs    :   vardec locvdecs
				{ $1->setSibling($2); }

            |   vardec
				{ $$ = $1; }
            ;

stmtlst     :   stmt stmtlst
				{
                  	if ($1 != NULL)
                      	$1->setSibling($2);
                  	else
                      	$$ = $2;

                }

            |   stmt
				{ $$ = $1; }
            ;

stmt        :   IF '(' expression ')' stmt ELSE stmt
				{
                    $$ = new ConditionalNode( IF, $1->line, "If" );
                    $$->setChild(0, $3);
                    $$->setChild(1, $5);
                    $$->setChild(2, $7);
                }

            |   WHILE '(' expression ')' stmt
				{
                    $$ = new ConditionalNode( WHILE, $1->line, "While" );
                    $$->setChild(0, $3);
                    $$->setChild(1, $5);
                }

            |   noncond
				{ $$ = $1; }
            ;

noncond     :   brkstmt
				{ $$ = $1; }

            |   retstmt
				{ $$ = $1; }

            |   compound
				{ $$ = $1; }

            |   expression ';'
				{ $$ = $1; }

            |   ';'
				{
                    $$ = new StmNode( 0, lineNo, "Empty" );
                }
            ;

expression  :   var ASSIGN expression
				{
                    //If we are loading a constant, set that we are
                    int id = ASSIGN;
                    if ( $3->getTokenType() == NUMBER )
                      id = ASSIGN_CONST;

                      //Create my node
                    $$ = new AssignNode( id, $1->getLineNo(), $2->stringValue, "Assign: " );
                    $$->setChild(0, $1);
                    $$->setChild(1, $3);
                }

            |   var ASSIGN '(' type_assign ')' expression
				{
                  	//If we are loading a constant, set that we are
                    int id = ASSIGN;
                    if ( $6->getTokenType() == NUMBER )
                      id = ASSIGN_CONST;

                      //Create my node
                    $$ = new AssignNode( id, $1->getLineNo(), $2->stringValue, "Assign Int: " );
                    $$->setChild(0, $1);
                    $$->setChild(1, $6);
                    $$->setChild(2, $4);
                }

            |   simpexp
				{ $$ = $1; }
            ;

type_assign :   INT
				{
                  	$$ = new TypeNode( INT, $1->line, "int", "Type: " );
                }

            |   FLOAT
				{
                  	$$ = new TypeNode( FLOAT, $1->line, "float", "Type: " );
                }
            ;

var         :   IDENT
				{
                    $$ = new VariableNode( IDENT, $1->line, $1->stringValue );
                }

            |   var DOT IDENT
				{
                    //Convert my variable node, to a VariableExNode
                  	if ( $1->getTokenType() != VAR_EX )
                  	{
                    	$$ = new VariableExNode( VAR_EX,
                                             $1->getLineNo() );
                    	reinterpret_cast<VariableExNode*>($$)->addVariable(
                          reinterpret_cast<VariableNode*>($1) );
                  	}

                    //Add a new variable
                  	reinterpret_cast<VariableExNode*>($$)->addVariable(
                                   new VariableNode( IDENT,
                                      $3->line,//line number
                                      $3->stringValue//label
                                    ) );
                }
            ;

simpexp     :   simpexp logop relexp
				{
                    $$ = $2;
                    $$->setChild(0, $1);
                    $$->setChild(1, $3);
                }

            |   relexp
				{ $$ = $1; }
            ;

relexp      :   addexp relop addexp
				{
                    $$ = $2;
                    $$->setChild(0, $1);
                    $$->setChild(1, $3);
                }

            |   addexp
				{ $$ = $1; }
            ;

relop       :   LEQ
				{
                    $$ = new ExpNode( LEQ, lineNo, $1->stringValue, "Op: " );
                }

            |   LESS
				{
                    $$ = new ExpNode( LESS, lineNo, $1->stringValue, "Op: " );
                }

            |   GREAT
				{
                    $$ = new ExpNode( GREAT, lineNo, $1->stringValue, "Op: " );
                }

            |   GEQ
				{
                    $$ = new ExpNode( GEQ, lineNo, $1->stringValue, "Op: " );
                }

            |   EQ
				{
                    $$ = new ExpNode( EQ, lineNo, $1->stringValue, "Op: " );
                }

            |   NEQ
				{
                    $$ = new ExpNode( NEQ, lineNo, $1->stringValue, "Op: " );
                }
            ;

addexp      :   addexp addop term
				{
                    $$ = $2;
                    $$->setChild(0, $1);
                    $$->setChild(1, $3);
                }

            |   term
				{ $$ = $1; }
            ;

addop       :   ADD
				{
                    $$ = new ExpNode( ADD, lineNo, $1->stringValue, "Op: " );
                }

            |   SUBT
				{
                    $$ = new ExpNode( SUBT, lineNo, $1->stringValue, "Op: " );
                }
            ;

logop       :   OR
				{
                    $$ = new ExpNode( OR, lineNo, $1->stringValue, "Op: " );
                }

            |   AND
				{
                    $$ = new ExpNode( AND, lineNo, $1->stringValue, "Op: " );
                }
            ;

term        :   term mulop unary
				{
                    $$ = $2;
                    $$->setChild(0, $1);
                    $$->setChild(1, $3);
                }

            |   unary
				{ $$ = $1; }
            ;

mulop       :   MUL
				{
                    $$ = new ExpNode( MUL, lineNo, $1->stringValue, "Op: " );
                }

            |   DIV
				{
                    $$ = new ExpNode( DIV, lineNo, $1->stringValue, "Op: " );
                }

            |   MOD
				{
                    $$ = new ExpNode( MOD, lineNo, $1->stringValue, "Op: " );
                }

            |   NOT
				{
                    $$ = new ExpNode( NOT, lineNo, $1->stringValue, "Op: " );
                }
            ;

unary       :   unaryop unary
				{ $1->setChild(0,$2); }

            |   fact
				{ $$ = $1; }
            ;

unaryop     :   NOT
				{
                    $$ = new ExpNode( NOT, lineNo, $1->stringValue, "Op: " );
                }

            |   SUBT
				{
                    $$ = new ExpNode( SUBT, lineNo, $1->stringValue, "Op: " );
                }
            ;

fact        :   '(' expression ')'
				{ $$ = $2; }

            |   var
				{ $$ = $1; }

            |   constant
				{ $$ = $1; }
            ;

constant    :   NUMBER
				{
                    $$ = new IntNode( NUMBER, lineNo, $1->stringValue, $1->numericValue, "Const: " );
                }
            ;

brkstmt     :   BREAK ';'
				{
                    $$ = new StmNode( BREAK, $1->line, "Break" );
                }
            ;

retstmt     :   RETURN ';'
				{
                    $$ = new StmNode( RETURN, $1->line, "Return" );
                }
            ;
%%

#include "main.c"
