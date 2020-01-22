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
        {"rule": "ELIF"},
        {"rule": "ELSE"},
        {"rule": "LET"},
        {"rule": "IN"},
        {"rule": "FN"},
        {"rule": "CLASS"},
        {"rule": "RETURN"},
        {"rule": "WHILE"},
        {"rule": "SWITCH"},
        {"rule": "MATCH"},
        {"rule": "CASE"},
        {"rule": "DEFAULT"},
        {"rule": "DO"},
        {"rule": "BREAK"},
        {"rule": "FOR"},
        {"rule": "FOREACH"},
        {"rule": "CONTINUE"},
        {"rule": "FIRST"},
        {"rule": "LAST"},
        {"rule": "FALSE"},
        {"rule": "TRUE"},
        {"rule": "SELF"},

        # In place mutation
        {"raw": "+=", "rule": "ADD_ASSIGN"},
        {"raw": "-=", "rule": "SUB_ASSIGN"},
        {"raw": "*=", "rule": "MUL_ASSIGN"},
        {"raw": "/=", "rule": "DIV_ASSIGN"},

        # Ops
        {"raw": "*", "rule": "MUL"},
        {"raw": "/", "rule": "DIV"},
        {"raw": "%", "rule": "MOD"},
        {"raw": "+", "rule": "ADD"},
        {"raw": "-", "rule": "SUB"},

        # Arrows
        {"raw": "=>", "rule": "ARROW_RIGHT"},

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
        {"rule": "U8"},
        {"rule": "U16"},
        {"rule": "U32"},
        {"rule": "U64"},
        {"rule": "U128"},
        {"rule": "F32"},
        {"rule": "F64"},
        {"rule": "STR"},
        {"rule": "VEC"},
        {"rule": "HASH"},

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
        {
            "rule": "STRING_DBL",
            "reg": '\\"([^\\\\\\"]|\\\\.)*\\"',
            "str": "strdup(yytext)",
        },
        {
            "rule": "STRING_TICK",
            "reg": "\\'(?:\\\\.|[^'\\\\])*\\'",
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
