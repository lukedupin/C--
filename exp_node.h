#ifndef __EXP_NODE_H__
#define __EXP_NODE_H__

/** \class ExpNode
    \brief A class for function, parameter, and variable declarations.
*/
#include "node.h"

class ExpNode : public Node
{
  protected:
    //! \brief Holds the registers used for generating code
  int Arg[2];

  public:
    //Setup my variable
  ExpNode (int tokenValue, int lineNo, const char* label, const char* cat);

  protected:
    //! \brief return the code gen
  void codeGenPreChild();

    //! \brief return the code gen
  void codeGenPostChild();

    //! \brief Prinout of myself and any other node
  void printMyself( int depth = 0 );

};

#endif
