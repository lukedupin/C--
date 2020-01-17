#ifndef __CONDITIONAL_NODE_H__
#define __CONDITIONAL_NODE_H__

/** \class ConditionalNode
    \brief A class for function, parameter, and variable declarations.
*/
#include "node.h"

class ConditionalNode : public Node
{
  protected:

  public:
    //Setup my variable
  ConditionalNode (int token, int lineNo, const char* label);

    //Override the code gen function
  virtual void codeGen( bool siblings = true );

  protected:
    //! \brief Prinout of myself and any other node
  void printMyself( int depth = 0 );

};

#endif
