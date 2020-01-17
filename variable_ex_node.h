#ifndef __VARIABLE_EX_NODE_H__
#define __VARIABLE_EX_NODE_H__

/** \class VariableExNode
    \brief A class which handles extended variables
*/
#include "node.h"
#include "variable_node.h"

class VariableExNode : public Node
{
  public:
    //! \brief Defines the max variable count
  static const int MAX_VAR_COUNT = 4;

  protected:
    //! \brief defines, this variables name
  VariableNode* Variables[MAX_VAR_COUNT];

    //! \brief Holds the current index
  int Idx;

    //! \brief A buffer to hold the name of my variable ex
  char Buffer[512];

  public:
    //Setup my variable
  VariableExNode (int tokenValue, int lineNo );

    //! \brief Add a variable to my ex
  void addVariable( VariableNode* var );

    //! \brief Returns the name of the variable ex
  const char* getName();
  

  protected:
    //! \brief Returns the code of this variable
  int getExCode();

    //! \brief return the code gen
  void codeGenPreChild();

    //! \brief Detects variables that aren't defined
  void codeDetectMyself();

    //! \brief Prinout of myself and any other node
  void printMyself( int depth = 0 );

};// class VariableNode

#endif
