#include "expression_node.h"

#include "constant_node.h"

#include <Parser/lex_token.h>
#include "parser.tab.h"

ExpressionNode::ExpressionNode( int code, int line, QString label ) :
    Node( code, line, label ),
    _typeName("Unknown")
{
}

QString ExpressionNode::getTypeName( Context* context )
{
    if ( !_calculated && Children.count() > 0 )
        calculateType( context, Children.last() );
    _calculated = true;

    return _typeName;
}

int ExpressionNode::getTypeCode( Context* context )
{
    if ( !_calculated )
        calculateType( context, Children.last() );
    _calculated = true;

    return _typeCode;
}

void ExpressionNode::calculateType( Context* context, Node* node )
{
    if ( node->tokenType() == IDENT)
    {
    }
    else
    {
        auto cn = dynamic_cast<ConstantNode*>(node);
        _typeCode = cn->typeCode();
        switch ( _typeCode )
        {
            case I8:    _typeName = "char"; break;
            case I16:   _typeName = "short"; break;
            case I32:   _typeName = "int"; break;
            case I64:   _typeName = "long"; break;
            case I128:  _typeName = "long long"; break;

            case U8:    _typeName = "unsigned char"; break;
            case U16:   _typeName = "unsigned short"; break;
            case U32:   _typeName = "unsigned int"; break;
            case U64:   _typeName = "unsigned long"; break;
            case U128:  _typeName = "unsigned long long"; break;

            case F32:   _typeName = "float"; break;
            case F64:   _typeName = "double"; break;

            case BOOL:   _typeName = "bool"; break;
            case STR:    _typeName = "QString"; break;

            default:
                _typeName = "Error";
                break;
        }
    }
}
