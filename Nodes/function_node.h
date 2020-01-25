#ifndef FUNCTIONNODE_H
#define FUNCTIONNODE_H

#include "node.h"
#include "param_node.h"

class FunctionNode : public Node
{
    private:
    ParamNode* _params = nullptr;
    ParamNode* _ret = nullptr;

    public:
    FunctionNode( int code, int line, QString name, Node* params, Node* ret );

    bool codeGenPreChild( QTextStream* stream, Context* context ) override;
};

#endif // FUNCTIONNODE_H
