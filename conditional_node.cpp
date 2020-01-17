#include "conditional_node.h"
#include "j_token.h"
#include "parser.tab.h"

  //Setup my variable
ConditionalNode::ConditionalNode (int tokenValue, int lineNo, const char* lab)
  : Node(tokenValue, lineNo, lab, "Conditional: ")
{
}

  //Special code generation call
void ConditionalNode::codeGen( bool siblings )
{
  int if_idx;
  int else_idx; 
  int start_idx;
  int reg;

    //Store my start before we do anything, this is for while statements
  start_idx = Program_Len;

    //Add a comment
  if ( m_Token == WHILE )
    commentLine("While Statement");
  else if ( m_Token == IF )
    commentLine("If Statement");

    //Load up my expression
  m_Children[0]->setRegister( (reg = claimRegister()) );
  m_Children[0]->codeGen();
  releaseRegister( reg );

    //Output my logical jumps
  if_idx = writeLine("HOLD UNTIL IF", "");  

    //Output my true code
  m_Children[1]->codeGen();

    //If we do have a else, set a blind jump to the end of the else now
  if ( m_Children[2] != NULL )
    else_idx = writeLine("HOLD UNTIL ELSE", "");

    //Check if we are a while loop
  if ( m_Token == WHILE )
  {
      //Write out my loop back call to test for validity
    commentLine("Loop back to while statement" );
    writeLine( "BVAL %d", "While statement, go back to top and check",
               start_idx ); 

      //Replace any break statements with a branch
    for ( int i = start_idx; i < Program_Len; i++ )
      if ( Program[i].find("BREAK") != std::string::npos )
        writeLine( i, "BVAL %d", "Break out of my loop", Program_Len );
  }

    //Output my jump until if statement
  writeLine( if_idx, "BFVAL %d, %d", "If conditional false, jump to else/end", 
             m_Children[0]->getRegister(), Program_Len ); 

    //Output my else code
  if ( m_Children[2] != NULL )
  {
    commentLine("Else Statement");
    m_Children[2]->codeGen();
    writeLine( else_idx, "BVAL %d", 
                         "ELSE: If was true, starting else, jump to end", 
               Program_Len ); 
  }

    //Dump siblings
  if ( siblings && m_Sibling != NULL )
    m_Sibling->codeGen();
}

  //Print out my name
void ConditionalNode::printMyself( int depth )
{
  printIndent( depth );
  printf( "%s %s\n", m_Category, m_Label );
}
