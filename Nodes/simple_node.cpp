#include "simple_node.h"

SimpleNode::SimpleNode( int code, int line, QString label ) :
    Node( code, line, label )
{
}

bool SimpleNode::codeGenPreChild(QTextStream *stream, Context *context)
{
    Q_UNUSED(context)

    (*stream) << _label << " ";

    return true;
}
