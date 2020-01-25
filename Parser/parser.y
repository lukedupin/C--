%{
    //C includes
    #include <stdio.h>
    #include <stack>

    //Custom includes
    #include "lex_token.h"
    #include <Helpers/token.h>
    #include <Nodes/node.h>

    #include <Nodes/block_node.h>
    #include <Nodes/constant_node.h>
    #include <Nodes/declare_variable.h>
    #include <Nodes/expression_node.h>
    #include <Nodes/function_node.h>
    #include <Nodes/if_node.h>
    #include <Nodes/program_node.h>
    #include <Nodes/simple_node.h>

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
    ProgramNode* ParseTree = nullptr;
    Context* ParseContext = nullptr;
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
%token <tokInfo> FOR
%token <tokInfo> FOREACH
%token <tokInfo> CONTINUE
%token <tokInfo> FIRST
%token <tokInfo> LAST
%token <tokInfo> FALSE
%token <tokInfo> TRUE
%token <tokInfo> SELF
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
%token <tokInfo> BOOL
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
%type <nodeInfo> let_dec
%type <nodeInfo> fn_dec
%type <nodeInfo> fn_ret_parm
%type <nodeInfo> meth_dec
%type <nodeInfo> param_list
%type <nodeInfo> param
%type <nodeInfo> class_dec
%type <nodeInfo> class_block
%type <nodeInfo> class_body
%type <nodeInfo> class_def
%type <nodeInfo> block
%type <nodeInfo> switch_block
%type <nodeInfo> match_block
%type <nodeInfo> stmtlst
%type <nodeInfo> stmt
%type <nodeInfo> noncond
%type <nodeInfo> expression
%type <nodeInfo> expression_list
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
%type <tokInfo> primitive_type

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
decl        :   let_dec
                { $$ = $1; }
            |   fn_dec
                { $$ = $1; }
            |   class_dec
                { $$ = $1; }
            ;

// Declare variables
let_dec      :  LET IDENT ASSIGN expression ';'
                {
                    $$ = new DeclareVariable( LET, $IDENT->line, $IDENT->stringValue );
                    $$->Children.push_back( $expression );
                }
            ;

class_dec   :   CLASS IDENT class_block
                {
                    $$ = new Node( $1->code, $1->line, $IDENT->stringValue );
                    if ( $class_block != nullptr )
                        $$->Children.push_back( $class_block );
                }
            ;

class_block :   LEFT_CURLY class_body RIGHT_CURLY
                {
                    $$ = $class_body;
                }
            |   LEFT_CURLY RIGHT_CURLY
                {
                    $$ = nullptr;
                }
            ;

class_body  :   class_def class_body
                { $1->Sibling = $2; }
            |   class_def
                { $$ = $1; }
            ;

class_def   :   let_dec
                { $$ = $1; }
            |   meth_dec
                { $$ = $1; }
            |   class_dec
                { $$ = $1; }
            ;

meth_dec    :   FN IDENT '(' fn_ret_parm block
                {
                    $$ = new Node( FN, $2->line, $2->stringValue );
                    if ( $fn_ret_parm != nullptr )
                        $block->Children.push_front( $fn_ret_parm );
                    $$->Children.push_back( $block);
                }

            |   FN IDENT '(' param_list fn_ret_parm block
                {
                    $$ = new Node( FN, $2->line, $2->stringValue );
                    $block->Children.push_front( $param_list );
                    if ( $fn_ret_parm != nullptr )
                        $block->Children.push_front( $fn_ret_parm );
                    $$->Children.push_back( $block);
                }

            |   FN IDENT '(' SELF fn_ret_parm block
                {
                    $$ = new Node( FN, $2->line, $2->stringValue );
                    $block->Children.push_front( new Node( SELF, $SELF->line, $SELF->stringValue ));
                    if ( $fn_ret_parm != nullptr )
                        $block->Children.push_front( $fn_ret_parm );
                    $$->Children.push_back( $block);
                }

            |   FN IDENT '(' SELF ',' param_list fn_ret_parm block
                {
                    $$ = new Node( FN, $2->line, $2->stringValue );
                    $block->Children.push_front( new Node( SELF, $SELF->line, $SELF->stringValue ));
                    $block->Children.push_front( $param_list );
                    if ( $fn_ret_parm != nullptr )
                        $block->Children.push_front( $fn_ret_parm );
                    $$->Children.push_back( $block);
                }
            ;

fn_dec      :   FN IDENT '(' fn_ret_parm block
                {
                    $$ = new FunctionNode( FN, $IDENT->line, $IDENT->stringValue, nullptr, $fn_ret_parm );
                    if ( $fn_ret_parm != nullptr )
                        $block->Children.push_front( $fn_ret_parm );
                    $$->Children.push_back( $block );
                }

            |   FN IDENT '(' param_list fn_ret_parm block
                {
                    $$ = new FunctionNode( FN, $IDENT->line, $IDENT->stringValue, $param_list, $fn_ret_parm );
                    if ( $fn_ret_parm != nullptr )
                        $block->Children.push_front( $fn_ret_parm );
                    $$->Children.push_back( $block);
                }
            ;

fn_ret_parm :   ')' ARROW_RIGHT primitive_type
                {
                    $$ = new ParamNode( $3->code, $3->line, $3->stringValue, ParseContext->primitiveToNative( $primitive_type->code ) );
                }

            |   ')' ARROW_RIGHT IDENT
                { $$ = new ParamNode( $3->code, $3->line, $3->stringValue, $IDENT->stringValue ); }

            |   ')' ARROW_RIGHT '(' param_list ')'
                { $$ = $param_list; }

            |   ')'
                { $$ = nullptr; }

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

param       :   IDENT ':' primitive_type
                {
                    $$ = new ParamNode( $1->code, $1->line, $1->stringValue, ParseContext->primitiveToNative( $primitive_type->code ) );
                }
            |   IDENT ':' IDENT
                {
                    $$ = new ParamNode( $1->code, $1->line, $1->stringValue, $3->stringValue );
                }
            ;

block       :   LEFT_CURLY stmtlst  RIGHT_CURLY
                {
                    $$ = new BlockNode( $1->code, $1->line );
                    $$->Children.push_back( $2);
                }

            |   LEFT_CURLY RIGHT_CURLY
                {
                    $$ = new BlockNode( $1->code, $1->line );
                }
            ;

switch_block :  LEFT_CURLY RIGHT_CURLY
                {
                    $$ = new BlockNode( $1->code, $1->line );
                }
            ;

match_block :   LEFT_CURLY RIGHT_CURLY
                {
                    $$ = new BlockNode( $1->code, $1->line );
                }
            ;

stmtlst     :   stmt stmtlst
                {
                    $1->Sibling = $2;
                }

            |   stmt
                { $$ = $1; }
            ;

stmt        :   IF expression block
                {
                    $$ = new IfNode( $1->code, $1->line );
                    $$->Children.push_back( $expression );
                    $$->Children.push_back( $block );
                }

            |   ELIF expression block
                {
                    $$ = new IfNode( $1->code, $1->line );
                    $$->Children.push_back( $expression );
                    $$->Children.push_back( $block );
                }

            |   ELSE block
                {
                    $$ = new IfNode( $1->code, $1->line );
                    $$->Children.push_back( $block );
                }

            |   WHILE '(' expression ')' block
                {
                    $$ = new Node( $1->code, $1->line, $1->stringValue );
                    $$->Children.push_back( $3);
                    $$->Children.push_back( $5);
                }

            |   FOREACH '(' IDENT IN expression ')' block
                {
                    auto iter = new Node( $IN->code, $IN->line, $IN->stringValue );
                    iter->Children.push_back( new Node( $IDENT->code, $IDENT->line, $IDENT->stringValue ));
                    iter->Children.push_back( $expression );

                    //Add the foreach node
                    $$ = new Node( $1->code, $1->line, $1->stringValue );
                    $$->Children.push_back( iter );
                    $$->Children.push_back( $block);
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

            |   let_dec
                { $$ = $1; }

            |   noncond
                { $$ = $1; }
            ;

noncond     :   block ';'
                { $$ = $1; }

            |   retstmt ';'
                { $$ = $1; }

            |   brkstmt ';'
                { $$ = $1; }

            |   var '(' expression_list ')' ';'
                {
                    $$ = new Node( FN, $1->lineNumber(), $1->label() );
                    $$->Children.push_back( $var );
                    $$->Children.push_back( $expression_list );
                }

            |   expression ';'
                { $$ = $1; }

            |   ';'
                {
                    $$ = new Node( 0, lineNo, "Empty" );
                }
            ;

expression_list :  expression ',' expression_list
                { $1->Sibling = $3; }

            |   expression
                { $$ = $1; }
            ;

expression  :   var ASSIGN expression
                {
                    //Create my node
                    $$ = new AssignNode( $2->code, $1->lineNumber(), $2->stringValue );
                    $$->Children.push_back( $1);
                    $$->Children.push_back( $3);
                }

            |   var ADD_ASSIGN expression
                {
                    $$ = new AssignNode( $2->code, $1->lineNumber(), $2->stringValue );
                    $$->Children.push_back( $1);
                    $$->Children.push_back( $3);
                }

            |   var SUB_ASSIGN expression
                {
                    $$ = new AssignNode( $2->code, $1->lineNumber(), $2->stringValue );
                    $$->Children.push_back( $1);
                    $$->Children.push_back( $3);
                }

            |   var MUL_ASSIGN expression
                {
                    $$ = new AssignNode( $2->code, $1->lineNumber(), $2->stringValue );
                    $$->Children.push_back( $1);
                    $$->Children.push_back( $3);
                }

            |   var DIV_ASSIGN expression
                {
                    $$ = new AssignNode( $2->code, $1->lineNumber(), $2->stringValue );
                    $$->Children.push_back( $1);
                    $$->Children.push_back( $3);
                }

            |   simpexp
                {
                    $$ = $1;
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
                    $$ = new SimpleNode( LEQ, $1->line, $1->stringValue, 0 );
                }

            |   LT
                {
                    $$ = new SimpleNode( LT, $1->line, $1->stringValue, 0 );
                }

            |   GT
                {
                    $$ = new SimpleNode( GT, $1->line, $1->stringValue, 0 );
                }

            |   GEQ
                {
                    $$ = new SimpleNode( GEQ, $1->line, $1->stringValue, 0 );
                }

            |   EQ
                {
                    $$ = new SimpleNode( EQ, $1->line, $1->stringValue, 0 );
                }

            |   NEQ
                {
                    $$ = new SimpleNode( NEQ, $1->line, $1->stringValue, 0 );
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
                    $$ = new SimpleNode( ADD, $1->line, $1->stringValue, 0 );
                }

            |   SUB
                {
                    $$ = new SimpleNode( SUB, $1->line, $1->stringValue, 0 );
                }
            ;

logop       :   OR
                {
                    $$ = new SimpleNode( OR, $1->line, $1->stringValue, 0 );
                }

            |   AND
                {
                    $$ = new SimpleNode( AND, $1->line, $1->stringValue, 0 );
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
                    $$ = new SimpleNode( MUL, $1->line, $1->stringValue, 0 );
                }

            |   DIV
                {
                    $$ = new SimpleNode( DIV, $1->line, $1->stringValue, 0 );
                }

            |   MOD
                {
                    $$ = new SimpleNode( MOD, $1->line, $1->stringValue, 0 );
                }

            |   NOT
                {
                    $$ = new SimpleNode( NOT, $1->line, $1->stringValue, 0 );
                }
            ;

unary       :   unaryop unary
                { $1->Children.push_back($2); }

            |   fact
                { $$ = $1; }
            ;

unaryop     :   NOT
                {
                    $$ = new SimpleNode( NOT, $1->line, $1->stringValue );
                }

            |   SUB
                {
                    $$ = new SimpleNode( SUB, $1->line, $1->stringValue );
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

primitive_type :   I8
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
                { $$ = new SimpleNode( $1->code, $1->line, $1->stringValue ); }

            |   var DOT IDENT
                {
                    $$ = new SimpleNode( $2->code, $2->line, $2->stringValue, 0 );
                    $$->Children.push_back( $1 );
                    $$->Children.push_back( new SimpleNode( $3->code, $3->line, $3->stringValue ) );
                }

            |   SELF
                { $$ = new SimpleNode( $1->code, $1->line, $1->stringValue ); }

            |   SELF DOT IDENT
                {
                    $$ = new SimpleNode( $2->code, $2->line, $2->stringValue, 0 );
                    $$->Children.push_back( new SimpleNode( $1->code, $1->line, $1->stringValue ) );
                    $$->Children.push_back( new SimpleNode( $3->code, $3->line, $3->stringValue ) );
                }
            ;

constant    :   NUMBER
                {
                    $$ = new ConstantNode( $1->code, $1->line, $1->stringValue );
                }
            |   NUMBER ':' primitive_type
                {
                    $$ = new ConstantNode( $1->code, $1->line, $1->stringValue, $primitive_type->code );
                }
            |   TRUE
                {
                    $$ = new ConstantNode( $1->code, $1->line, $1->stringValue, BOOL );
                }
            |   FALSE
                {
                    $$ = new ConstantNode( $1->code, $1->line, $1->stringValue, BOOL );
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
                    $$ = new ConstantNode( $1->code, $1->line, $1->stringValue, STR );
                }
            |   STRING_TICK
                {
                    $$ = new ConstantNode( $1->code, $1->line, $1->stringValue, STR );
                }
            ;

brkstmt     :   BREAK
                { $$ = new SimpleNode( $1->code, $1->line, $1->stringValue ); }
            ;

retstmt     :   RETURN
                { $$ = new SimpleNode( $1->code, $1->line, $1->stringValue ); }

            |   RETURN expression
                {
                    $$ = new SimpleNode( $1->code, $1->line, $1->stringValue );
                    $$->Children.push_back( $expression );
                }
            ;
%%

//The actual main
int qt_main( int argc, char** argv, ProgramNode** parse_tree, Context** context,  FILE** yyin, int* yydebug );


//Pass through main
int main( int argc, char** argv )
{
  return qt_main( argc, argv, &ParseTree, &ParseContext, &yyin, &yydebug );
}
