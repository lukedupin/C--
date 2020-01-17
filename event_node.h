#ifndef __EVENT_NODE_H__
#define __EVENT_NODE_H__

/** \class ConditionalNode
    \brief Defines a logic based statement
*/
#include "conditional_node.h"

class EventNode : public ConditionalNode
{
  private:
    //! \brief Holds the top index of the event
  int Event_Idx;

  public:
    //Setup my variable
  EventNode (int tokenValue, int lineNo);

    //Overide the conditional code gen func
  virtual void codeGen( bool siblings = true );

  protected:
    //! \brief return the code gen
  virtual void codeGenPreChild();

    //! \brief return the code gen
  virtual void codeGenPostChild();

    //! \brief Prinout of myself and any other node
  void printMyself( int depth = 0 );

};

#endif
