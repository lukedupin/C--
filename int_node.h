#ifndef INT_NODE_H
#define INT_NODE_H

#include "node.h"

  //! \brief Defines the type node
class IntNode : public Node
{
  protected:
    //! \brief Defines my numerica value
  int Number;

  public:
    //! \brief Define my type node
  IntNode( int token, int line, const char* label, int num, const char* cat );

  protected:
    //! \brief Define my code generation
  void codeGenPreChild();

    //! \brief Defines my print statement
  void printMyself( int depth );
};

#endif
