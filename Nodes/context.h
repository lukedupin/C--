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
};

#endif // CONTEXT_H
