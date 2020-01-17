#ifndef __NODE_H__
#define __NODE_H__

#include <stdio.h>

#include <string>
#include <map>

/** \class Node
    \brief Pure virtual base class from which all nodes of the parse tree are derived.
*/

class Node
{
  public:
    //! \brief The number of children you can hold
  static const int MAX_CHILDREN = 3;

    //! \brief Holds the max size of a program
  static const int MAX_PROG_SIZE = 16384;

    //! \brief Holds the max number of registers
  static const int REGISTER_COUNT = 16;

    //! \brief Holds the max number of variables a user can have
  static const int VARIABLE_COUNT = 256 - REGISTER_COUNT;

    //! \brief Returns the number of errors detected
  static int getErrorCount();

  protected:
    //! \brief Defines my output means for the code
  static FILE* Code_Output;

    //! \brief Defines the variable map
  static std::map<std::string, int> Var_List;

    //! \brief Defines the number of errors we detected
  static int Error_Count;

    //! \brief Holds the entire program
  static std::string Program[MAX_PROG_SIZE];

    //! \brief Holds a ASM comment line if there is one
  static std::string Program_Comment[MAX_PROG_SIZE];

    //! \brief Holds the current program size
  static int Program_Len;

    //! \brief Holds my used registers
  static bool Register_Used[REGISTER_COUNT];

  public:
    //! \brief Init my node
  Node( int tokenValue, int lineNo, const char * label, const char * category );

    //! \brief Defines my code output
  void setCodeOutput( FILE* code );

    //! \brief define the child node
  Node* setChild( int childNum, Node* child );

    //! \brief Get the child node
  Node* getChild( int childNum );

    //! \brief Define my sibling
  Node* setSibling( Node * sibling );

    //! \brief return my sibling
  Node* getSibling();

    //! \brief Get the line number of this node
  int getLineNo();

    //! \brief Return my token type
  int getTokenType();

    //! \brief Return the label of this 
  const char* getLabel();

    //! \brief Return the category
  const char* getCategory();

    //! \brief print out this node and anyone else
  void print( int depth = 0 );

    //! \brief generate code for this node
  virtual void codeGen( bool siblings = true );

    //! \brief Detects errors in the code
  virtual void codeDetectErrors();

    //! \brief Sets the result register value
  virtual bool setRegister( int reg );

    //! \brief Returns the register/variable number for this node
  virtual int getRegister();

    //! \brief Sets the value variable
  virtual void setValue( int value );

    //! \brief Reads the value variable
  virtual int getValue();

    //! \brief Set that the node is read or write mode, used for assigning
  virtual void setReadMode( bool read );

    //! \brief Set that the node is read or write mode, used for assigning
  virtual bool getReadMode();

  protected:
    //Define my local variables
  int             m_Token;
  int             m_LineNo;
  Node*           m_Children[MAX_CHILDREN];
  Node*           m_Sibling;
  Node*           m_Parent;
  const char*     m_Category;
  const char*     m_Label;
  int             m_Result_Reg;
  int             m_Value;
  bool            m_Read_Mode;

    //! \brief Add a line of ASM to the program
  int writeLine( const char* str, const char* comment, ... );

    //! \brief Add a line to a specific spot
  int writeLine( int idx, const char* str, const char* comment, ... );

    //! \brief Add a line to a specific spot
  int commentLine( const char* comment, ... );

    //! \brief Add a line to a specific spot
  int commentLine( int idx, const char* comment, ... );

    //! \brief Takes an empty register, returns -1 if none is avaliable
  int claimRegister();

    //! \brief Releases a register to be used for something else
  bool releaseRegister( int idx );

    //! \brief Detects if there is an error in this node
  virtual void codeDetectMyself();

    //! \brief Generate code before the child
  virtual void codeGenPreChild();

    //! \brief Generate code after the child
  virtual void codeGenPostChild();

    //! \brief print out this node and anyone else
  virtual void printMyself( int depth );

      //Print out stuff
  void printChildren( int depth );
  void printSibling( int depth );
  void printIndent( int depth );
};// class Node

#endif
