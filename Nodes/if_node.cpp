#include "if_node.h"

#include <Helpers/token.h>
#include <Parser/lex_token.h>
#include <Parser/parser.tab.h>

IfNode::IfNode( int code, int line ) :
    Node( code, line, "" )
{
}

Node::NodeType IfNode::nodeType()
{
    return IF_NODE;
}

bool IfNode::codeGenPreChild( QTextStream* stream, Context* context )
{
    if ( _token == IF )
        (*stream) << context->padding() << "if ";
    else if ( _token == ELIF )
        (*stream) << context->padding() << "else if ";
    else if ( _token == ELSE )
        (*stream) << context->padding() << "else";
    else
        qDebug("***%s", tokenStr(_token));

    return true;
}

bool IfNode::codeGenPostChildWrapper( QTextStream* stream, Context* context, Node* node, int idx, int len )
{
    Q_UNUSED(context)
    Q_UNUSED(node)
    Q_UNUSED(len)

    if ( idx == 0 )
        (*stream) << "\r\n";

    return true;
}
