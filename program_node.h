#ifndef PROGRAM_NODE_H
#define PROGRAM_NODE_H

#include "node.h"

class ProgramNode : public Node
{
    public:
    ProgramNode();

    protected:
    void print( int depth ) override;
};

#endif
