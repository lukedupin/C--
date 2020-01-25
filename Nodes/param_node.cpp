#include "param_node.h"

#include <Parser/lex_token.h>
#include <Parser/parser.tab.h>

ParamNode::ParamNode( int type_code, int line, QString name, QString ident ) :
    Node( type_code, line, name ),
    _ident( ident )
{
}

QString ParamNode::getType()
{
    return _ident;
}

bool ParamNode::codeGenPreChild(QTextStream *stream, Context *context)
{
    Q_UNUSED(context)

    QStringList ary;
    ParamNode* node = this;

    //Loop while we have nodes
    while ( node != nullptr )
    {
        ary.append( QString("%1 %2").arg(node->_ident).arg(node->_label) );
        node = dynamic_cast<ParamNode*>( node->Sibling );
    }

    //Write out the param list with types defined in C++ style
    (*stream) << ary.join(", ");

    return true;
}
