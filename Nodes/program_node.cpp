#include "program_node.h"

  //Setup a program node
ProgramNode::ProgramNode() :
  Node( -1, -1, "ProgramNode" )
{
}

void ProgramNode::print( int depth )
{
    Q_UNUSED(depth)
    qDebug( "Start Program" );
}
