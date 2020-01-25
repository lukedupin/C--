#ifndef CONTEXT_H
#define CONTEXT_H

#include <QString>
#include <QVector>
#include <QHash>

class Node;

class Context
{
    public:
    QVector<Node*> NodeStack;
    QVector<QVector<QString>> ScopedVariables;

    QHash<QString, Node*> Variables;

    int Depth = 0;

    public:
    Context();

    //Clear out context info, not settings data
    void reset();

    //Return white space padding based on depth
    QString padding();

    //Convert a variable name into a user defined type based on scope
    QString nameToType( QString variable_name );

    //Convert a code into target language type
    QString primitiveToNative( int type_code );
};

#endif // CONTEXT_H
