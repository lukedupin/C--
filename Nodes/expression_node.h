#ifndef EXPRESSIONNODE_H
#define EXPRESSIONNODE_H

#include "node.h"

#include <QString>

class ExpressionNode : public Node
{
    private:
    bool _calculated = false;
    int _typeCode = -1;
    QString _typeName;

    public:
    ExpressionNode( int code, int line, QString label );

    QString getTypeName( Context* context );

    int getTypeCode( Context* context );

    bool codeGenBetweenChild( QTextStream* stream, Context* context, int child_idx );

    private:
    void calcualteType( Context* context );
};

#endif // EXPRESSIONNODE_H
