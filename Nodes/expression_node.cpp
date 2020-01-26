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

bool ExpressionNode::codeGenPreChild(QTextStream *stream, Context *context)
{
    Q_UNUSED(context)

    //Write out the operator for the expression
    if ( Parenthesis )
        (*stream) << '(';
    return true;
}

bool ExpressionNode::codeGenPostChild(QTextStream *stream, Context *context)
{
    Q_UNUSED(context)

    //Write out the operator for the expression
    if ( Parenthesis )
        (*stream) << ')';
    return true;
}

bool ExpressionNode::codeGenPostChildWrapper(QTextStream *stream, Context *context, int child_idx)
{
    Q_UNUSED(context)

    //Only bost after the first child
    if ( child_idx != 0 )
        return true;

    //Write out the operator for the expression
    (*stream) << _label << " ";

    return true;
}
