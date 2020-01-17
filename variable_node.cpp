#include "variable_node.h"
#include "j_token.h"
#include "parser.tab.h"

  //Setup my variable
VariableNode::VariableNode (int tokenValue, int lineNo, const char* name)
  : Node(tokenValue, lineNo, name, "Id: "),
  Name( name )
{
}

  //Define my code generate, which there is none for me
void VariableNode::codeGenPreChild()
{
  int tmp;

    //Figure out what is wanted of us
  switch ( m_Parent->getTokenType() )
  {
      //Assign my result register onto myself
    case ASSIGN:
      tmp = getRegister();

          //Figure out which way we are pushing ourselves
      if ( m_Read_Mode )
        writeLine("LD %d, %d", "Store %s into Reg%d",
                  m_Result_Reg, tmp, Name, m_Result_Reg );
      else
        writeLine("LD %d, %d", "Store Reg%d to %s",
                  tmp, m_Result_Reg, m_Result_Reg, Name );
      break;

      //Assign a constant value
    case ASSIGN_CONST:
      tmp = getRegister();
      if ( m_Value > 0xFFFF )
        writeLine("LDMSW %d", "Load value in two parts, MSB", m_Value >> 16);
      writeLine("LDVAL %d, %d", "Store %d to %s",
                tmp, (m_Value & 0xFFFF), m_Value, Name );
      break;

    default:
      break;
  }
}

  //Detect an error
void VariableNode::codeDetectMyself()
{
      //Store my variable into the list
  if ( Var_List.find( Name ) == Var_List.end() )
  {
    Error_Count++;
    fprintf(stderr, "Undefined variable: %s at line %d\n", Name, m_LineNo );
  }
}

  //Returns the name
const char* VariableNode::getName()
{
  return Name;
}

  //Returns the variable number
int VariableNode::getRegister()
{
  int id = -1;

      //Store my variable into the list
  if ( Var_List.find( Name ) != Var_List.end() )
    id = Var_List[Name];

  return id;
}

  //Print out my name
void VariableNode::printMyself( int depth )
{
  int id = -1;

      //Store my variable into the list
  if ( Var_List.find( Name ) != Var_List.end() )
    id = Var_List[Name];

    //Print out the variable
  printIndent( depth );
  printf( "Variable: %s [%d]\n", Name, id);
}
