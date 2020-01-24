#include "declare_variable.h"

#include "expression_node.h"

DeclareVariable::DeclareVariable( int code, int line, QString name ) :
    Node( code, line, name )
{
}

bool DeclareVariable::codeGenPreChild( QTextStream* stream, Context* context )
{
    if ( Children.count() < 1 )
        return false;

    auto expression = dynamic_cast<ExpressionNode*>(Children.last());

    QString pad;
    pad.resize( context->Depth * 4, ' ');
    (*stream) << expression->getTypeName( context ) << " "
              << _label << " = "
              << expression->label() << ";\r\n";

    return true;
}
