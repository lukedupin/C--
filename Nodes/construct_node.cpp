#include "construct_node.h"

ConstructNode::ConstructNode( Type type, Node* decl, int line ) :
    Node( '=', line, "" ),
    _type( type ),
    _decl( decl )
{
}

Node::NodeType ConstructNode::nodeType()
{
    return CONSTRUCT_NODE;
}

bool ConstructNode::codeGenPreChild( QTextStream* stream, Context* context )
{
    QStringList list;

    for ( auto node = _decl;
          node != nullptr;
          node = node->Sibling )
        list.append( node->label() );

    switch ( _type )
    {
        case TUPLE:
            (*stream) << "std::make_tuple(" << list.join(", ") << ')';
            break;

        case ARRAY:
            (*stream) << "Array";
            break;

        case HASH:
            (*stream) << "HASH";
            break;

        default:
            return false;
    }

    return true;
}
