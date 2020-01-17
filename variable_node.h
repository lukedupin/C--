#ifndef __VARIABLE_NODE_H__
#define __VARIABLE_NODE_H__

/** \class VariableNode
    \brief A class for function, parameter, and variable declarations.
*/
#include "node.h"

class VariableNode : public Node
{
  protected:
    //! \brief defines, this variables name
  const char*     Name;

  public:
    //Setup my variable
  VariableNode (int tokenValue, int lineNo, const char* name);

    //! \brief Returns the name of the variable
  const char* getName();

    //! \brief Returns the variable number for this node
  int getRegister();

  protected:
    //! \brief return the code gen
  void codeGenPreChild();

    //! \brief Detects variables that aren't defined
  void codeDetectMyself();

    //! \brief Prinout of myself and any other node
  void printMyself( int depth = 0 );

};// class VariableNode

#endif
