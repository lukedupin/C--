/// \file main.c Processes command line options and sets our compiler in motion.
#include <strings.h>
#include <unistd.h>

#include "node.h"

#include <iostream>

using namespace std;

#define kmCommandSwitches "dpsjo:v"

extern int ourGetopt( int, char **, const char*);

int main( int argc, char * argv[])
{

	extern char *optarg;
  bool print_tree = false;

    //Default for my variables
  yyin = stdin;

  int retVal;
  while ((retVal = ourGetopt (argc, argv, kmCommandSwitches)) && optind <= argc)
  {
    switch (retVal)
    {
      case 'd':
        yydebug = 1;
      break;
      case 'p':
        print_tree = true;
      break;
      case 'o':
        //ParseTree->setCodeOutput( fopen(optarg, "w") );
        optind++;
      break;
      case '?':
          printf("Usage: %s -[any of %s] (input file).\n If no input file is specified, stdin is used.\n", argv[0], kmCommandSwitches);
      break;

        //Set the input file
      default:
        if (optind != argc)
        {
          yyin = fopen(argv[optind], "r");
          optind++;
        }
      break;
    }

      //Break out of my loop when we've looked at all options
    if (optind == argc)
      break;
  }


    //Parse out my try
  yyparse();
  if (ParseTree != nullptr) //No parse errors
  {
      //Detect any and all errors
			Error err;
    	ParseTree->detectErrors( &err );

      //Print out the parse tree
    if (print_tree)
      ParseTree->codePrint();

      //Dump out the number of errors and warnings
    printf("Number of warnings: 0\n");
    //printf("Number of errors: %d\n\n", err.count() );

    //if ( err.count() != 0) return 0; // arbitrary value

      //Dump the ASM
			ostringstream stream;
    	ParseTree->codeGen( &stream );

			cout << stream.str();
  }
}
