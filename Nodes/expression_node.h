#ifndef EXPRESSIONNODE_H
#define EXPRESSIONNODE_H

#include "node.h"

#include <QString>

class ExpressionNode : public Node
{
    private:
    Node::SemanticType _semanticType;

    public:
    ExpressionNode( int code, int line, QString label );

    SemanticType semanticType( Context* context ) override;

    bool codeGenBetweenChild( QTextStream* stream, Context* context, int child_idx ) override;
};

#endif // EXPRESSIONNODE_H
