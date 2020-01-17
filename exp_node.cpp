#include "exp_node.h"
#include "j_token.h"
#include "parser.tab.h"

  //Setup my variable
ExpNode::ExpNode (int tokenValue, int lineNo, const char* lab, const char* cat)
  : Node(tokenValue, lineNo, lab, cat)
{
}

  //Define my code generate, which there is none for me
void ExpNode::codeGenPreChild()
{
    //Loop through my args
  for ( int i = 0; i < 2; i++ )
  {
    Arg[i] = -1;

      //break if we don't have a child
    if ( m_Children[i] == NULL ) continue;

      //If child0 is a variable, assign Arg[i] to that, else, claim a register
    if ( m_Children[i]->getTokenType() == IDENT )
      Arg[i] = m_Children[i]->getRegister();
    else
      m_Children[i]->setRegister( Arg[i] = claimRegister() );
  }
}

  //Define my code generation for after the children are called
void ExpNode::codeGenPostChild()
{
    //Based on the action type, conduct that, and then
  switch ( m_Token )
  {
//Arithmetic ops
    case ADD:
      writeLine("ADD %d, %d, %d", "Add Reg%d and Reg%d, store in Reg%d",
                m_Result_Reg, Arg[0], Arg[1], 
                Arg[0], Arg[1], m_Result_Reg );
      break;

    case SUBT:
      writeLine("SUB %d, %d, %d", "Sub Reg%d from Reg%d, store in Reg%d",
                m_Result_Reg, Arg[0], Arg[1], 
                Arg[0], Arg[1], m_Result_Reg );
      break;

    case MUL:
      writeLine("MUL %d, %d, %d", "Multiple Reg%d and Reg%d, store in Reg%d",
                m_Result_Reg, Arg[0], Arg[1], 
                Arg[0], Arg[1], m_Result_Reg );
      break;

     case DIV:
      writeLine("DIV %d, %d, %d", "Divide Reg%d / Reg%d, store in Reg%d",
                m_Result_Reg, Arg[0], Arg[1], 
                Arg[0], Arg[1], m_Result_Reg );
      break;

     case MOD:
      writeLine("MOD %d, %d, %d", "Mod Reg%d % Reg%d, store in Reg%d",
                m_Result_Reg, Arg[0], Arg[1], 
                Arg[0], Arg[1], m_Result_Reg );
      break;

//Logic ops
     case AND:
      writeLine("AND %d, %d, %d", "Reg%d && Reg%d, store in Reg%d",
                m_Result_Reg, Arg[0], Arg[1], 
                Arg[0], Arg[1], m_Result_Reg );
      break;

     case OR:
      writeLine("OR %d, %d, %d", "Reg%d || Reg%d, store in Reg%d",
                m_Result_Reg, Arg[0], Arg[1], 
                Arg[0], Arg[1], m_Result_Reg );
      break;

     case GEQ:
      writeLine("GEQ %d, %d, %d", "Reg%d >= Reg%d, store in Reg%d",
                m_Result_Reg, Arg[0], Arg[1], 
                Arg[0], Arg[1], m_Result_Reg );
      break;

     case LEQ:
      writeLine("GEQ %d, %d, %d", "Reg%d >= Reg%d, store in Reg%d",
                m_Result_Reg, Arg[1], Arg[0], 
                Arg[1], Arg[0], m_Result_Reg );
      break;

     case NEQ:
      writeLine("NEQ %d, %d, %d", "Reg%d != Reg%d, store in Reg%d",
                m_Result_Reg, Arg[0], Arg[1], 
                Arg[0], Arg[1], m_Result_Reg );
      break;

     case GREAT:
      writeLine("GREAT %d, %d, %d", "Reg%d > Reg%d, store in Reg%d",
                m_Result_Reg, Arg[0], Arg[1], 
                Arg[0], Arg[1], m_Result_Reg );
      break;

     case LESS:
      writeLine("GREAT %d, %d, %d", "Reg%d < Reg%d, store in Reg%d",
                m_Result_Reg, Arg[1], Arg[0], 
                Arg[1], Arg[0], m_Result_Reg );
      break;

     case EQ:
      writeLine("EQ %d, %d, %d", "Reg%d == Reg%d, store in Reg%d",
                m_Result_Reg, Arg[0], Arg[1], 
                Arg[0], Arg[1], m_Result_Reg );
      break;

     case NOT:
      writeLine("NOT %d, %d", "!Reg%d, store in Reg%d",
                m_Result_Reg, Arg[0], Arg[0], m_Result_Reg );
      break;

      //No operation to be had
    default:
      break;
  };

    //Give back my registers
  releaseRegister( Arg[0] );
  releaseRegister( Arg[1] );
}

  //Print out my name
void ExpNode::printMyself( int depth )
{
  printIndent( depth );
  printf( "%s %s\n", m_Category, m_Label );
}
