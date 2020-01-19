def data():
    return [
        {
            "reg": "[\(\)\[\]\{\},;:]",
            "str": "strdup(yytext)",
            "ret": "yytext[0]",
        },
        {"rule": "IF"},
        {"rule": "ELSE"},
        {"rule": "VAR"},
        {"rule": "FN"},
        {"rule": "CLASS"},
        {"rule": "RETURN"},
        {"rule": "WHILE"},
        {"rule": "BREAK"},
        {"rule": "CONTINUE"},
        {"rule": "FALSE"},
        {"rule": "TRUE"},

        # Ops
        {"raw": "*", "rule": "MUL"},
        {"raw": "/", "rule": "DIV"},
        {"raw": "%", "rule": "MOD"},
        {"raw": "+", "rule": "ADD"},
        {"raw": "-", "rule": "SUB"},

        # Logic
        {"raw": "&&", "rule": "AND"},
        {"raw": "||", "rule": "OR"},
        {"raw": "!=", "rule": "NEQ"},
        {"raw": "<=", "rule": "LEQ"},
        {"raw": ">=", "rule": "GEQ"},
        {"raw": "==", "rule": "EQ"},
        {"raw": ">", "rule": "GT"},
        {"raw": "<", "rule": "LT"},
        {"reg": "[\!]", "rule": "NOT", "str": "!"},

        # Action
        {"reg": "[\=]", "rule": "ASSIGN", "str": "="},
        {"reg": "[.]", "rule": "DOT", "str":"."},

        # Vars
        {
            "reg": "[A-Za-z_][A-Za-z0-9_]*",
            "str": "strdup(yytext)",
            "ret": "IDENT",
        },
        {
            "reg": "[+-]?([0-9]*)(\.([0-9]+))?",
            "str": "strdup(yytext)",
            "ret": "NUMBER",
        },

        # White spacey stuff
        {"pure":"\"\\r\\n\" { lineNo++;}"},
        {"pure": "\"\\n\" { lineNo++;}"},
        {"pure": "\"\\r\" { lineNo++;}"},
        {"pure": "\"//\".*\n { lineNo++;}"},
        {"pure": "\" \" {}"},
        {"pure": "\\t {}"},
    ]
