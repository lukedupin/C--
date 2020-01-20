def data():
    return [
        {
            "reg": "[\(\)\[\],;:]",
            "str": "strdup(yytext)",
            "ret": "yytext[0]",
        },

        {"raw": "{", "rule": "LEFT_CURLY"},
        {"raw": "}", "rule": "RIGHT_CURLY"},

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

        # Arrows
        {"raw": "->", "rule": "ARROW_RIGHT"},
        {"raw": "<-", "rule": "ARROW_LEFT"},

        # Logic
        {"raw": "&&", "rule": "AND"},
        {"raw": "||", "rule": "OR"},
        {"raw": "!=", "rule": "NEQ"},
        {"raw": "<=", "rule": "LEQ"},
        {"raw": ">=", "rule": "GEQ"},
        {"raw": "==", "rule": "EQ"},
        {"raw": ">", "rule": "GT"},
        {"raw": "<", "rule": "LT"},
        {"reg": "[\!]", "rule": "NOT", "str": '"!"'},

        # Action
        {"reg": "[\=]", "rule": "ASSIGN", "str": '"="'},
        {"reg": "[.]", "rule": "DOT", "str": '"."'},

        # Types
        {"rule": "I8"},
        {"rule": "I16"},
        {"rule": "I32"},
        {"rule": "I64"},
        {"rule": "I128"},

        # Vars
        {
            "rule": "IDENT",
            "reg": "[A-Za-z_][A-Za-z0-9_]*",
            "str": "strdup(yytext)",
        },
        {
            "rule": "NUMBER",
            "reg": "[+-]?([0-9]*)(\.([0-9]+))?",
            "str": "strdup(yytext)",
        },

        # White spacey stuff
        {"pure":"\"\\r\\n\" { lineNo++;}"},
        {"pure": "\"\\n\" { lineNo++;}"},
        {"pure": "\"\\r\" { lineNo++;}"},
        {"pure": "\"//\".*\\n { lineNo++;}"},
        {"pure": "\" \" {}"},
        {"pure": "\\t {}"},
    ]
