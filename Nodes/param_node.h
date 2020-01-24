#ifndef PARAMNODE_H
#define PARAMNODE_H

#include "node.h"

class ParamNode : public Node
{
    private:
    QString _ident;

    public:
    ParamNode( int type_code, int line, QString name, QString ident );

    bool codeGenPreChild(QTextStream *stream, Context *context) override;
};

#endif // PARAMNODE_H
