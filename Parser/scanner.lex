%option noyywrap
%option yylineno
%{
    #include <stdio.h>
    #include <lex_token.h>
    #include <node.h>
    #include <parser.tab.h>
    int lineNo;
%}

%%

[\(\)\[\],;:] {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = strdup(yytext);
    s->line = yylineno;
    return yytext[0];
}
"{" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "{";
    s->line = yylineno;
    return LEFT_CURLY;
}
"}" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "}";
    s->line = yylineno;
    return RIGHT_CURLY;
}
"if" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "if";
    s->line = yylineno;
    return IF;
}
"else" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "else";
    s->line = yylineno;
    return ELSE;
}
"var" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "var";
    s->line = yylineno;
    return VAR;
}
"fn" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "fn";
    s->line = yylineno;
    return FN;
}
"class" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "class";
    s->line = yylineno;
    return CLASS;
}
"return" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "return";
    s->line = yylineno;
    return RETURN;
}
"while" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "while";
    s->line = yylineno;
    return WHILE;
}
"break" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "break";
    s->line = yylineno;
    return BREAK;
}
"continue" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "continue";
    s->line = yylineno;
    return CONTINUE;
}
"false" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "false";
    s->line = yylineno;
    return FALSE;
}
"true" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "true";
    s->line = yylineno;
    return TRUE;
}
"*" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "*";
    s->line = yylineno;
    return MUL;
}
"/" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "/";
    s->line = yylineno;
    return DIV;
}
"%" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "%";
    s->line = yylineno;
    return MOD;
}
"+" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "+";
    s->line = yylineno;
    return ADD;
}
"-" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "-";
    s->line = yylineno;
    return SUB;
}
"->" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "->";
    s->line = yylineno;
    return ARROW_RIGHT;
}
"<-" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "<-";
    s->line = yylineno;
    return ARROW_LEFT;
}
"&&" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "&&";
    s->line = yylineno;
    return AND;
}
"||" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "||";
    s->line = yylineno;
    return OR;
}
"!=" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "!=";
    s->line = yylineno;
    return NEQ;
}
"<=" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "<=";
    s->line = yylineno;
    return LEQ;
}
">=" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = ">=";
    s->line = yylineno;
    return GEQ;
}
"==" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "==";
    s->line = yylineno;
    return EQ;
}
">" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = ">";
    s->line = yylineno;
    return GT;
}
"<" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "<";
    s->line = yylineno;
    return LT;
}
[\!] {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "!";
    s->line = yylineno;
    return NOT;
}
[\=] {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "=";
    s->line = yylineno;
    return ASSIGN;
}
[.] {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = ".";
    s->line = yylineno;
    return DOT;
}
"i8" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "i8";
    s->line = yylineno;
    return I8;
}
"i16" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "i16";
    s->line = yylineno;
    return I16;
}
"i32" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "i32";
    s->line = yylineno;
    return I32;
}
"i64" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "i64";
    s->line = yylineno;
    return I64;
}
"i128" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "i128";
    s->line = yylineno;
    return I128;
}
"u8" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "u8";
    s->line = yylineno;
    return U8;
}
"u16" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "u16";
    s->line = yylineno;
    return U16;
}
"u32" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "u32";
    s->line = yylineno;
    return U32;
}
"u64" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "u64";
    s->line = yylineno;
    return U64;
}
"u128" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "u128";
    s->line = yylineno;
    return U128;
}
"f32" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "f32";
    s->line = yylineno;
    return F32;
}
"f64" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "f64";
    s->line = yylineno;
    return F64;
}
"str" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "str";
    s->line = yylineno;
    return STR;
}
"vec" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "vec";
    s->line = yylineno;
    return VEC;
}
"hash" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = "hash";
    s->line = yylineno;
    return HASH;
}
[A-Za-z_][A-Za-z0-9_]* {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = strdup(yytext);
    s->line = yylineno;
    return IDENT;
}
[+-]?([0-9]*)(\.([0-9]+))? {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = strdup(yytext);
    s->line = yylineno;
    return NUMBER;
}
"\r\n" { lineNo++;}
"\n" { lineNo++;}
"\r" { lineNo++;}
"//".*\n { lineNo++;}
" " {}
\t {}
. {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->stringValue = yytext;
    s->line = yylineno;
    return ERROR;
}

%%
