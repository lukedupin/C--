#include "context.h"

#include "node.h"

#include <Parser/lex_token.h>
#include <Parser/parser.tab.h>
#include <Helpers/token.h>

Context::Context()
{
    reset();
}

void Context::reset()
{
    Depth = 0;
    NodeStack.clear();
    ScopedVariables.clear();
    Variables.clear();
}

QString Context::padding()
{
    QString pad;
    pad.resize( Depth * 4, ' ' );
    return pad;
}

QString Context::typeToNative(int type_code, QString variable_name)
{
    if ( type_code == IDENT || type_code == SELF )
        return nameToType( variable_name );
    else
        return primitiveToNative( type_code );
}

QString Context::nameToType( QString variable_name )
{
    if ( Variables.contains(variable_name) )
        return Variables[variable_name];

    if ( variable_name == "self" && KlassStack.count() > 0 )
        return KlassStack.last();

    return "Error";
}


QString Context::primitiveToNative(int type_code)
{
    //Primitive type
    switch ( type_code )
    {
        case I8:    return "char";
        case I16:   return "short";
        case I32:   return "int";
        case I64:   return "long";
        case I128:  return "long long";

        case U8:    return "unsigned char";
        case U16:   return "unsigned short";
        case U32:   return "unsigned int";
        case U64:   return "unsigned long";
        case U128:  return "unsigned long long";

        case F32:   return "float";
        case F64:   return "double";

        case BOOL:   return "bool";
        case STR:    return "QString";

        default:
            return "Error";
    }
}
