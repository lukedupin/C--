#include "simple_node.h"

SimpleNode::SimpleNode( int code, int line, QString label, int idx ) :
    Node( code, line, label ),
    _idx( idx )
{
}

bool SimpleNode::codeGenBetweenChild( QTextStream* stream, Context* context, int idx )
{
    Q_UNUSED(context)

    if ( _idx == idx )
        (*stream) << _label << " ";

    return true;
}
