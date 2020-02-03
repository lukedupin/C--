#include "call_node.h"

#include <lex_token.h>
#include <parser.tab.h>

CallNode::CallNode( int token, int line, QString name ) :
    Node( token, line, name )
{
}

Node::NodeType CallNode::nodeType()
{
    return CALL_NODE;
}

bool CallNode::codeGenPreChild(QTextStream *stream, Context *context)
{
    if ( CompleteStatement )
        (*stream) << context->padding();

    //go through the children, looked for named variable arguments.
    //If found, replace those with correctly ordered calls based on context

    return true;
}

bool CallNode::codeGenPreChildWrapper(QTextStream *stream, Context *context, int idx )
{
    Q_UNUSED(context)

    //Must be comma argument list
    if ( idx > 1 )
        (*stream) << ',';

    return true;
}

bool CallNode::codeGenPostChildWrapper(QTextStream *stream, Context *context, int idx )
{
    Q_UNUSED(context)

    //This is after the name of the function/method call
    if ( idx == 0 )
        (*stream) << '(';

    return true;
}

bool CallNode::codeGenPostChild(QTextStream *stream, Context *context)
{
    Q_UNUSED(context)

    if ( CompleteStatement )
        (*stream) << ");\r\n";
    else
        (*stream) << ')';

    return true;
}
