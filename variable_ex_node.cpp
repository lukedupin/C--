#include "variable_ex_node.h"
#include "j_token.h"
#include "parser.tab.h"
#include "string.h"

  //Test run
#define VAR_EQ( x, y ) (strcasecmp( Variables[x]->getName(), y ) == 0)

  //Setup my variable
VariableExNode::VariableExNode (int tokenValue, int lineNo)
  : Node(tokenValue, lineNo, "Variable", "Id Ex: "),
  Idx(0)
{
}

  //Returns the code of the variable ex
int VariableExNode::getExCode()
{
  int type = -1;
  int base = -1;
  int code = -1;

    //Figure out what kind of call I am
  if      ( VAR_EQ( 0, "controller" ) )  type = 0x0000;
  else if ( VAR_EQ( 0, "console" ) )     type = 0x1000;

    //We found that we are dealing with a controller
  if ( type >= 0 )
  {
      //Define my possible sub actions
    if      ( VAR_EQ( 1, "a" ) )           base = 0x0000;
    else if ( VAR_EQ( 1, "b" ) )           base = 0x0100;
    else if ( VAR_EQ( 1, "y" ) )           base = 0x0200;
    else if ( VAR_EQ( 1, "x" ) )           base = 0x0300;

      //PS3
    else if ( VAR_EQ( 1, "cross" ) )       base = 0x0000;
    else if ( VAR_EQ( 1, "circle" ) )      base = 0x0010;
    else if ( VAR_EQ( 1, "triangle" ) )    base = 0x0020;
    else if ( VAR_EQ( 1, "square" ) )      base = 0x0030;

    else if ( VAR_EQ( 1, "start" ) )       base = 0x0040;
    else if ( VAR_EQ( 1, "select" ) )      base = 0x0050;
    else if ( VAR_EQ( 1, "guide" ) )       base = 0x0060;
    else if ( VAR_EQ( 1, "dpadLeft" ) )    base = 0x0070;
    else if ( VAR_EQ( 1, "dpadUp" ) )      base = 0x0080;
    else if ( VAR_EQ( 1, "dpadRight" ) )   base = 0x0090;
    else if ( VAR_EQ( 1, "dpadDown" ) )    base = 0x00A0;

    else if ( VAR_EQ( 1, "leftStick" ) )   base = 0x00B0;
    else if ( VAR_EQ( 1, "RightStick" ) )  base = 0x00C0;

    else if ( VAR_EQ( 1, "rb" ) )          base = 0x00D0;
    else if ( VAR_EQ( 1, "rt" ) )          base = 0x00E0;
    else if ( VAR_EQ( 1, "lb" ) )          base = 0x00F0;
    else if ( VAR_EQ( 1, "lt" ) )          base = 0x0100;
  
      //If we have a button, figure out what the sub category is
    if ( base >= 0 )
    {
      if ( Idx <= 2 ) code = type + base + 0x00;
        //Sub items
      else if ( VAR_EQ( 2, "pressed" ) )  code = type + base + 0x01;
      else if ( VAR_EQ( 2, "released" ) ) code = type + base + 0x02;
      else if ( VAR_EQ( 2, "up" ) )       code = type + base + 0x03;
      else if ( VAR_EQ( 2, "down" ) )     code = type + base + 0x04;
      else
      {
        Error_Count++;
        fprintf(stderr, "Unknown Variable %s, try another name %d\n", 
                Variables[2]->getName(), m_LineNo);
        return -1;
      }

      return code;
    }

      //Define my possible sub actions
    if      ( VAR_EQ( 1, "LeftStickX" ) )  base = 0x0110;
    else if ( VAR_EQ( 1, "LeftStickY" ) )  base = 0x0120;
    else if ( VAR_EQ( 1, "RightStickX" ) ) base = 0x0130;
    else if ( VAR_EQ( 1, "RightStickY" ) ) base = 0x0140;

      //If we have a stick x/y, figure out the sub category
    if ( base >= 0 )
    {
      code = type + base + 0x00;
      return code;
    }

      //Error out
    Error_Count++;
    fprintf(stderr, "Unknown Variable, try Controller %d\n", m_LineNo);
    return -1;
  }

    //Figure out what kind of call I am
  if      ( VAR_EQ( 0, "system" ) )      type = 0x2000;

    //We found that we are dealing with a controller
  if ( type >= 0 )
  {
      //Define my possible sub actions
    if      ( VAR_EQ( 1, "tick" ) )      base = 0x0000;

      //If we have a button, figure out what the sub category is
    if ( base >= 0 )
    {
      if ( Idx == 2 ) code = type + base + 0x00;
        //Sub items
      else
      {
        Error_Count++;
        fprintf(stderr, "Unknown Variable %s, try another name %d\n", 
                Variables[2]->getName(), m_LineNo);
        return -1;
      }

      return code;
    }

      //Error out
    Error_Count++;
    fprintf(stderr, "Unknown Variable, try Controller %d\n", m_LineNo);
    return -1;
  }

    //Couldn't find the base type
  Error_Count++;
  fprintf(stderr, "Unknown Variable, try Controller %d\n", m_LineNo);
  return -1;
}

  //Define my code generate, which there is none for me
void VariableExNode::codeGenPreChild()
{
  int code = getExCode();

    //If we are in read mode, just load the value
  if ( m_Read_Mode )
  {
    writeLine("LDEX %d, %d", "Loading %s into Reg%d",
              m_Result_Reg, code, getName(), m_Result_Reg );
    return;
  }

    //Else we are in write mode Figure out what is wanted of us
  switch ( m_Parent->getTokenType() )
  {
      //Assign my result register onto myself
    case ASSIGN:
      writeLine("STREX %d, %d", "Store Reg%d to %s",
                m_Result_Reg, code, m_Result_Reg, getName() );

      break;

      //Assign a constant value
    case ASSIGN_CONST:
      m_Result_Reg = claimRegister();

        //Load my constant into a register
      if ( m_Value > 0xFFFF )
        writeLine("LDMSW %d", "Load value in two parts, MSB", m_Value >> 16);
      writeLine("LDVAL %d, %d", "Store %d to %s",
                m_Result_Reg, (m_Value % 0x10000), m_Value, getName() );

        //Store the value back into the reg ex
      writeLine("STREX %d, %d", "Store Reg%d to %s",
                m_Result_Reg, code, m_Result_Reg, getName() );
      releaseRegister( m_Result_Reg );
      break;

      //Load my variable into the register provided
    default:
      break;
  }
}

  //Detect an error
void VariableExNode::codeDetectMyself()
{
      //Store my variable into the list
  if ( Idx <= 1 )
  {
    Error_Count++;
    fprintf(stderr, "Variable Ex doesn't have enough nodes at line %d\n", 
            m_LineNo);
    return;
  }

    //Do a test run for validity
  getExCode();
}

  //Add a variable to the variable EX
void VariableExNode::addVariable( VariableNode* var )
{
    //Error if we have too many 
  if ( Idx >= MAX_VAR_COUNT )
  {
    Error_Count++;
    fprintf(stderr, "Too many variables added to the variable ex\n");
    return;
  }

    //Add the variable
  Variables[Idx++] = var;
}

  //Returns the name of the variable ex
const char* VariableExNode::getName()
{
  if ( Idx == 0 ) strcpy( Buffer, "" );
  else if ( Idx == 1 ) snprintf(Buffer, sizeof(Buffer), "%s", 
                                Variables[0]->getName() );
  else if ( Idx == 2 ) snprintf(Buffer, sizeof(Buffer), "%s.%s", 
                                Variables[0]->getName(),
                                Variables[1]->getName() );
  else if ( Idx == 3 ) snprintf(Buffer, sizeof(Buffer), "%s.%s.%s", 
                                Variables[0]->getName(),
                                Variables[1]->getName(),
                                Variables[2]->getName() );
  else if ( Idx == 4 ) snprintf(Buffer, sizeof(Buffer), "%s.%s.%s.%s", 
                                Variables[0]->getName(),
                                Variables[1]->getName(),
                                Variables[2]->getName(),
                                Variables[3]->getName() );

  return Buffer;
}

  //Print out my name
void VariableExNode::printMyself( int depth )
{
    //Print out the variable
  printIndent( depth );
  printf( "VariableEx: %s [0x%04X]\n", getName(), getExCode() );
}
