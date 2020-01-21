#ifndef LEX_TOKEN_H
#define LEX_TOKEN_H

struct LexToken
{
    int code;
    const char * stringValue;
    int line;
};

#endif
