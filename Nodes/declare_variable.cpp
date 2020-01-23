#include "declare_variable.h"

DeclareVariable::DeclareVariable( int code, int line, char* name ) :
    Node( code, line, name )
{
}

bool DeclareVariable::codeGenPreChild( QTextStream* stream, Context* context )
{
    if ( Children.count() < 1 )
        return false;

    auto expression = dynamic_cast<ExpressionNode*>(Children[0]);

    QString pad;
    pad.resize( context->Depth * 4, ' ');
    (*stream) <<  << " " << name
}
