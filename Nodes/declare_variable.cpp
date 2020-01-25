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

    qDebug("Found a %s in expression", tokenStr( Children.last()->tokenType() ));

    auto expression = dynamic_cast<ConstantNode*>(Children.last());

    (*stream) << context->padding() << context->primitiveToNative( expression->typeCode() ) << " "
              << _label << " = "
              << expression->label() << ";\r\n";

    return true;
}
