#ifndef PROGRAM_NODE_H
#define PROGRAM_NODE_H

#include "node.h"

  //! \brief Defines my program node, the top node
class ProgramNode : public Node
{
  public:
    //! \brief Setup the program node
  ProgramNode();

    //! \brief Output the program
  void writeProgram();

  protected:
    //! \brief Generate a full program
  void codeGenPreChild();

    //! \brief Print out the program
  void printMyself( int depth = 0 );
};

#endif
