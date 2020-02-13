#include "return_node.h"

ReturnNode::ReturnNode( int code, int line, QString label, Node* params ) :
    Node( code, line, label ),
    _params( params )
{
}

Node::NodeType ReturnNode::nodeType()
{
    return RETURN_NODE;
}

bool ReturnNode::codeGenPreChild(QTextStream *stream, Context *context)
{
    if ( CompleteStatement )
        (*stream) << context->padding() << _label << " ";
    else
        (*stream) << _label << " ";

    //Create a construct node
    for ( auto param = _params; param != nullptr; param = param->Sibling )
    {
    }

    return true;
}

bool ReturnNode::codeGenPostChild(QTextStream *stream, Context *context)
{
    Q_UNUSED(context)

    if ( CompleteStatement )
        (*stream) << ";\r\n";

    return true;
}
