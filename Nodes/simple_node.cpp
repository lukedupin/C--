#include "simple_node.h"

SimpleNode::SimpleNode( int code, int line, QString label ) :
    Node( code, line, label )
{
}

Node::NodeType SimpleNode::nodeType()
{
    return SIMPLE_NODE;
}

bool SimpleNode::codeGenPreChild(QTextStream *stream, Context *context)
{
    if ( CompleteStatement )
        (*stream) << context->padding() << _label << " ";
    else
        (*stream) << _label << " ";

    return true;
}

bool SimpleNode::codeGenPostChild(QTextStream *stream, Context *context)
{
    Q_UNUSED(context)

    if ( CompleteStatement )
        (*stream) << ";\r\n";

    return true;
}
