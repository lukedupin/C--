#include "function_node.h"

FunctionNode::FunctionNode( int code, int line, QString name, DeclareVariable* params ) :
    Node( code, line, name ),
    _params( params )
{
}

bool FunctionNode::codeGenPreChild(QTextStream *stream, Context *context)
{
    (*stream) << "xxxx" << _label << "( " << "params" << ")";
    return true;
}
