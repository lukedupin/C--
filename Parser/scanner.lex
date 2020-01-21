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
    s->code = yytext[0];
    s->line = yylineno;
    s->stringValue = strdup(yytext);
    return yytext[0];
}
"{" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = LEFT_CURLY;
    s->line = yylineno;
    s->stringValue = "{";
    return LEFT_CURLY;
}
"}" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = RIGHT_CURLY;
    s->line = yylineno;
    s->stringValue = "}";
    return RIGHT_CURLY;
}
"if" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = IF;
    s->line = yylineno;
    s->stringValue = "if";
    return IF;
}
"else" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = ELSE;
    s->line = yylineno;
    s->stringValue = "else";
    return ELSE;
}
"var" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = VAR;
    s->line = yylineno;
    s->stringValue = "var";
    return VAR;
}
"fn" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = FN;
    s->line = yylineno;
    s->stringValue = "fn";
    return FN;
}
"class" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = CLASS;
    s->line = yylineno;
    s->stringValue = "class";
    return CLASS;
}
"return" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = RETURN;
    s->line = yylineno;
    s->stringValue = "return";
    return RETURN;
}
"while" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = WHILE;
    s->line = yylineno;
    s->stringValue = "while";
    return WHILE;
}
"break" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = BREAK;
    s->line = yylineno;
    s->stringValue = "break";
    return BREAK;
}
"continue" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = CONTINUE;
    s->line = yylineno;
    s->stringValue = "continue";
    return CONTINUE;
}
"false" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = FALSE;
    s->line = yylineno;
    s->stringValue = "false";
    return FALSE;
}
"true" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = TRUE;
    s->line = yylineno;
    s->stringValue = "true";
    return TRUE;
}
"*" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = MUL;
    s->line = yylineno;
    s->stringValue = "*";
    return MUL;
}
"/" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = DIV;
    s->line = yylineno;
    s->stringValue = "/";
    return DIV;
}
"%" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = MOD;
    s->line = yylineno;
    s->stringValue = "%";
    return MOD;
}
"+" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = ADD;
    s->line = yylineno;
    s->stringValue = "+";
    return ADD;
}
"-" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = SUB;
    s->line = yylineno;
    s->stringValue = "-";
    return SUB;
}
"->" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = ARROW_RIGHT;
    s->line = yylineno;
    s->stringValue = "->";
    return ARROW_RIGHT;
}
"<-" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = ARROW_LEFT;
    s->line = yylineno;
    s->stringValue = "<-";
    return ARROW_LEFT;
}
"&&" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = AND;
    s->line = yylineno;
    s->stringValue = "&&";
    return AND;
}
"||" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = OR;
    s->line = yylineno;
    s->stringValue = "||";
    return OR;
}
"!=" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = NEQ;
    s->line = yylineno;
    s->stringValue = "!=";
    return NEQ;
}
"<=" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = LEQ;
    s->line = yylineno;
    s->stringValue = "<=";
    return LEQ;
}
">=" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = GEQ;
    s->line = yylineno;
    s->stringValue = ">=";
    return GEQ;
}
"==" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = EQ;
    s->line = yylineno;
    s->stringValue = "==";
    return EQ;
}
">" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = GT;
    s->line = yylineno;
    s->stringValue = ">";
    return GT;
}
"<" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = LT;
    s->line = yylineno;
    s->stringValue = "<";
    return LT;
}
[\!] {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = NOT;
    s->line = yylineno;
    s->stringValue = "!";
    return NOT;
}
[\=] {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = ASSIGN;
    s->line = yylineno;
    s->stringValue = "=";
    return ASSIGN;
}
[.] {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = DOT;
    s->line = yylineno;
    s->stringValue = ".";
    return DOT;
}
"i8" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = I8;
    s->line = yylineno;
    s->stringValue = "i8";
    return I8;
}
"i16" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = I16;
    s->line = yylineno;
    s->stringValue = "i16";
    return I16;
}
"i32" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = I32;
    s->line = yylineno;
    s->stringValue = "i32";
    return I32;
}
"i64" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = I64;
    s->line = yylineno;
    s->stringValue = "i64";
    return I64;
}
"i128" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = I128;
    s->line = yylineno;
    s->stringValue = "i128";
    return I128;
}
"u8" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = U8;
    s->line = yylineno;
    s->stringValue = "u8";
    return U8;
}
"u16" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = U16;
    s->line = yylineno;
    s->stringValue = "u16";
    return U16;
}
"u32" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = U32;
    s->line = yylineno;
    s->stringValue = "u32";
    return U32;
}
"u64" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = U64;
    s->line = yylineno;
    s->stringValue = "u64";
    return U64;
}
"u128" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = U128;
    s->line = yylineno;
    s->stringValue = "u128";
    return U128;
}
"f32" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = F32;
    s->line = yylineno;
    s->stringValue = "f32";
    return F32;
}
"f64" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = F64;
    s->line = yylineno;
    s->stringValue = "f64";
    return F64;
}
"str" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = STR;
    s->line = yylineno;
    s->stringValue = "str";
    return STR;
}
"vec" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = VEC;
    s->line = yylineno;
    s->stringValue = "vec";
    return VEC;
}
"hash" {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = HASH;
    s->line = yylineno;
    s->stringValue = "hash";
    return HASH;
}
[A-Za-z_][A-Za-z0-9_]* {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = IDENT;
    s->line = yylineno;
    s->stringValue = strdup(yytext);
    return IDENT;
}
[+-]?([0-9]*)(\.([0-9]+))? {
    lineNo = yylineno;
    LexToken * s = new LexToken;
    yylval.tokInfo = s;
    s->code = NUMBER;
    s->line = yylineno;
    s->stringValue = strdup(yytext);
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
    s->code = ERROR;
    s->line = yylineno;
    s->stringValue = yytext;
    return ERROR;
}

%%
