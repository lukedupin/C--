#ifndef IFNODE_H
#define IFNODE_H

#include "node.h"

class IfNode : public Node
{
    public:
    IfNode( int code, int line );

    bool codeGenPreChild( QTextStream* stream, Context* context ) override;
};

#endif // IFNODE_H
