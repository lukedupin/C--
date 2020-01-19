#!/usr/bin/python

from scanner import data
import re

rules = []

# Open the scanner.lex
file = open("scanner.lex", "w")

# Write out the heard
file.write('%option noyywrap\n')
file.write('%option yylineno\n')
file.write('%{\n')
file.write('    #include <stdio.h>\n')
file.write('    #include "j_token.h"\n')
file.write('    #include "node.h"\n')
file.write('    #include "parser.tab.h"\n')
file.write('    int lineNo;\n')
file.write('%}\n')
file.write('\n')
file.write('%%\n')
file.write('\n')

# Write out the user rules
rule_count = 0
for entry in data():
    rule_count += 1
    if "pure" in entry:
        file.write("%s\n" % entry['pure'])
        continue

    # Raw defines
    if 'define' in entry:
        rules.append( entry['define'] )
        continue

    # Handle rule based actions
    if 'rule' in entry:
        rule = entry['rule']
        rules.append(rule)

        if "raw" in entry:
            sv = '"%s"' % entry['raw']
            file.write('"%s" {\n' %  entry['raw'])
            file.write('    lineNo = yylineno;\n')
            file.write('    JToken * s = new JToken;\n')
            file.write('    yylval.tokInfo = s;\n')
            file.write('    s->stringValue = %s;\n' % (sv if "str" not in entry else entry['str']))
            file.write('    s->line = yylineno;\n')
            file.write('    return %s;\n' % rule if "ret" not in entry else entry['ret'])

        elif "reg" in entry:
            sv = '"%s"' % entry['reg']
            file.write('%s {\n' %  entry['reg'])
            file.write('    lineNo = yylineno;\n')
            file.write('    JToken * s = new JToken;\n')
            file.write('    yylval.tokInfo = s;\n')
            file.write('    s->stringValue = %s;\n' % (sv if "str" not in entry else entry['str']))
            file.write('    s->line = yylineno;\n')
            file.write('    return %s;\n' % rule if "ret" not in entry else entry['ret'])

        else:
            sv = '"%s"' % rule.lower()
            file.write('"%s" {\n' %  rule.lower())
            file.write('    lineNo = yylineno;\n')
            file.write('    JToken * s = new JToken;\n')
            file.write('    yylval.tokInfo = s;\n')
            file.write('    s->stringValue = %s;\n' % (sv if "str" not in entry else entry['str']))
            file.write('    s->line = yylineno;\n')
            file.write('    return %s;\n' % rule if "ret" not in entry else entry['ret'])

    # None rule based rule, raw chars or something?
    else:
        file.write('%s {\n' % entry['reg'])
        file.write('    lineNo = yylineno;\n')
        file.write('    JToken * s = new JToken;\n')
        file.write('    yylval.tokInfo = s;\n')
        file.write('    s->stringValue = %s;\n' % entry['str'])
        file.write('    s->line = yylineno;\n')
        file.write('    return %s;\n' % entry['ret'])

    file.write('}\n')

# Error are defaults!
rules.append("ERROR")
file.write('. {\n')
file.write('    lineNo = yylineno;\n')
file.write('    JToken * s = new JToken;\n')
file.write('    yylval.tokInfo = s;\n')
file.write('    s->stringValue = yytext;\n')
file.write('    s->line = yylineno;\n')
file.write('    return ERROR;\n')
file.write('}\n')
file.write('\n')
file.write('%%\n')

file.close()

print("Wrote to scanner.lex %d rules" % (rule_count + 1))

# Update the parser.y
parser = []
file = open("parser.y", "r")

found = False
for line in file.readlines():
    # Replace the token section with the tokens we just found
    if re.search("%token[ ]+<tokInfo>", line) is not None:
        if not found:
            for rule in rules:
                parser.append("%%token <tokInfo> %s\n" % rule)
            print("Wrote %d tokens" % len(rules))
        found = True
        continue

    # Add in
    parser.append( line )

file.close()

# Write out the parser
file = open("parser.y", "w")
for line in parser:
    file.write(line)
file.close()

# Write out a conversion for my rules
file = open("helpers/token.h", "w")
file.write('''#ifndef TOKEN_H

const char* tokenStr( int token );

#endif
''')
file.close()

# Write out the token helper cpp
file = open("helpers/token.cpp", "w")
file.write('''#include "token.h"
#include "node.h"
#include "j_token.h"
#include "parser.tab.h"

const char* tokenStr( int token )
{
    switch ( token )
    {
''')

for rule in rules:
  file.write('        case %s:\n' % rule)
  file.write('            return "%s";\n' % rule)
  file.write('\n')

file.write('''        
        default:
            return "Unknown";
    }
}
''')
file.close()
