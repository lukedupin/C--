#include "param_node.h"

#include <Parser/lex_token.h>
#include <Parser/parser.tab.h>

ParamNode::ParamNode( int type_code, int line, Type type, QString name, QString ident ) :
    Node( type_code, line, name ),
    _ident( ident ),
    DeclareType( type )
{
}

Node::NodeType ParamNode::nodeType()
{
    return PARAM_NODE;
}

QString ParamNode::getNativeType()
{
    return _ident;
}

bool ParamNode::codeGenPreChild(QTextStream *stream, Context *context)
{
    Q_UNUSED(context)

    switch ( DeclareType )
    {
        case FUNC_PARAM: {
            QStringList ary;

            //Loop while we have nodes
            for ( auto node = this;
                  node != nullptr;
                  node = dynamic_cast<ParamNode*>( node->Sibling ) )
                ary.append( QString("%1 %2").arg(node->_ident).arg(node->_label) );

            (*stream) << ary.join(", ");
        } break;

        case FUNC_RETURN: {
            (*stream) << context->padding()
                      << QString("%1 %2").arg(_ident).arg(_label)
                      << ";\r\n";
        } break;

        default: break;
    }

    return true;
}
