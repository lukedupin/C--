#include "declare_node.h"

#include <Helpers/token.h>
#include "constant_node.h"

DeclareNode::DeclareNode( int code, int line, QString name ) :
    Node( code, line, name )
{
}

Node::NodeType DeclareNode::nodeType()
{
    return DECLARE_NODE;
}

bool DeclareNode::codeGenPreChild( QTextStream* stream, Context* context )
{
    if ( Children.count() < 1 )
        return false;

    auto node = Children.last();
    auto semantics = node->semanticType( context );

    (*stream) << context->padding()
              << semantics.TargetType << " "
              << _label << " = ";

    return true;
}

bool DeclareNode::codeGenPostChild( QTextStream* stream, Context* context )
{
    Q_UNUSED(context)

    (*stream) << ";\r\n";

    return true;
}
