#include "constant_node.h"

#include <Parser/lex_token.h>
#include "parser.tab.h"

ConstantNode::ConstantNode( int code, int line, QString value, int type_code, int base ) :
    Node( code, line, value ),
    _typeCode( type_code ),
    _base( base )
{
    if ( type_code < 0 )
    {
        if ( value.contains('.'))
            _typeCode = F64;
        else
            _typeCode = I32;
    }
}

Node::NodeType ConstantNode::nodeType()
{
    return CONSTANT_NODE;
}

Node::SemanticType ConstantNode::semanticType(Context *context)
{
    SemanticType sem;
    {
        sem.TypeCode = _typeCode;
        sem.TargetType = context->primitiveToNative( _typeCode );
    }

    return sem;
}

bool ConstantNode::codeGenPreChild( QTextStream* stream, Context* context )
{
    Q_UNUSED(context)

    if ( _typeCode == STR )
        (*stream) << "QString(" << _label << ')';
    else
        (*stream) << _label;

    return true;
}

bool ConstantNode::codeGenPreChildWrapper( QTextStream* stream, Context* context, int idx )
{
    Q_UNUSED(context)
    Q_UNUSED(idx)

    if ( _typeCode == STR )
        (*stream) << ".arg(";

    return true;
}


bool ConstantNode::codeGenPostChildWrapper( QTextStream* stream, Context* context, int idx )
{
    Q_UNUSED(context)
    Q_UNUSED(idx)

    if ( _typeCode == STR )
        (*stream) << ')';

    return true;
}
