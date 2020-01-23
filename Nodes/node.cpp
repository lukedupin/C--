#include "node.h"
#include <Helpers/token.h>
#include <Helpers/util.h>

#include <QScopedPointer>

  //Define my node
Node::Node( int token, int lineNo, QString label )
    : _token(token),
      _lineNumber(lineNo),
      _label(label)
{
}

Node::~Node()
{}

//Get some info
int Node::lineNumber() { return _lineNumber; }
int Node::tokenType() { return _token; }
QString Node::label() { return _label; }

  //Dump the code
bool Node::codeGen( QTextStream* stream, Context* context )
{
    //Pre child call
    codeGenPreChild( stream, context );

    //Iterate through the children, calling code gen
    iterateChildren( context,
                     [=](Node* node) {
                        node->codeGen( stream, context );
                     });

    //Post child call
    codeGenPostChild( stream, context );

    //Test the sibling
    if ( Sibling != nullptr )
        Sibling->codeGen( stream, context );

    return true;
}

  //Detect errors
bool Node::detectErrors( Error* err, Context* context )
{
    //Pre child call
    calculateErrors( err, context );

    //Iterate through the children, calling code gen
    iterateChildren( context,
                     [=](Node* node) {
                        node->detectErrors( err, context );
                     });

    //Test the sibling
    if ( Sibling != nullptr )
        Sibling->detectErrors( err, context );

    return true;
}

  //Print out my nodes
void Node::codePrint( Context* context )
{
    //Pre child call
    print( context->NodeStack.count() );

    //Iterate through the children, calling code gen
    iterateChildren( context,
                     [=](Node* node) {
                        node->codePrint( context );
                     });

    //Test the sibling
    if ( Sibling != nullptr )
        Sibling->codePrint( context );
}

void Node::iterateChildren( Context* context, std::function<void (Node*)> callback )
{
    //Push onto the stack
    auto c_depth = (increaseScopeDepth()? 1: 0);
    context->NodeStack.push_back( this );
    context->Depth += c_depth;

    //Go through my children
    for ( auto& node : Children )
        if ( node != nullptr )
            callback( node );

    //Pop off the stack
    context->NodeStack.pop_back();
    context->Depth -= c_depth;
}

bool Node::calculateErrors( Error* err, Context* context )
{
    Q_UNUSED(err)
    Q_UNUSED(context)
    return true;
}

bool Node::codeGenPreChild( QTextStream* stream, Context* context )
{
    Q_UNUSED(stream)
    Q_UNUSED(context)
    return true;
}

bool Node::codeGenPostChild( QTextStream* stream, Context* context )
{
    Q_UNUSED(stream)
    Q_UNUSED(context)
    return true;
}

bool Node::increaseScopeDepth()
{
    return false;
}

  //print out the children
void Node::print( int depth )
{
    QString padding;
    padding.resize( depth * 4, ' ');
    qDebug( "%s%s on line %d -> %s", padding.toUtf8().data(), tokenStr( _token ), _lineNumber, _label.toUtf8().data() );
}
