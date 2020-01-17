#include "dec_node.h"

  //Setup my global variable
int DecNode::Var_Count = 0;

  //Setup my variable
DecNode::DecNode (int tokenValue, int lineNo, const char* name)
  : Node(tokenValue, lineNo, "Declare: ", "DEC"),
  Name( name )
{
      //Store my variable into the list
  if ( Var_List.find( Name ) == Var_List.end() ) 
    Var_List[Name] = (REGISTER_COUNT + Var_Count++);
  else
  {
    Error_Count++;
    fprintf( stderr, "Redeclaration of variable %s at line %d\n", name, lineNo);
  }
}

  //Detects an error
void DecNode::codeDetectMyself()
{
      //Store my variable into the list
  if ( Var_List.find( Name ) == Var_List.end() )
  {
    Error_Count++;
    fprintf(stderr, "Undefined variable: %s at line %d\n", Name, m_LineNo );
  }
}

  //Print out my name
void DecNode::printMyself( int depth )
{
  int id = -1;

      //Store my variable into the list
  if ( Var_List.find( Name ) != Var_List.end() )
    id = Var_List[Name];

      //Dump out the variable
  printIndent( depth );
  printf( "Dec Var: %s [%d]\n", Name, id );
}
