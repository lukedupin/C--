#include <program_node.h>

#include <QCoreApplication>

void yyparse();

int qt_main( int argc, char** argv, ProgramNode** parse_tree, FILE** yyin, int* yydebug )
{
    QCoreApplication app( argc, argv );

    //Setup some vars
    auto print_tree = false;
    (*yyin) = stdin;
    *yydebug = 0;

    if ( argc <= 1 )
    {
        qDebug("Usage: ./%s [-d] [-p] FILENAME.c--", argv[0]);
        return -1;
    }

    //Setup the switches
    for ( auto& arg : app.arguments() )
    {
        if ( arg == "-d")
            *yydebug = 1;
        else if ( arg == "-p" )
            print_tree = true;
    }

    //Setup the input
    *yyin = fopen(argv[argc - 1], "r");

    //Parse out my try
    yyparse();
    if ( *parse_tree == nullptr) //No parse errors
    {
        qDebug("No parse tree found");
        return -1;
    }

    Context context;

    //Detect any and all errors
    Error err;
    context.reset();
    (*parse_tree)->detectErrors( &err, &context );

    //Print out the parse tree
    if (print_tree)
    {
        context.reset();
        (*parse_tree)->codePrint( &context );
    }

    //Dump out the number of errors and warnings
    qDebug("Number of warnings: 0");
    qDebug("Number of errors: %d\n", err.count() );

    if ( err.count() != 0)
    {
        qDebug("Exiting due to errors");
        return 1;
    }

    //Compile the program
    QString result;
    QTextStream stream( &result );

    context.reset();
    (*parse_tree)->codeGen( &stream, &context );

    //Temp, should write to file
    qDebug("Program Dump:\n%s", result.toUtf8().data());

    return 0;
}
