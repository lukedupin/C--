#include "context.h"

Context::Context()
{
    reset();
}

void Context::reset()
{
    Depth = 0;
    NodeStack.clear();
    ScopedVariables.clear();
    Variables.clear();
}
