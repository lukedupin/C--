#ifndef __NODE_H__
#define __NODE_H__

#include <stdio.h>

#include <string>
#include <map>
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
    const char* _category = nullptr;

    public:
    std::vector<Node*> Children;
    Node* Sibling = nullptr;

    public:
    // Init my node
    Node( int tokenValue, int lineNo, const char * label, const char * category );

    //Read only for my data
    int tokenType();
    int lineNumber();
    const char* label();
    const char* category();

    //*** Common functions the node uses to call into the child object

    // generate code for this node
    string codeGen( int depth = 0 );

    // Detects errors in the code
    bool detectErrors( Error* err );

    //Dup the symbol tree for debug
    void codePrint( int depth = 0 );

    //*** Child specific implementions
    protected:

    //Detect errors
    virtual bool calculateErrors( Error* err );

    // Pre child code gen
    virtual string codeGenPreChild( int depth );

    // Pre child code gen
    virtual string codeGenPostChild( int depth );

    // print out this node and anyone else
    virtual void print( int depth = 0 );
};

#endif
