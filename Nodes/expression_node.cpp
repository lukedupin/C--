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
    calcualteType(context);

    return _typeName;
}

int ExpressionNode::getTypeCode( Context* context )
{
    calcualteType(context);

    return _typeCode;
}

bool ExpressionNode::codeGenBetweenChild( QTextStream* stream, Context* context, int child_idx )
{
    //Only bost after the first child
    if ( child_idx != 0 )
        return true;

    //Write out the operator for the expression
    (*stream) << context->padding() << " " << _label << " ";
    qDebug("This was called");

    return true;
}

void ExpressionNode::calcualteType( Context* context )
{
    if ( _calculated || Children.count() <= 0 )
        return;
    _calculated = true;

    //Grab the node and pull the type
    auto node = Children.last();
    switch ( node->tokenType() )
    {
        case TRUE:
        case FALSE:
        case NUMBER:
        case STRING_DBL:
        case STRING_TICK: {
            auto const_node = dynamic_cast<ConstantNode*>( node );
            _typeCode = const_node->typeCode();
            _typeName = context->primitiveToNative( const_node->typeCode() );
        } break;

        default: break;
    }
}