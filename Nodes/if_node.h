#ifndef IFNODE_H
#define IFNODE_H

#include "node.h"

class IfNode : public Node
{
    public:
    IfNode( int code, int line );

    NodeType nodeType() override;

    bool codeGenPreChild( QTextStream* stream, Context* context ) override;

    bool codeGenPostChildWrapper( QTextStream* stream, Context* context, int idx ) override;
};

#endif // IFNODE_H
