#include "stm_node.h"
#include "j_token.h"
#include "parser.tab.h"

  //Setup my object
StmNode::StmNode( int token, int line, const char* label )
  : Node( token, line, label, "" )
{
}

  //Dump my code gen
void StmNode::codeGenPreChild()
{
    //Figure out which token type we are
  switch ( m_Token )
  {
    case BREAK:
      commentLine("Break");
      writeLine("BREAK", "Break out of my loop");
      break;

    case RETURN:
      commentLine("Return");
      writeLine("NOP", "Exit the event");
      break;

      //No code gen
    default:
      break;
  }
}

  //Print out my code statement
void StmNode::printMyself( int depth )
{
  printIndent( depth );
  printf( "%s: %d\n", m_Label, m_Token );
}
