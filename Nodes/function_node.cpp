#include "function_node.h"

#include <Parser/lex_token.h>
#include <Parser/parser.tab.h>

#include <QStringList>

FunctionNode::FunctionNode( int code, int line, QString name, Node* params, Node* ret ) :
    Node( code, line, name ),
    _params( dynamic_cast<ParamNode*>( params ) ),
    _ret( dynamic_cast<ParamNode*>( ret ) )
{
}

bool FunctionNode::codeGenPreChild(QTextStream *stream, Context *context)
{
    QStringList params;
    QStringList rets;

    //Go through the param nodes
    for ( ParamNode* node = _params;  node != nullptr;
          node = dynamic_cast<ParamNode*>(node->Sibling) )
        params.append( QString("%1 %2").arg(node->getType()).arg(node->label()) );

    for ( ParamNode* node = _ret;  node != nullptr;
          node = dynamic_cast<ParamNode*>(node->Sibling) )
        rets.append( node->getType() );

    //Calculate the return string
    QString return_sig = "";
    if ( rets.count() == 0 )
        return_sig = "void";
    else if ( rets.count() == 1 )
        return_sig = rets[0];
    else
        return_sig = QString("std::tuple<%1>").arg(rets.join(", "));

    //Write out the function
    (*stream) << context->padding() << return_sig << " " << _label << "( " << params.join(", ") << " )" << "\r\n";

    return true;
}
