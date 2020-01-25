#include "declare_variable.h"

#include <Helpers/token.h>
#include "expression_node.h"
#include "constant_node.h"

DeclareVariable::DeclareVariable( int code, int line, QString name ) :
    Node( code, line, name )
{
}

bool DeclareVariable::codeGenPreChild( QTextStream* stream, Context* context )
{
    if ( Children.count() < 1 )
        return false;

    auto node = Children.last();
    auto semantics = node->semanticType( context );

    (*stream) << context->padding()
              << semantics.TargetType << " "
              << _label << " = ";

    return true;
}

bool DeclareVariable::codeGenPostChild( QTextStream* stream, Context* context )
{
    Q_UNUSED(context)

    (*stream) << ";\r\n";

    return true;
}
