#include "function_node.h"

#include <Parser/lex_token.h>
#include <Parser/parser.tab.h>

#include <QStringList>

FunctionNode::FunctionNode( int code, int line, QString name, Node* params, Node* ret ) :
    Node( code, line, name ),
    _params( params ),
    _ret( ret )
{
}

Node::NodeType FunctionNode::nodeType()
{
    return FUNCTION_NODE;
}

bool FunctionNode::codeGenPreChild(QTextStream *stream, Context *context)
{
    //Go through the param nodes
    QStringList params;
    for ( Node* node = _params;  node != nullptr; node = node->Sibling )
        if ( node->tokenType() != SELF )
            params.append( QString("%1 %2").arg(context->typeToNative(node->tokenType(), node->label()))
                                           .arg(node->label()) );

    QStringList rets;
    for ( Node* node = _ret;  node != nullptr; node = node->Sibling )
        rets.append( dynamic_cast<ParamNode*>(node)->getNativeType() );

    //Calculate the return string
    QString return_sig = "";
    if ( rets.count() == 0 )
        return_sig = "void";
    else if ( rets.count() == 1 )
        return_sig = rets[0];
    else
        return_sig = QString("std::tuple<%1>").arg(rets.join(", "));

    //Write out the function
    (*stream) << context->padding() << return_sig << " "
              << _label << "( " << params.join(", ") << " )" << "\r\n";

    return true;
}
