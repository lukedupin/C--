#ifndef __ASSIGN_NODE_H__
#define __ASSIGN_NODE_H__

/** \class AssignNode
    \brief A class for function, parameter, and variable declarations.
*/
#include "node.h"

class AssignNode : public Node
{
  protected:

  public:
    //Setup my variable
  AssignNode (int tokenValue, int lineNo, const char* label, const char* cat);

    //Overide the default code gen function
  virtual void codeGen( bool siblings = true );

  protected:
    //! \brief Prinout of myself and any other node
  void printMyself( int depth = 0 );

};

#endif
