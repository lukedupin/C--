#ifndef PARAMNODE_H
#define PARAMNODE_H

#include "node.h"

class ParamNode : public Node
{
    public:
    enum DeclareType {
        FUNC_PARAM,
        FUNC_RETURN,

        UNKNOWN
    };

    private:
    QString _ident;
    DeclareType _type = UNKNOWN;

    public:
    ParamNode( int type_code, int line, DeclareType type, QString name, QString ident );

    NodeType nodeType() override;

    DeclareType declareType();

    QString getNativeType();

    bool codeGenPreChild(QTextStream *stream, Context *context) override;
};

#endif // PARAMNODE_H
