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

//Get some info
int Node::lineNumber() { return _lineNumber; }
int Node::tokenType() { return _token; }
QString Node::label() { return _label; }

  //Dump the code
bool Node::codeGen( QTextStream* stream, QVector<Node*>* stack, int depth )
{
    //Alloc a pointer?
    QScopedPointer<QVector<Node*>> ptr;
    if ( stack == nullptr )
    {
        ptr.reset( new QVector<Node*>() );
        stack = ptr.data();
    }

    //Pre child call
    codeGenPreChild( stream, stack, depth );

    //Test the kids
    stack->push_back( this );
    auto c_depth = depth + (increaseScopeDepth()? 1: 0);
    for ( auto& node : Children )
        node->codeGen( stream, stack, c_depth );
    stack->pop_back();

    //Post child call
    codeGenPostChild( stream, stack, depth );

    //Test the sibling
    if ( Sibling != nullptr )
        Sibling->codeGen( stream, stack, depth );

    return true;
}

  //Detect errors
bool Node::detectErrors( Error* err, QVector<Node*>* stack )
{
    //Alloc a pointer?
    QScopedPointer<QVector<Node*>> ptr;
    if ( stack == nullptr )
    {
        ptr.reset( new QVector<Node*>() );
        stack = ptr.data();
    }

    //Pre child call
    calculateErrors( err, stack );

    //Test the kids
    stack->push_back( this );
    for ( auto& node : Children )
        node->detectErrors( err, stack );
    stack->pop_back();

    //Test the sibling
    if ( Sibling != nullptr )
        Sibling->detectErrors( err, stack );

    return true;
}

  //Print out my nodes
void Node::codePrint( QVector<Node*>* stack, int depth )
{
    //Alloc a pointer?
    QScopedPointer<QVector<Node*>> ptr;
    if ( stack == nullptr )
    {
        ptr.reset( new QVector<Node*>() );
        stack = ptr.data();
    }

    //Pre child call
    print( depth );

    //Print the kids
    stack->push_back( this );
    for ( auto& node : Children )
        node->codePrint( stack, depth + 1 );
    stack->pop_back();

    //Test the sibling
    if ( Sibling != nullptr )
        Sibling->codePrint( stack, depth );
}

bool Node::calculateErrors( Error* err, QVector<Node*>* stack )
{
    Q_UNUSED(err)
    Q_UNUSED(stack)
    return true;
}

bool Node::codeGenPreChild( QTextStream* stream, QVector<Node*>* stack, int depth )
{
    Q_UNUSED(stream)
    Q_UNUSED(stack)
    Q_UNUSED(depth)
    return true;
}

bool Node::codeGenPostChild( QTextStream* stream, QVector<Node*>* stack, int depth )
{
    Q_UNUSED(stream)
    Q_UNUSED(stack)
    Q_UNUSED(depth)
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
