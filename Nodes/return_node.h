#ifndef RETURNNODE_H
#define RETURNNODE_H

#include "node.h"

class ReturnNode : public Node
{
    private:
    Node* _params = nullptr;

    public:
    ReturnNode( int code, int line, QString name, Node* params = nullptr );

    NodeType nodeType() override;

    bool codeGenPreChild( QTextStream* stream, Context* context ) override;

    bool codeGenPostChild( QTextStream* strem, Context* context ) override;
};

#endif // RETURNNODE_H
