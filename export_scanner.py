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
for entry in data():
    if "pure" in entry:
        file.write("%s\n" % entry['pure'])

    elif 'rule' in entry:
        rule = entry['rule']
        rules.append(rule)

        if "raw" in entry:
            file.write('"%s" {\n' %  entry['raw'])
            file.write('    lineNo = yylineno;\n')
            file.write('    JToken * s = new JToken;\n')
            file.write('    yylval.tokInfo = s;\n')
            file.write('    s->stringValue = "%s";\n' % entry['raw'])
            file.write('    s->line = yylineno;\n')
            file.write('    return %s;\n' % rule)

        elif "reg" in entry:
            file.write('%s {\n' %  entry['reg'])
            file.write('    lineNo = yylineno;\n')
            file.write('    JToken * s = new JToken;\n')
            file.write('    yylval.tokInfo = s;\n')
            file.write('    s->stringValue = "%s";\n' % entry['reg'])
            file.write('    s->line = yylineno;\n')
            file.write('    return %s;\n' % rule)

        else:
            file.write('"%s" {\n' %  rule.lower())
            file.write('    lineNo = yylineno;\n')
            file.write('    JToken * s = new JToken;\n')
            file.write('    yylval.tokInfo = s;\n')
            file.write('    s->stringValue = "%s";\n' % rule.lower())
            file.write('    s->line = yylineno;\n')
            file.write('    return %s;\n' % rule)

    else:
        file.write('%s {\n' % entry['reg'])
        file.write('    lineNo = yylineno;\n')
        file.write('    JToken * s = new JToken;\n')
        file.write('    yylval.tokInfo = s;\n')
        file.write('    s->stringValue = %s;\n' % entry['str'])
        file.write('    s->line = yylineno;\n')
        file.write('    return %s;\n' % entry['ret'])

    file.write('}\n')

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

# Update the parser.y
parser = []
file = open("parser.y", "r")

found = False
for line in file.readlines():
    if re.search("%token[ ]+<tokInfo>", line):
        if not found:
            for rule in rules:
                parser.append("%%token <tokInfo> %s\n" % (rule))
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
