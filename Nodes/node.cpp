#include "node.h"
#include <Helpers/token.h>
#include <Helpers/util.h>

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
bool Node::codeGen( QTextStream* stream, int depth )
{
    //Pre child call
    codeGenPreChild( stream, depth );

    //Test the kids
    auto c_depth = depth + (increaseScopeDepth()? 1: 0);
    for ( auto& node : Children )
        node->codeGen( stream, c_depth );

    //Post child call
    codeGenPostChild( stream, depth );

    //Test the sibling
    if ( Sibling != nullptr )
        Sibling->codeGen( stream, depth );

    return true;
}

  //Detect errors
bool Node::detectErrors( Error* err )
{
    //Pre child call
    calculateErrors( err );

    //Test the kids
    for ( auto& node : Children )
        node->detectErrors( err );

    //Test the sibling
    if ( Sibling != nullptr )
        Sibling->detectErrors( err );

    return true;
}

  //Print out my nodes
void Node::codePrint( int depth )
{
    //Pre child call
    print( depth );

    //Print the kids
    auto c_depth = depth + (increaseScopeDepth()? 1: 0);
    for ( auto& node : Children )
        node->codePrint( c_depth );

    //Test the sibling
    if ( Sibling != nullptr )
        Sibling->codePrint( depth );
}

bool Node::calculateErrors( Error* err )
{
    Q_UNUSED(err)
    return true;
}

bool Node::codeGenPreChild( QTextStream* stream, int depth )
{
    Q_UNUSED(stream)
    Q_UNUSED(depth)
    return true;
}

bool Node::codeGenPostChild( QTextStream* stream, int depth )
{
    Q_UNUSED(stream)
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
