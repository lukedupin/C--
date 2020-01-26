#include "if_node.h"

#include <Helpers/token.h>
#include <Parser/lex_token.h>
#include <Parser/parser.tab.h>

IfNode::IfNode( int code, int line ) :
    Node( code, line, "" )
{
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

bool IfNode::codeGenPostChildWrapper( QTextStream* stream, Context* context, int idx )
{
    Q_UNUSED(context)

    if ( idx == 0 )
        (*stream) << "\r\n";

    return true;
}
