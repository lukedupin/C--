#ifndef SIMPLENODE_H
#define SIMPLENODE_H

#include <Nodes/node.h>

class SimpleNode : public Node
{
    private:
    int _idx;

    public:
    SimpleNode( int code, int line, QString label, int idx = -1 );

    bool codeGenBetweenChild( QTextStream* stream, Context* context, int idx ) override;
};

#endif // SIMPLENODE_H
