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

int ConstantNode::typeCode()
{
    return _typeCode;
}

int ConstantNode::base()
{
    return _base;
}
