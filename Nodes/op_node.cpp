#include "op_node.h"

OpNode::OpNode( int code, int line, QString value ) :
    Node( code, line, value )
{
}

Node::NodeType OpNode::nodeType()
{
    return OP_NODE;
}

bool OpNode::codeGenPreChild( QTextStream* stream, Context* context )
{
    if ( CompleteStatement )
        (*stream) << context->padding();
    if ( Parenthesis )
        (*stream) << '(';

    return true;
}



bool OpNode::codeGenPostChildWrapper( QTextStream* stream, Context* context, Node* node, int idx, int len )
{
    Q_UNUSED(context)
    Q_UNUSED(node)
    Q_UNUSED(len)

    if ( idx == 0 )
        (*stream) << _label << " ";

    return true;
}


bool OpNode::codeGenPostChild( QTextStream* stream, Context* context )
{
    Q_UNUSED(context)

    if ( Parenthesis )
        (*stream) << ')';
    if ( CompleteStatement )
        (*stream) << ";\r\n";

    return true;
}
