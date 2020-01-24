#ifndef DECLARE_VARIABLE_H
#define DECLARE_VARIABLE_H

#include "node.h"

class DeclareVariable : public Node
{
    public:
    DeclareVariable( int code, int line, QString name );

    bool codeGenPreChild( QTextStream* stream, Context* context ) override;
};

#endif // DECLARE_VARIABLE_H
