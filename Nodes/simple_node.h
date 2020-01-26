#ifndef SIMPLENODE_H
#define SIMPLENODE_H

#include <Nodes/node.h>

class SimpleNode : public Node
{
    public:
    SimpleNode( int code, int line, QString label );

    bool codeGenPreChild( QTextStream* stream, Context* context ) override;
};

#endif // SIMPLENODE_H
