#ifndef TYPE_NODE_H
#define TYPE_NODE_H

#include "node.h"

  //! \brief Defines the type node
class TypeNode : public Node
{
  public:
    //! \brief Define my type node
  TypeNode( int token, int line, const char* label, const char* cat );

  protected:
    //! \brief Defines my print statement
  void printMyself( int depth );
};

#endif
