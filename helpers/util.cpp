#include <string.h>
#include <stdio.h>

void printIndent( const int depth, const int spaces )
{
    char buffer[depth * spaces + 1];

    memset( buffer, ' ', depth * spaces );
    buffer[depth * spaces] = 0;

    printf("%s", buffer);
}
