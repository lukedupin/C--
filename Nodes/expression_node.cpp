#include "expression_node.h"

#include "constant_node.h"

#include <Parser/lex_token.h>
#include "parser.tab.h"

ExpressionNode::ExpressionNode( int code, int line, QString label ) :
    Node( code, line, label )
{
}

Node::SemanticType ExpressionNode::semanticType(Context *context)
{
    //Calculate the types?
    if ( _semanticType.TypeCode < 0 )
        _semanticType = Children.last()->semanticType( context );

    return _semanticType;
}

bool ExpressionNode::codeGenBetweenChild( QTextStream* stream, Context* context, int child_idx )
{
    //Only bost after the first child
    if ( child_idx != 0 )
        return true;

    //Write out the operator for the expression
    (*stream) << context->padding() << " " << _label << " ";

    return true;
}
