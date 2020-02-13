#ifndef OP_NODE_H
#define OP_NODE_H

#include "node.h"

class OpNode : public Node
{
    public:
    OpNode( int code, int line, QString value );

    NodeType nodeType() override;

    bool codeGenPreChild( QTextStream* stream, Context* context ) override;

    bool codeGenPostChildWrapper( QTextStream* stream, Context* context, Node* node, int idx, int len ) override;

    bool codeGenPostChild( QTextStream* stream, Context* context ) override;
};

#endif
