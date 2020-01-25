#ifndef FUNCTIONNODE_H
//Dump out the code
#define FUNCTIONNODE_H

#include "node.h"
#include "declare_variable.h"

class FunctionNode : public Node
{
    private:
    DeclareVariable* _params = nullptr;

    public:
    FunctionNode( int code, int line, QString name, DeclareVariable* params );

    bool codeGenPreChild( QTextStream* stream, Context* context ) override;
};

#endif // FUNCTIONNODE_H
