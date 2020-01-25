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
    (*stream) << _label;

    return true;
}
