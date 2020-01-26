#ifndef DECLARE_NODE_H
#define DECLARE_NODE_H

#include "node.h"

class DeclareNode : public Node
{
    public:
    DeclareNode( int code, int line, QString name );

    NodeType nodeType() override;

    bool codeGenPreChild( QTextStream* stream, Context* context ) override;

    bool codeGenPostChild( QTextStream* stream, Context* context ) override;
};

#endif
