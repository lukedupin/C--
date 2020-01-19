#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "node.h"

  //Define my node
Node::Node( int token, int lineNo, const char * label, const char * category )
    : _token(token),
      _lineNumber(lineNo),
      _label(label),
      _category(category)
{
}

//Get some info
int Node::lineNumber() { return _lineNumber; }
int Node::tokenType() { return _token; }
const char* Node::label() { return _label; }
const char* Node::category() { return _category; }

  //Dump the code
void Node::codeGen( int depth, bool siblings )
{
    //Pre child call
    codeGenPreChild( depth );

    //Test the kids
    for ( auto& node : Children )
        node->codeGen( depth );

    //Post child call
    codeGenPostChild( depth );

    //Test the sibling
    if ( Sibling != nullptr )
        Sibling->codeGen( depth );
}

  //Detect errors
void Node::detectErrors( Error* err )
{
    //Pre child call
    calculteErrors( err );

    //Test the kids
    for ( auto& node : Children )
        node->calculteErrors( err );

    //Test the sibling
    if ( Sibling != nullptr )
        Sibling->calculteErrors( err );
}

  //Print out my nodes
void Node::codePrint( int depth )
{
    //Pre child call
    print( depth );

    //Test the kids
    for ( auto& node : Children )
        node->print(depth);

    //Test the sibling
    if ( Sibling != nullptr )
        Sibling->print(depth);
}

bool Node::calculteErrors( Error* err )
{
    return true;
}

string Node::codeGenPreChild( int depth )
{
    return string();
}

string Node::codeGenPostChild( int depth )
{
    return string();
}

  //print out the children
void Node::print( int depth )
{
}
