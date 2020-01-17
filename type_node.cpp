#include "type_node.h"

  //Defines my type node
TypeNode::TypeNode( int token, int line, const char* label, const char* cat )
  : Node( token, line, label, cat )
{
}

  //Print out my type conversion
void TypeNode::printMyself( int depth )
{
  printIndent(depth);
  printf( "%s: %s\n", m_Category, m_Label );
}
