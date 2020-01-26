#include "klass_node.h"

KlassNode::KlassNode( int code, int line, QString name ) :
    Node( code, line, name )
{
}

Node::NodeType KlassNode::nodeType()
{
    return KLASS_NODE;
}

bool KlassNode::increaseScopeDepth()
{
    return true;
}

bool KlassNode::codeGenPreChild( QTextStream* stream, Context* context )
{
    (*stream) << context->padding() << "class " << _label << "\r\n";
    (*stream) << context->padding() << "{\r\n";

    context->KlassStack.push_back( _label );

    return true;
}

bool KlassNode::codeGenPostChild( QTextStream* stream, Context* context )
{
    (*stream) << context->padding() << "}\r\n";

    context->KlassStack.pop_back();

    return true;
}
