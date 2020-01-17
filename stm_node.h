#ifndef STM_NODE_H
#define STM_NODE_H

#include "node.h"

  //! \brief Define a statement node, only useful for breaks and returns
class StmNode : public Node
{
  public:
    //! \brief Define my statement node object
  StmNode( int token, int line, const char* label );

  protected:
    //! \brief Defines my code generation, if any
  void codeGenPreChild();

    //! \brief Defines my print statement
  void printMyself( int depth );
};

#endif
