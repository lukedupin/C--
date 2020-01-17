#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "node.h"

  //Define my local variable to detect and zero any static variables
bool First_Run = true;

  //Define my static variable
FILE* Node::Code_Output = stdout;

  //Setup my variable list
std::map<std::string, int> Node::Var_List;

  //Set that we have no errors
int Node::Error_Count = 0;

  //Holds the current size of the program
int Node::Program_Len = 0;

  //! \brief Required for the linker
bool Node::Register_Used[Node::REGISTER_COUNT] = { false };

  //! \brief Required for the linker
std::string Node::Program[Node::MAX_PROG_SIZE];

  //! \brief Required for the linker
std::string Node::Program_Comment[Node::MAX_PROG_SIZE];

  //Define my node
Node::Node( int token, int lineNo, const char * label, const char * category )
    : m_Token(token),
      m_LineNo(lineNo),
      m_Label(label),
      m_Sibling(NULL),
      m_Parent(NULL),
      m_Category(category),
      m_Result_Reg(-1),
      m_Value(0),
      m_Read_Mode( true )
{
  int i;

  for ( i = 0; i < MAX_CHILDREN; ++i )
    m_Children[i] = NULL;

    //Quit if this isn't the first run
  if ( !First_Run ) 
    return;

    //Zero out my static arrays
  for ( i = 0; i < REGISTER_COUNT; i++ )
    Register_Used[i] = false;

      //Ensure we don't run this part again
  First_Run = false;
}

  //Define the code output
void Node::setCodeOutput( FILE* code )
{
  Code_Output = code;
}

  //Define the child
Node* Node::setChild( int child, Node* node )
{
  if ( child < MAX_CHILDREN )
  {
    if (m_Children[child] == NULL)
    {
      node->m_Parent = this;
      m_Children[child] = node;
    }
    else
      printf("Child %d set twice.  Set at %d\n", child, m_LineNo);
  }
  else
    printf("Too many children: line %d.  Requested child: %d\n", m_LineNo, child);

  return this;
}

  //Return a child node
Node* Node::getChild( int child )
{
  return m_Children[child];
}

  //Return the sibling
Node* Node::setSibling( Node* sibling )
{
  if ( m_Sibling != NULL )
  {
    Node* sib = m_Sibling;

      //Skip to the last sibling
    while ( sib->m_Sibling != NULL )
      sib = sib->m_Sibling;

    sib->m_Sibling = sibling;
  }
  else
    m_Sibling = sibling;

    //Define the parent
  sibling->m_Parent = m_Parent;

  return this;
}

  //Return the sibling
Node* Node::getSibling()
{
  return m_Sibling;
}

  //! \brief Returns the number of errors detected
int Node::getErrorCount()
{
  return Error_Count;
}

  //! \brief Get the line number of this node
int Node::getLineNo() 
{
  return m_LineNo;
}

  //! \brief Return my token type
int Node::getTokenType()
{
  return m_Token;
}

  //! \brief Return the label of this 
const char* Node::getLabel()
{
  return m_Label;
}

  //! \brief Return the category
const char* Node::getCategory()
{
  return m_Category;
}

  //Dump the code
void Node::codeGen( bool siblings )
{
    //Pre child call
  codeGenPreChild();

      //Test the kids
  for (int i = 0; i < MAX_CHILDREN; ++i)
    if ( m_Children[i] != NULL )
      m_Children[i]->codeGen();

    //Post child call
  codeGenPostChild();

    //Test the sibling
  if ( siblings && m_Sibling != NULL )
    m_Sibling->codeGen();
}

  //Detect errors
void Node::codeDetectErrors()
{
    //Test myself first
  codeDetectMyself();

      //Test the kids
  for (int i = 0; i < MAX_CHILDREN; ++i)
    if ( m_Children[i] != NULL )
      m_Children[i]->codeDetectErrors();

    //Test the sibling
  if ( m_Sibling != NULL )
    m_Sibling->codeDetectErrors();
}

  //Sets the register
bool Node::setRegister( int reg )
{
    //Ensure the register is valid
  if ( reg < 0 )//|| reg >= REGISTER_COUNT )
    return false;

    //Set the register
  m_Result_Reg = reg;
  return true;
}

  //Returns the register result value
int Node::getRegister()
{
  return m_Result_Reg;
}

  //set the value variable
void Node::setValue( int value )
{
  m_Value = value;
}

  //Reads the value variable
int Node::getValue()
{
  return m_Value;
}

  //Sets if we are read or write mode
void Node::setReadMode( bool read )
{
  m_Read_Mode = read;
}

  //Returns the read mode
bool Node::getReadMode()
{
  return m_Read_Mode;
}


  //Default error detection does nothing
void Node::codeDetectMyself()
{
}

  //! \brief Generate code before the child
void Node::codeGenPreChild()
{
}

  //! \brief Generate code after the child
void Node::codeGenPostChild()
{
}

  //! \brief print out this node and anyone else
void Node::printMyself( int depth )
{
  (void)depth;
}

  //Store a line to the program
int Node::writeLine( const char* line, const char* comment, ... )
{
  char pad[32];
  char format[1024];
  char buf[1024];
  va_list ap;
  int i, len;

    //Fail if we have no more room
  if ( Program_Len >= MAX_PROG_SIZE )
    return -1;

    //Setup the format
  va_start( ap, comment );
  len = vsnprintf( format, sizeof(format), line, ap );
  va_end( ap );

    //Setup my thing
  memset( pad, ' ', sizeof(pad) );
  pad[((20 > len)? 20 - len: 1)] = 0;
  snprintf( format, sizeof(format), "%s%s#%s", line, pad, comment );

    //Write my line to the end
  va_start( ap, comment );
  vsnprintf( buf, sizeof(buf), format, ap );
  va_end( ap );

    //Write my line
  Program[Program_Len] = buf;

  return Program_Len++;
}


  //Store a line to the program
int Node::writeLine( int idx, const char* line, const char* comment, ... )
{
  char pad[32];
  char format[1024];
  char buf[1024];
  va_list ap;
  int i, len;

    //Fail if we have no more room
  if ( idx > Program_Len )
    return -1;

    //Setup the format
  va_start( ap, comment );
  len = vsnprintf( format, sizeof(format), line, ap );
  va_end( ap );

    //Setup my thing
  memset( pad, ' ', sizeof(pad) );
  pad[((20 > len)? 20 - len: 1)] = 0;
  snprintf( format, sizeof(format), "%s%s#%s", line, pad, comment );

    //Write my line to the end
  va_start( ap, comment );
  vsnprintf( buf, sizeof(buf), format, ap );
  va_end( ap );

    //Write my line
  Program[idx] = buf;
  return idx;
}

  //! \brief Add a line to a specific spot
int Node::commentLine( const char* comment, ... )
{
  char buf[1024];
  va_list ap;

    //Write my line to the end
  va_start( ap, comment );
  vsnprintf( buf + 1, sizeof(buf) - 1, comment, ap );
  buf[0] = '#';
  va_end( ap );

    //Write my line
  Program_Comment[Program_Len] = buf;
  return Program_Len;
}

  //! \brief Add a line to a specific spot
int Node::commentLine( int idx, const char* comment, ... )
{
  char buf[1024];
  va_list ap;

    //Fail if we have no more room
  if ( idx > Program_Len )
    return -1;

    //Write my line to the end
  va_start( ap, comment );
  vsnprintf( buf, sizeof(buf), comment, ap );
  va_end( ap );

    //Write my line
  Program_Comment[idx] = buf;
  return idx;
}

  //Claims an empty register value
int Node::claimRegister()
{
    //Find an empty register
  for ( int i = 0; i < REGISTER_COUNT; i++ )
    if ( !Register_Used[i] )
    {
      Register_Used[i] = true;
      return i;
    }

  return -1;
}

  //Give back a register
bool Node::releaseRegister( int idx )
{
    //Fail if idx isn't a register
  if ( idx < 0 || idx >= REGISTER_COUNT )
    return false;
  
    //Tell the user if this was a register
  bool result = Register_Used[idx];

    //Clear the register and return if it was used
  Register_Used[idx] = false;
  return result;
}

  //Print out my nodes
void Node::print( int depth )
{
    //Print myself
  printMyself( depth );
  printChildren( depth );
  printSibling( depth );
}

  //print out the children
void Node::printChildren( int depth )
{
  for (int i = 0; i < MAX_CHILDREN; ++i)
  {
      //Skip to the next child
    if (m_Children[i] == NULL) continue;
    
      //Print out the child
    printIndent( depth );
    printf("Child: %d\n", i+1);
    m_Children[i]->print( depth + 1 );
  }
}

  //Print out the sibling
void Node::printSibling( int depth )
{
    //If we have a sibling print it out
  if ( m_Sibling != NULL )
    m_Sibling->print( depth );

  return;
}

  //Print out my indent
void Node::printIndent( int depth )
{
  while ( depth-- >= 0 )
    printf("  ");
}
