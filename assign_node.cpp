#include "assign_node.h"
#include "j_token.h"
#include "parser.tab.h"

  //Setup my variable
AssignNode::AssignNode (int token, int lineNo, const char* lab, const char* cat)
  : Node(token, lineNo, lab, cat)
{
}

  //Overload the code gen function
void AssignNode::codeGen( bool siblings )
{
  commentLine("Assign Statement");
  
    //Figure out if we have a direct, or indirect assignment
  switch ( m_Token )
  {
    case ASSIGN:
      if ( m_Children[0]->getTokenType() == IDENT )
      {
          //Claim a result register, ensure it worked
        if ( !m_Children[1]->setRegister( m_Children[0]->getRegister() ) )
        {
          fprintf(stderr, 
                  "Register overrun, statement is too complicated at line %d\n",
                  m_LineNo );
          Error_Count++;
          return;
        }

          //Calculate my expression
        m_Children[1]->codeGen();
      }
        //Handles all possible assigns
      else
      {
          //Claim a result register, ensure it worked
        if ( !m_Children[1]->setRegister( claimRegister() ) )
        {
          fprintf(stderr, 
                  "Register overrun, statement is too complicated at line %d\n",
                  m_LineNo );
          Error_Count++;
          return;
        }

          //Calculate my expression
        m_Children[1]->codeGen();

          //Set the result register
        m_Children[0]->setRegister( m_Children[1]->getRegister() );

          //Assign my variable to the current register value
        m_Children[0]->setReadMode( false );
        m_Children[0]->codeGen();
      }

        //Release my register
      releaseRegister( m_Children[1]->getRegister() );
      break;

      //Simple number assign
    case ASSIGN_CONST:
        //Set the result register
      m_Children[0]->setValue( m_Children[1]->getValue() );

        //Assign my variable to the current register value
      m_Children[0]->setReadMode( false );
      m_Children[0]->codeGen();
      break;

      //Error case!
    default:
      fprintf( stderr, "Invalid assignment request\n" );
      Error_Count++;
      break;
  }

    //If we have a type change, do it here
  if ( m_Children[2] != NULL )
    m_Children[2]->codeGen();

    //Pass to any siblings
  if ( siblings && m_Sibling != NULL )
    m_Sibling->codeGen();
}

  //Print out my name
void AssignNode::printMyself( int depth )
{
  printIndent( depth );
  printf( "%s %s\n", m_Category, m_Label );
}
