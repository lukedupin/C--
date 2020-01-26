#include "program_node.h"

  //Setup a program node
ProgramNode::ProgramNode() :
  Node( -1, -1, "ProgramNode" )
{
}

Node::NodeType ProgramNode::nodeType()
{
    return PROGRAM_NODE;
}

void ProgramNode::print( int depth )
{
    Q_UNUSED(depth)
    qDebug( "Start Program" );
}
