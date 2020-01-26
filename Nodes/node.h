#ifndef NODE_H
#define NODE_H

#include <QTextStream>
#include <QVector>

#include "error.h"
#include "context.h"

class Node
{
    public:
    struct SemanticType {
        QString TargetType;
        int TypeCode = -1;
    };

    protected:
    //Facts about this node
    int _token = -1;
    int _lineNumber = 0;
    QString _label;

    public:
    QVector<Node*> Children;
    Node* Sibling = nullptr;

    //Flags for code generation
    bool CompleteStatement = false;
    bool Parenthesis = false;

    public:
    // Init my node
    Node( int tokenValue, int lineNo, QString label = QString() );

    virtual ~Node();

    //Read only for my data
    int tokenType();
    int lineNumber();
    QString label();
    virtual SemanticType semanticType( Context* context );

    //*** Common functions the node uses to call into the child object

    // generate code for this node
    bool codeGen( QTextStream* stream, Context* context );

    // Detects errors in the code
    bool detectErrors( Error* err, Context* context );

    //Dup the symbol tree for debug
    void codePrint( Context* context );

    //Add siblings as children
    int addSiblingsAsChildren( Node* node );

    //*** Child specific implementions
    protected:
    //Iterate over children with custom callback on each
    void iterateChildren( Context* context, std::function<void (Node*, int)> callback );

    //Detect errors
    virtual bool calculateErrors( Error* err, Context* context );

    // Pre child code gen
    virtual bool codeGenPreChild( QTextStream* stream, Context* context );

    // Post child code gen
    virtual bool codeGenPostChild( QTextStream* stream, Context* context );

    // Between child code gen
    virtual bool codeGenPreChildWrapper( QTextStream* stream, Context* context, int child_idx );

    // Between child code gen
    virtual bool codeGenPostChildWrapper( QTextStream* stream, Context* context, int child_idx );

    // Return true if we are increasing scope depth
    virtual bool increaseScopeDepth();

    // print out this node and anyone else
    virtual void print( int scope_depth );
};

#endif
