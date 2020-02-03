#ifndef PARAMNODE_H
#define PARAMNODE_H

#include "node.h"

class ParamNode : public Node
{
    public:
    enum Type {
        FUNC_PARAM,
        FUNC_RETURN,
        FUNC_RETURN_SIMPLE,

        UNKNOWN
    };

    private:
    QString _ident;

    public:
    Type DeclareType = UNKNOWN;

    public:
    ParamNode( int type_code, int line, Type type, QString name, QString ident );

    NodeType nodeType() override;

    QString getNativeType();

    bool codeGenPreChild(QTextStream *stream, Context *context) override;
};

#endif // PARAMNODE_H
