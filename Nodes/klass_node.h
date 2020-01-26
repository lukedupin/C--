#ifndef KLASSNODE_H
#define KLASSNODE_H

#include "node.h"

class KlassNode : public Node
{
    public:
    KlassNode( int code, int line, QString name );

    NodeType nodeType() override;

    bool increaseScopeDepth() override;

    bool codeGenPreChild( QTextStream* stream, Context* context ) override;

    bool codeGenPostChild( QTextStream* stream, Context* context ) override;
};

#endif // KLASSNODE_H
