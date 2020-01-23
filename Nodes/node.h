#ifndef NODE_H
#define NODE_H

#include <QTextStream>
#include <QVector>

#include "error.h"
#include "context.h"

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

    virtual ~Node();

    //Read only for my data
    int tokenType();
    int lineNumber();
    QString label();

    //*** Common functions the node uses to call into the child object

    // generate code for this node
    bool codeGen( QTextStream* stream, Context* context );

    // Detects errors in the code
    bool detectErrors( Error* err, Context* context );

    //Dup the symbol tree for debug
    void codePrint( Context* context );

    //Iterate over children with custom callback on each
    void iterateChildren( Context* context, std::function<void (Node*)> callback );

    //*** Child specific implementions
    protected:

    //Detect errors
    virtual bool calculateErrors( Error* err, Context* context );

    // Pre child code gen
    virtual bool codeGenPreChild( QTextStream* stream, Context* context );

    // Pre child code gen
    virtual bool codeGenPostChild( QTextStream* stream, Context* context );

    // Return true if we are increasing scope depth
    virtual bool increaseScopeDepth();

    // print out this node and anyone else
    virtual void print( int scope_depth );
};

#endif
