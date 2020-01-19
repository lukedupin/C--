%option noyywrap
%option yylineno
%{
    #include <stdio.h>
    #include "j_token.h"
    #include "node.h"
    #include "parser.tab.h"
    int lineNo;
%}

%%

[\(\)\[\]\{\},;:] {
    lineNo = yylineno;
    JToken * s = new JToken;
    yylval.tokInfo = s;
    s->stringValue = strdup(yytext);
    s->line = yylineno;
    return yytext[0];
}
"if" {
    lineNo = yylineno;
    JToken * s = new JToken;
    yylval.tokInfo = s;
    s->stringValue = "if";
    s->line = yylineno;
    return IF;
}
"else" {
    lineNo = yylineno;
    JToken * s = new JToken;
    yylval.tokInfo = s;
    s->stringValue = "else";
    s->line = yylineno;
    return ELSE;
}
"var" {
    lineNo = yylineno;
    JToken * s = new JToken;
    yylval.tokInfo = s;
    s->stringValue = "var";
    s->line = yylineno;
    return VAR;
}
"fn" {
    lineNo = yylineno;
    JToken * s = new JToken;
    yylval.tokInfo = s;
    s->stringValue = "fn";
    s->line = yylineno;
    return FN;
}
"class" {
    lineNo = yylineno;
    JToken * s = new JToken;
    yylval.tokInfo = s;
    s->stringValue = "class";
    s->line = yylineno;
    return CLASS;
}
"return" {
    lineNo = yylineno;
    JToken * s = new JToken;
    yylval.tokInfo = s;
    s->stringValue = "return";
    s->line = yylineno;
    return RETURN;
}
"while" {
    lineNo = yylineno;
    JToken * s = new JToken;
    yylval.tokInfo = s;
    s->stringValue = "while";
    s->line = yylineno;
    return WHILE;
}
"break" {
    lineNo = yylineno;
    JToken * s = new JToken;
    yylval.tokInfo = s;
    s->stringValue = "break";
    s->line = yylineno;
    return BREAK;
}
"continue" {
    lineNo = yylineno;
    JToken * s = new JToken;
    yylval.tokInfo = s;
    s->stringValue = "continue";
    s->line = yylineno;
    return CONTINUE;
}
"false" {
    lineNo = yylineno;
    JToken * s = new JToken;
    yylval.tokInfo = s;
    s->stringValue = "false";
    s->line = yylineno;
    return FALSE;
}
"true" {
    lineNo = yylineno;
    JToken * s = new JToken;
    yylval.tokInfo = s;
    s->stringValue = "true";
    s->line = yylineno;
    return TRUE;
}
"*" {
    lineNo = yylineno;
    JToken * s = new JToken;
    yylval.tokInfo = s;
    s->stringValue = "*";
    s->line = yylineno;
    return MUL;
}
"/" {
    lineNo = yylineno;
    JToken * s = new JToken;
    yylval.tokInfo = s;
    s->stringValue = "/";
    s->line = yylineno;
    return DIV;
}
"%" {
    lineNo = yylineno;
    JToken * s = new JToken;
    yylval.tokInfo = s;
    s->stringValue = "%";
    s->line = yylineno;
    return MOD;
}
"+" {
    lineNo = yylineno;
    JToken * s = new JToken;
    yylval.tokInfo = s;
    s->stringValue = "+";
    s->line = yylineno;
    return ADD;
}
"-" {
    lineNo = yylineno;
    JToken * s = new JToken;
    yylval.tokInfo = s;
    s->stringValue = "-";
    s->line = yylineno;
    return SUB;
}
"&&" {
    lineNo = yylineno;
    JToken * s = new JToken;
    yylval.tokInfo = s;
    s->stringValue = "&&";
    s->line = yylineno;
    return AND;
}
"||" {
    lineNo = yylineno;
    JToken * s = new JToken;
    yylval.tokInfo = s;
    s->stringValue = "||";
    s->line = yylineno;
    return OR;
}
"!=" {
    lineNo = yylineno;
    JToken * s = new JToken;
    yylval.tokInfo = s;
    s->stringValue = "!=";
    s->line = yylineno;
    return NEQ;
}
"<=" {
    lineNo = yylineno;
    JToken * s = new JToken;
    yylval.tokInfo = s;
    s->stringValue = "<=";
    s->line = yylineno;
    return LEQ;
}
">=" {
    lineNo = yylineno;
    JToken * s = new JToken;
    yylval.tokInfo = s;
    s->stringValue = ">=";
    s->line = yylineno;
    return GEQ;
}
"==" {
    lineNo = yylineno;
    JToken * s = new JToken;
    yylval.tokInfo = s;
    s->stringValue = "==";
    s->line = yylineno;
    return EQ;
}
">" {
    lineNo = yylineno;
    JToken * s = new JToken;
    yylval.tokInfo = s;
    s->stringValue = ">";
    s->line = yylineno;
    return GT;
}
"<" {
    lineNo = yylineno;
    JToken * s = new JToken;
    yylval.tokInfo = s;
    s->stringValue = "<";
    s->line = yylineno;
    return LT;
}
[\!] {
    lineNo = yylineno;
    JToken * s = new JToken;
    yylval.tokInfo = s;
!    s->line = yylineno;
    return NOT;
}
[\=] {
    lineNo = yylineno;
    JToken * s = new JToken;
    yylval.tokInfo = s;
=    s->line = yylineno;
    return ASSIGN;
}
[.] {
    lineNo = yylineno;
    JToken * s = new JToken;
    yylval.tokInfo = s;
.    s->line = yylineno;
    return DOT;
}
[A-Za-z_][A-Za-z0-9_]* {
    lineNo = yylineno;
    JToken * s = new JToken;
    yylval.tokInfo = s;
    s->stringValue = strdup(yytext);
    s->line = yylineno;
    return IDENT;
}
[+-]?([0-9]*)(\.([0-9]+))? {
    lineNo = yylineno;
    JToken * s = new JToken;
    yylval.tokInfo = s;
    s->stringValue = strdup(yytext);
    s->line = yylineno;
    return NUMBER;
}
"\r\n" { lineNo++;}
"\n" { lineNo++;}
"\r" { lineNo++;}
"//".*
 { lineNo++;}
" " {}
\t {}
. {
    lineNo = yylineno;
    JToken * s = new JToken;
    yylval.tokInfo = s;
    s->stringValue = yytext;
    s->line = yylineno;
    return ERROR;
}

%%
