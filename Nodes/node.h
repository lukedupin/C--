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
    bool codeGen( QTextStream* stream, QVector<Node*>* stack = nullptr, int scope_depth = 0 );

    // Detects errors in the code
    bool detectErrors( Error* err, QVector<Node*>* stack = nullptr );

    //Dup the symbol tree for debug
    void codePrint( QVector<Node*>* stack = nullptr, int scope_depth = 0 );

    //*** Child specific implementions
    protected:

    //Detect errors
    virtual bool calculateErrors( Error* err, QVector<Node*>* stack = nullptr );

    // Pre child code gen
    virtual bool codeGenPreChild( QTextStream* stream, QVector<Node*>* stack, int scope_depth );

    // Pre child code gen
    virtual bool codeGenPostChild( QTextStream* stream, QVector<Node*>* stack, int scope_depth );

    // Return true if we are increasing scope depth
    virtual bool increaseScopeDepth();

    // print out this node and anyone else
    virtual void print( int scope_depth );
};

#endif
