#ifndef BLOCKNODE_H
#define BLOCKNODE_H

#include "node.h"

class BlockNode : public Node
{
    public:
    BlockNode( int code, int line );

    bool increaseScopeDepth() override;

    bool codeGenPreChild( QTextStream* stream, Context* context ) override;

    bool codeGenPostChild( QTextStream* stream, Context* context ) override;
};

#endif // BLOCKNODE_H
