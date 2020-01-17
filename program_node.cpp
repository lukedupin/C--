#include "program_node.h"

using namespace std;

  //Setup a program node
ProgramNode::ProgramNode() :
  Node( 0, 0, "ProgramNode", "Program" )
{
}

  //Write the program
void ProgramNode::writeProgram()
{
  for ( int i = 0; i < Program_Len; i++ )
  {
    if ( Program_Comment[i].size() > 0 )
      fprintf( Code_Output, "\n  %s\n", Program_Comment[i].c_str() );
    fprintf( Code_Output, "%04d: %s\n", i, Program[i].c_str() );
  }
}

  //Generate the code
void ProgramNode::codeGenPreChild()
{
/*
    //Define all my variables
  map<string,int>::iterator it;

    //Global variables
//  commentLine( "Global Variables" );

  // show content:
  for ( it = Var_List.begin(); it != Var_List.end(); it++ )
  {
    string str = (*it).first;
    commentLine( "Define variable %s as reg %d", str.c_str(), (*it).second );
  }
*/
}

  //Print out the program
void ProgramNode::printMyself( int depth )
{
  printf("Program\r\n");
}
