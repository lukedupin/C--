#ifndef __NODE_H__
#define __NODE_H__

#include <sstream>
#include <vector>

#include "error.h"

using namespace std;

class Node
{
    protected:
    //Facts about this node
    int _token = -1;
    int _lineNumber = 0;
    const char* _label = nullptr;

    public:
    std::vector<Node*> Children;
    Node* Sibling = nullptr;

    public:
    // Init my node
    Node( int tokenValue, int lineNo, const char * label = nullptr );

    //Read only for my data
    int tokenType();
    int lineNumber();
    const char* label();

    //*** Common functions the node uses to call into the child object

    // generate code for this node
    bool codeGen( ostringstream* stream, int depth = 0 );

    // Detects errors in the code
    bool detectErrors( Error* err );

    //Dup the symbol tree for debug
    void codePrint( int depth = 0 );

    //*** Child specific implementions
    protected:

    //Detect errors
    virtual bool calculateErrors( Error* err );

    // Pre child code gen
    virtual bool codeGenPreChild( ostringstream* stream, int depth );

    // Pre child code gen
    virtual bool codeGenPostChild( ostringstream* stream, int depth );

    // Return true if we are increasing scope depth
    virtual bool increaseScopeDepth();

    // print out this node and anyone else
    virtual void print( int depth );
};

#endif
