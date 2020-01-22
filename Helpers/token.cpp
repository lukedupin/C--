#include <token.h>
#include <node.h>
#include <lex_token.h>
#include <parser.tab.h>

const char* tokenStr( int token )
{
    switch ( token )
    {
        case LEFT_CURLY:
            return "LEFT_CURLY";

        case RIGHT_CURLY:
            return "RIGHT_CURLY";

        case IF:
            return "IF";

        case ELIF:
            return "ELIF";

        case ELSE:
            return "ELSE";

        case LET:
            return "LET";

        case IN:
            return "IN";

        case FN:
            return "FN";

        case CLASS:
            return "CLASS";

        case RETURN:
            return "RETURN";

        case WHILE:
            return "WHILE";

        case SWITCH:
            return "SWITCH";

        case MATCH:
            return "MATCH";

        case CASE:
            return "CASE";

        case DEFAULT:
            return "DEFAULT";

        case DO:
            return "DO";

        case BREAK:
            return "BREAK";

        case CONTINUE:
            return "CONTINUE";

        case FIRST:
            return "FIRST";

        case LAST:
            return "LAST";

        case FALSE:
            return "FALSE";

        case TRUE:
            return "TRUE";

        case ADD_ASSIGN:
            return "ADD_ASSIGN";

        case SUB_ASSIGN:
            return "SUB_ASSIGN";

        case MUL_ASSIGN:
            return "MUL_ASSIGN";

        case DIV_ASSIGN:
            return "DIV_ASSIGN";

        case MUL:
            return "MUL";

        case DIV:
            return "DIV";

        case MOD:
            return "MOD";

        case ADD:
            return "ADD";

        case SUB:
            return "SUB";

        case ARROW_RIGHT:
            return "ARROW_RIGHT";

        case AND:
            return "AND";

        case OR:
            return "OR";

        case NEQ:
            return "NEQ";

        case LEQ:
            return "LEQ";

        case GEQ:
            return "GEQ";

        case EQ:
            return "EQ";

        case GT:
            return "GT";

        case LT:
            return "LT";

        case NOT:
            return "NOT";

        case ASSIGN:
            return "ASSIGN";

        case DOT:
            return "DOT";

        case I8:
            return "I8";

        case I16:
            return "I16";

        case I32:
            return "I32";

        case I64:
            return "I64";

        case I128:
            return "I128";

        case U8:
            return "U8";

        case U16:
            return "U16";

        case U32:
            return "U32";

        case U64:
            return "U64";

        case U128:
            return "U128";

        case F32:
            return "F32";

        case F64:
            return "F64";

        case STR:
            return "STR";

        case VEC:
            return "VEC";

        case HASH:
            return "HASH";

        case IDENT:
            return "IDENT";

        case NUMBER:
            return "NUMBER";

        case STRING_DBL:
            return "STRING_DBL";

        case STRING_TICK:
            return "STRING_TICK";

        case ERROR:
            return "ERROR";

        
        default:
            return "Unknown";
    }
}
