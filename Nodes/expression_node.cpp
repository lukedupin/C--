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

void ExpressionNode::calcualteType( Context* context )
{
    if ( _calculated || Children.count() <= 0 )
        return;
    _calculated = true;

    auto node = Children.last();
    _typeCode = node->tokenType();
    _typeName = context->primativeToNative( node->tokenType() );
}
