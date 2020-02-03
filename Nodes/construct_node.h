#ifndef CONSTRUCTNODE_H
#define CONSTRUCTNODE_H

#include "node.h"

class ConstructNode : public Node
{
    public:
    enum Type {
        INVALID,

        TUPLE,
        ARRAY,
        HASH
    };

    private:
    Type _type = INVALID;
    Node* _decl = nullptr;

    public:
    ConstructNode( Type type, Node* decl, int line );

    NodeType nodeType() override;

    bool codeGenPreChild( QTextStream* stream, Context* context ) override;
};

#endif // CONSTRUCTNODE_H
