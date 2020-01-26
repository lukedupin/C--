#ifndef FUNCTIONNODE_H
#define FUNCTIONNODE_H

#include "node.h"
#include "param_node.h"

class FunctionNode : public Node
{
    private:
    Node* _params = nullptr;
    Node* _ret = nullptr;

    public:
    FunctionNode( int code, int line, QString name, Node* params, Node* ret );

    NodeType nodeType() override;

    bool codeGenPreChild( QTextStream* stream, Context* context ) override;
};

#endif // FUNCTIONNODE_H
