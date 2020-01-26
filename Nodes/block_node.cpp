#include "block_node.h"

BlockNode::BlockNode( int code, int line ) :
    Node( code, line, "" )
{
}

Node::NodeType BlockNode::nodeType()
{
    return BLOCK_NODE;
}

bool BlockNode::increaseScopeDepth()
{
    return true;
}

bool BlockNode::codeGenPreChild( QTextStream* stream, Context* context )
{
    (*stream) << context->padding() << '{' << "\r\n";

    return true;
}

bool BlockNode::codeGenPostChild( QTextStream* stream, Context* context )
{
    (*stream) << context->padding() << '}' << "\r\n";

    return true;
}
