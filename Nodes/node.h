#ifndef __NODE_H__
#define __NODE_H__

#include <QTextStream>
#include <QVector>

#include "error.h"

class Node
{
    protected:
    //Facts about this node
    int _token = -1;
    int _lineNumber = 0;
    QString _label;

    public:
    QVector<Node*> Children;
    Node* Sibling = nullptr;

    public:
    // Init my node
    Node( int tokenValue, int lineNo, QString label = QString() );

    //Read only for my data
    int tokenType();
    int lineNumber();
    QString label();

    //*** Common functions the node uses to call into the child object

    // generate code for this node
    bool codeGen( QTextStream* stream, int depth = 0 );

    // Detects errors in the code
    bool detectErrors( Error* err );

    //Dup the symbol tree for debug
    void codePrint( int depth = 0 );

    //*** Child specific implementions
    protected:

    //Detect errors
    virtual bool calculateErrors( Error* err );

    // Pre child code gen
    virtual bool codeGenPreChild( QTextStream* stream, int depth );

    // Pre child code gen
    virtual bool codeGenPostChild( QTextStream* stream, int depth );

    // Return true if we are increasing scope depth
    virtual bool increaseScopeDepth();

    // print out this node and anyone else
    virtual void print( int depth );
};

#endif
