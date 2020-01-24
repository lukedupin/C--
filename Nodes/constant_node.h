#ifndef CONSTANTNODE_H
#define CONSTANTNODE_H

#include "node.h"

class ConstantNode : public Node
{
    private:
    int _typeCode = -1;
    int _base = 10;

    public:
    ConstantNode( int code, int line, QString value, int type_code = -1, int base = 10 );

    int typeCode();

    int base();
};

#endif // CONSTANTNODE_H
