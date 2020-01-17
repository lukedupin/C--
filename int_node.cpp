#include "int_node.h"

  //Setup my int node
IntNode::IntNode( int token, int line, const char* l, int num, const char* cat )
  : Node( token, line, l, cat )
{
  m_Value = num;
}

  //Generate my code
void IntNode::codeGenPreChild()
{
    //IF we have a register to load oursevles into, then do so
  if ( m_Result_Reg >= 0 && m_Result_Reg < REGISTER_COUNT )
  {
    if ( m_Value > 0xFFFF )
      writeLine("LDMSW %d", "Load value in two parts, MSB", m_Value >> 16);
    writeLine("LDVAL %d, %d", "Store %d to Reg%d",
              m_Result_Reg, (m_Value & 0xFFFF), m_Value, m_Result_Reg );
  }
}

  //Print out what we are
void IntNode::printMyself( int depth )
{
  printIndent( depth );
  printf("%s: %d\n", m_Label, Number );
}
