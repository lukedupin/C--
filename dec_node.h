#ifndef __DECNODE_H__
#define __DECNODE_H__

/** \class DecNode
    \brief A class for function, parameter, and variable declarations.
*/
#include "node.h"

class DecNode : public Node
{
  protected:
    //! \brief defines, this variables name
  const char*     Name;

    //! \brief Defines the current number of variables in use
  static int      Var_Count;

  public:
    //Setup my variable
  DecNode (int tokenValue, int lineNo, const char* name);

  protected:
    //! \brief Detects multiple declaration of a variable
  void codeDetectMyself();

    //! \brief Prinout of myself and any other node
  void printMyself( int depth = 0 );

};// class DecNode

#endif
