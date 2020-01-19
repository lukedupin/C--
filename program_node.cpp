#include "program_node.h"

#include <iostream>

  //Setup a program node
ProgramNode::ProgramNode() :
  Node( -1, -1, "ProgramNode" )
{
}

void ProgramNode::print( int depth )
{
    cout << "Start Program" << endl;
}
