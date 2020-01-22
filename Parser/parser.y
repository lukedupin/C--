%{
    //C includes
    #include <stdio.h>
    #include <stack>

    //Custom includes
    #include "lex_token.h"
    #include <node.h>
    #include <program_node.h>

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

%define parse.error verbose

%union {
    Node * nodeInfo;
    LexToken * tokInfo;
}

//Token list
%token <tokInfo> LEFT_CURLY
%token <tokInfo> RIGHT_CURLY
%token <tokInfo> IF
%token <tokInfo> ELIF
%token <tokInfo> ELSE
%token <tokInfo> LET
%token <tokInfo> IN
%token <tokInfo> FN
%token <tokInfo> CLASS
%token <tokInfo> RETURN
%token <tokInfo> WHILE
%token <tokInfo> SWITCH
%token <tokInfo> MATCH
%token <tokInfo> CASE
%token <tokInfo> DEFAULT
%token <tokInfo> DO
%token <tokInfo> BREAK
%token <tokInfo> CONTINUE
%token <tokInfo> FIRST
%token <tokInfo> LAST
%token <tokInfo> FALSE
%token <tokInfo> TRUE
%token <tokInfo> ADD_ASSIGN
%token <tokInfo> SUB_ASSIGN
%token <tokInfo> MUL_ASSIGN
%token <tokInfo> DIV_ASSIGN
%token <tokInfo> MUL
%token <tokInfo> DIV
%token <tokInfo> MOD
%token <tokInfo> ADD
%token <tokInfo> SUB
%token <tokInfo> ARROW_RIGHT
%token <tokInfo> AND
%token <tokInfo> OR
%token <tokInfo> NEQ
%token <tokInfo> LEQ
%token <tokInfo> GEQ
%token <tokInfo> EQ
%token <tokInfo> GT
%token <tokInfo> LT
%token <tokInfo> NOT
%token <tokInfo> ASSIGN
%token <tokInfo> DOT
%token <tokInfo> I8
%token <tokInfo> I16
%token <tokInfo> I32
%token <tokInfo> I64
%token <tokInfo> I128
%token <tokInfo> U8
%token <tokInfo> U16
%token <tokInfo> U32
%token <tokInfo> U64
%token <tokInfo> U128
%token <tokInfo> F32
%token <tokInfo> F64
%token <tokInfo> STR
%token <tokInfo> VEC
%token <tokInfo> HASH
%token <tokInfo> IDENT
%token <tokInfo> NUMBER
%token <tokInfo> STRING_DBL
%token <tokInfo> STRING_TICK
%token <tokInfo> ERROR

//Setup the symbol tree
%type <nodeInfo> program
%type <nodeInfo> declist
%type <nodeInfo> decl
%type <nodeInfo> var_dec
%type <nodeInfo> fn_dec
%type <nodeInfo> param_list
%type <nodeInfo> param
%type <nodeInfo> class_dec
%type <nodeInfo> block
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
%type <nodeInfo> str_form
%type <nodeInfo> str_params
%type <nodeInfo> str_literal
%type <nodeInfo> brkstmt
%type <nodeInfo> retstmt
%type <tokInfo> primative_type

%%
// Productions
program     :   declist
                { ParseTree->Sibling =  $1; }
            ;

// Collection of delcarations
declist     :   decl declist
                { $1->Sibling = $2; }

            |   decl
                { $$ = $1; }
            ;

// Declaration of class, functions etc
decl        :   var_dec
                { $$ = $1; }
            |   fn_dec
                { $$ = $1; }
            ;

// Declare variables
var_dec      :  LET IDENT ASSIGN expression ';'
                {
                    $$ = new Node( IDENT, $IDENT->line, $IDENT->stringValue );
                    $$->Children.push_back( $expression );
                }
            ;

fn_dec      :   FN IDENT '(' ')' block
                {
                    $$ = new Node( FN, $IDENT->line, $IDENT->stringValue );
                    //$$->Children.push_back( $4 );
                    $$->Children.push_back( $block );
                }
            |   FN IDENT '(' ')' ARROW_RIGHT primative_type block
                {
                    $$ = new Node( FN, $2->line, $2->stringValue );
                    $$->Children.push_back( $block);
                }
            |   FN IDENT '(' ')' ARROW_RIGHT IDENT block
                {
                    $$ = new Node( FN, $2->line, $2->stringValue );
                    $$->Children.push_back( $block);
                }
            |   FN IDENT '(' ')' ARROW_RIGHT '(' param_list ')' block
                {
                    $$ = new Node( FN, $2->line, $2->stringValue );
                    $block->Children.push_front( $7 );
                    $$->Children.push_back( $block);
                }

            |   FN IDENT '(' param_list ')' block
                {
                    $$ = new Node( FN, $IDENT->line, $IDENT->stringValue );
                    $block->Children.push_front( $4 );
                    $$->Children.push_back( $block );
                }
            |   FN IDENT '(' param_list ')' ARROW_RIGHT primative_type block
                {
                    $$ = new Node( FN, $2->line, $2->stringValue );
                    $block->Children.push_front( $4 );
                    $$->Children.push_back( $block);
                }
            |   FN IDENT '(' param_list ')' ARROW_RIGHT IDENT block
                {
                    $$ = new Node( FN, $2->line, $2->stringValue );
                    $block->Children.push_front( $4 );
                    $$->Children.push_back( $block);
                }
            |   FN IDENT '(' param_list ')' ARROW_RIGHT '(' param_list ')' block
                {
                    $$ = new Node( FN, $2->line, $2->stringValue );
                    $block->Children.push_front( $8 );
                    $block->Children.push_front( $4 );
                    $$->Children.push_back( $block);
                }
            ;

param_list  :   param ',' param_list
                {
                  $1->Sibling = $3;
                }
            |   param
                {
                  $$ = $1;
                }
            ;

param       :   IDENT ':' primative_type
                {
                    $$ = new Node( $3->code, $1->line, $1->stringValue );
                }
            |   IDENT ':' IDENT
                {
                    $$ = new Node( $3->code, $1->line, $1->stringValue );
                }
            ;

block    :   LEFT_CURLY stmtlst  RIGHT_CURLY
                {
                    $$ = new Node( LEFT_CURLY, $1->line );
                    $$->Children.push_back( $2);
                }

            |   LEFT_CURLY RIGHT_CURLY
                {
                    $$ = new Node( LEFT_CURLY, $1->line );
                }
            ;

stmtlst     :   stmt stmtlst
                {
                      if ($1 != NULL)
                          $1->Sibling = $2;
                      else
                          $$ = $2;
                }

            |   stmt
                { $$ = $1; }
            ;

stmt        :   IF '(' expression ')' block
                {
                    $$ = new Node( $1->code, $1->line, $1->stringValue );
                    $$->Children.push_back( $3);
                    $$->Children.push_back( $5);
                }

            |   ELIF '(' expression ')' block
                {
                    $$ = new Node( $1->code, $1->line, $1->stringValue );
                    $$->Children.push_back( $expression);
                    $$->Children.push_back( $block );
                }

            |   ELSE block
                {
                    $$ = new Node( $1->code, $1->line, $1->stringValue );
                    $$->Children.push_back( $block );
                }

            |   WHILE '(' expression ')' block
                {
                    $$ = new Node( $1->code, $1->line, $1->stringValue );
                    $$->Children.push_back( $3);
                    $$->Children.push_back( $5);
                }

                FOREACH '(' IDENT IN expression ')' block
                {
                    $$ = new Node( $1->code, $1->line, $1->stringValue );
                    $$->Children.push_back( $3);
                    $$->Children.push_back( $5);
                }

            |   DO '(' expression ')' block
                {
                    $$ = new Node( $1->code, $1->line, $1->stringValue );
                    $$->Children.push_back( $3);
                    $$->Children.push_back( $5);
                }

            |   SWITCH '(' expression ')' switch_block
                {
                    $$ = new Node( $1->code, $1->line, $1->stringValue );
                    $$->Children.push_back( $3);
                    $$->Children.push_back( $5);
                }

            |   MATCH '(' expression ')' match_block
                {
                    $$ = new Node( $1->code, $1->line, $1->stringValue );
                    $$->Children.push_back( $3);
                    $$->Children.push_back( $5);
                }

            |   var_dec
                { $$ = $1; }

            |   noncond
                { $$ = $1; }
            ;

noncond     :   brkstmt
                { $$ = $1; }

            |   retstmt
                { $$ = $1; }

            |   block
                { $$ = $1; }

            |   expression ';'
                { $$ = $1; }

            |   ';'
                {
                    $$ = new Node( 0, lineNo, "Empty" );
                }
            ;

expression  :   var ASSIGN expression
                {
                    //Create my node
                    $$ = new Node( $2->code, $1->lineNumber(), $2->stringValue );
                    $$->Children.push_back( $1);
                    $$->Children.push_back( $3);
                }

            |   var ADD_ASSIGN expression
                {
                    $$ = new Node( $2->code, $1->lineNumber(), $2->stringValue );
                    $$->Children.push_back( $1);
                    $$->Children.push_back( $3);
                }

            |   var SUB_ASSIGN expression
                {
                    $$ = new Node( $2->code, $1->lineNumber(), $2->stringValue );
                    $$->Children.push_back( $1);
                    $$->Children.push_back( $3);
                }

            |   var MUL_ASSIGN expression
                {
                    $$ = new Node( $2->code, $1->lineNumber(), $2->stringValue );
                    $$->Children.push_back( $1);
                    $$->Children.push_back( $3);
                }

            |   var DIV_ASSIGN expression
                {
                    $$ = new Node( $2->code, $1->lineNumber(), $2->stringValue );
                    $$->Children.push_back( $1);
                    $$->Children.push_back( $3);
                }

            |   simpexp
                { $$ = $1; }
            ;

primative_type :   I8
            |   I16
            |   I32
            |   I64
            |   I128
            |   F32
            |   F64
            |   STR
            |   VEC
            |   HASH
                {
                      $$ = $1;
                }
            ;

var         :   IDENT
                {
                    $$ = new Node( IDENT, $1->line, $1->stringValue );
                }

            |   var DOT IDENT
                {
                    $$ = new Node( IDENT, $1->lineNumber(), $3->stringValue );
                }
            ;

simpexp     :   simpexp logop relexp
                {
                    $$ = $2;
                    $$->Children.push_back( $1);
                    $$->Children.push_back( $3);
                }

            |   relexp
                { $$ = $1; }
            ;

relexp      :   addexp relop addexp
                {
                    $$ = $2;
                    $$->Children.push_back( $1);
                    $$->Children.push_back( $3);
                }

            |   addexp
                { $$ = $1; }
            ;

relop       :   LEQ
                {
                    $$ = new Node( LEQ, $1->line, $1->stringValue );
                }

            |   LT
                {
                    $$ = new Node( LT, $1->line, $1->stringValue );
                }

            |   GT
                {
                    $$ = new Node( GT, $1->line, $1->stringValue );
                }

            |   GEQ
                {
                    $$ = new Node( GEQ, $1->line, $1->stringValue );
                }

            |   EQ
                {
                    $$ = new Node( EQ, $1->line, $1->stringValue );
                }

            |   NEQ
                {
                    $$ = new Node( NEQ, $1->line, $1->stringValue );
                }
            ;

addexp      :   addexp addop term
                {
                    $$ = $2;
                    $$->Children.push_back( $1);
                    $$->Children.push_back( $3);
                }

            |   term
                { $$ = $1; }
            ;

addop       :   ADD
                {
                    $$ = new Node( ADD, $1->line, $1->stringValue );
                }

            |   SUB
                {
                    $$ = new Node( SUB, $1->line, $1->stringValue );
                }
            ;

logop       :   OR
                {
                    $$ = new Node( OR, $1->line, $1->stringValue );
                }

            |   AND
                {
                    $$ = new Node( AND, $1->line, $1->stringValue );
                }
            ;

term        :   term mulop unary
                {
                    $$ = $2;
                    $$->Children.push_back( $1);
                    $$->Children.push_back( $3);
                }

            |   unary
                { $$ = $1; }
            ;

mulop       :   MUL
                {
                    $$ = new Node( MUL, $1->line, $1->stringValue );
                }

            |   DIV
                {
                    $$ = new Node( DIV, $1->line, $1->stringValue );
                }

            |   MOD
                {
                    $$ = new Node( MOD, $1->line, $1->stringValue );
                }

            |   NOT
                {
                    $$ = new Node( NOT, $1->line, $1->stringValue );
                }
            ;

unary       :   unaryop unary
                { $1->Children.push_back($2); }

            |   fact
                { $$ = $1; }
            ;

unaryop     :   NOT
                {
                    $$ = new Node( NOT, $1->line, $1->stringValue );
                }

            |   SUB
                {
                    $$ = new Node( SUB, $1->line, $1->stringValue );
                }
            ;

fact        :   '(' expression ')'
                { $$ = $2; }

            |   var
                { $$ = $1; }

            |   constant
                { $$ = $1; }

            |   str_form
                { $$ = $1; }
            ;

constant    :   NUMBER
                {
                    $$ = new Node( NUMBER, $1->line, $1->stringValue );
                }
            |   NUMBER ':' primative_type
                {
                    $$ = new Node( NUMBER, $1->line, $1->stringValue );
                }
            |   TRUE
                {
                    $$ = new Node( $1->code, $1->line, $1->stringValue );
                }
            |   FALSE
                {
                    $$ = new Node( $1->code, $1->line, $1->stringValue );
                }
            ;

str_form    :   str_literal MOD simpexp
                {
                    $str_literal->Children.append( $simpexp );
                    $$ = $str_literal;
                }
            |   str_literal MOD '(' str_params ')'
                {
                    $str_literal->Children.append( $str_params );
                    $$ = $str_literal;
                }
            |   str_literal
                {
                    $$ = $str_literal;
                }
            ;

str_params  :   simpexp ',' str_params
                { $1->Sibling = $3; }
            |   simpexp
                { $$ = $1; }
            ;

str_literal :   STRING_DBL
                {
                    $$ = new Node( $1->code, $1->line, $1->stringValue );
                }
            |   STRING_TICK
                {
                    $$ = new Node( $1->code, $1->line, $1->stringValue );
                }
            ;

brkstmt     :   BREAK ';'
                {
                    $$ = new Node( BREAK, $1->line, "Break" );
                }
            ;

retstmt     :   RETURN ';'
                {
                    $$ = new Node( RETURN, $1->line, "Return" );
                }
            ;
%%

//The actual main
int qt_main( int argc, char** argv, ProgramNode** parse_tree, FILE** yyin, int* yydebug );


//Pass through main
int main( int argc, char** argv )
{
  return qt_main( argc, argv, &ParseTree, &yyin, &yydebug );
}
