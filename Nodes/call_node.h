#ifndef CALLNODE_H
#define CALLNODE_H

#include "node.h"

class CallNode : public Node
{
    public:
    CallNode( int token, int line, QString name );

    NodeType nodeType() override;

    bool codeGenPreChild(QTextStream *stream, Context *context) override;

    bool codeGenPreChildWrapper(QTextStream *stream, Context *context, Node* node, int idx, int len ) override;

    bool codeGenPostChildWrapper(QTextStream *stream, Context *context, Node* node, int idx, int len ) override;

    bool codeGenPostChild(QTextStream *stream, Context *context) override;
};

#endif // CALLNODE_H
