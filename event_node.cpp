#include "event_node.h"
#include "j_token.h"
#include "parser.tab.h"

  //Define an event
EventNode::EventNode( int token, int line )
  : ConditionalNode( token, line, "Event" )
{
}

  //Override the code gen to first print my event entry
void EventNode::codeGen( bool siblings )
{
    //Gerenate my if statement
  codeGenPreChild();

    //If we are an init, there is no expression, so just call the event
  if ( m_Token == INIT )
    m_Children[1]->codeGen();
  else
    ConditionalNode::codeGen( false );

    //Generate my closing call
  codeGenPostChild();

      //Dump siblings
  if ( siblings && m_Sibling != NULL )
    m_Sibling->codeGen();
}

  //Dump out my event entry tag
void EventNode::codeGenPreChild()
{
  //Output the code generation for an event
  commentLine( "Event Entry point" );
  Event_Idx = writeLine("HOLD PLACE", "");
}

  //Dump out my event entry tag
void EventNode::codeGenPostChild()
{
    //Write out the event length
  switch ( m_Token )
  {
    case INIT:
      writeLine(Event_Idx, "INIT %d", "System init event", Program_Len ); 
      break;

    case PRE_EVENT:
      writeLine(Event_Idx, "PRE_EVT %d", "Event entry point, runs before trans",
                Program_Len );
      break;

    case POST_EVENT:
      writeLine(Event_Idx, "POST_EVT %d", "Event entry point, runs after trans",
                Program_Len );
      break;

    default:
    case EVENT:
      writeLine(Event_Idx, "EVT %d", "Event entry point", Program_Len ); 
      break;
  }

    //Output the code generation for an event
  writeLine( "NOP", "Event termination" ); 
}

  //Tell the user we have an event
void EventNode::printMyself( int depth )
{
  printIndent( depth );
  printf( "Event Entry:\n" );
}
