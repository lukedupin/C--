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

    void reset();

    QString nameToType( QString variable_name );

    QString primativeToNative( int type_code );
};

#endif // CONTEXT_H
