/**CPPFile*********************************************************************

  FileName    [main.cpp]

  PackageName [none]

  Synopsis    [Main file for the tool SymSIM.]

  Description []

  SeeAlso     []

  Author      [Ashutosh Trivedi (trivedi@cse.iitb.ac.in)]
  
  Copyright   [ 
  
  This program SymSIM is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the Free
  Software Foundation; either version 2 of he License, or (at your option) any
  later version.  
  
  This program is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details
  at http://www.gnu.org/copyleft/gpl.html
  
  ]

*******************************************************************************/

#include "main.hpp"
#include <string>
#include <string.h>
#include "parser/parserInt.h"
#include "arena/Graph.hpp"
#include "arena/Solver.hpp"
#include "main.hpp"

/*---------------------------------------------------------------------------*/
/* Namespace declarations                                                    */
/*---------------------------------------------------------------------------*/
using namespace std;

/*---------------------------------------------------------------------------*/
/* Global Variable declarations                                              */
/*---------------------------------------------------------------------------*/
Options options;
const int Undef = std::numeric_limits<int>::min();
const int SymSIM_TIMEOUT = 10000;

/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/
void parseCommandLineOptions(int argc, char **argv, Options& opt);
parityGame::Graph parseInputGraph(string inpfile);

/*---------------------------------------------------------------------------*/
/* Definitions of exported function                                          */
/*---------------------------------------------------------------------------*/

/**Function********************************************************************
   
   Synopsis    [The "main" function]
   
   Description [optional]
   
   SideEffects [required]
   
   SeeAlso     [optional]
   
******************************************************************************/
int main(int argc, char* argv[])
{
  srand(time(NULL));
  
  /* Parse command line options and populate "options" data structure */
  parseCommandLineOptions(argc, argv, options);

  parityGame::Graph PG;

  /* Parse the input graph file */
  if (options.dual)  // Compute difficult example 
    PG = parseInputGraph(options.input_file).compute_dual_game();
  else  // Work iwth the original example
    PG = parseInputGraph(options.input_file);
  
  parityGame::Solver engine;
  parityGame::SymSIMStat result = engine.solve(PG,options.algo);


  return 0;
}

/**Function********************************************************************
   
   Synopsis    [This program parses the command-line options.]
   
   Description [This program parses the command line options and fills the
   variable opt of type Options defined in the file main.hpp.]
   
   SideEffects []
   
   SeeAlso     [optional]
   
******************************************************************************/
void parseCommandLineOptions(int argc, char **argv, Options& opt)
{

  opt.switch_rule = SwitchAll; //default switchign rule 
  opt.algo = All; //default algo 
  opt.dual = false;
  opt.show = false;
  argc--; argv++;

  while (argc > 0) {
    if (strcmp(*argv, "-algo") == 0 || strcmp(*argv, "-a") == 0) {
      argv++; argc--;
      
      if (argc == 0) {
        
	cout << "SymSIM-ERROR: \"algo\" command line option require one of the following  arguments:\n";
	cout << "             - lsio : for local strategy improvement algorithm for Odd\n";
	cout << "             - lsie : for local strategy improvement algorithm for Even\n";
	cout << "             - ssi : for symmetric strategy improvement algorithm \n";
	cout << "             - zie : for Zielonka's algorithm \n";
	cout << "             - all : All algorithms \n";
       
	exit(1);
      }
      
      if (strcmp(*argv, "lsio") == 0) opt.algo = LocalStrategyImprovementOdd;
      else if (strcmp(*argv, "lsie") == 0) opt.algo = LocalStrategyImprovementEven;
      else if (strcmp(*argv, "ssi") == 0) opt.algo = SymmetricStrategyImprovement;
      else if (strcmp(*argv, "zie") == 0) opt.algo = Zielonka;
      else if (strcmp(*argv, "all") == 0) opt.algo = All;
      else { cout << "SymSIM-ERROR: \"-algo\" unknown option\n"; exit(1);}
      
      argv++; argc--;
      
      continue;
    }
    else if (strcmp(*argv, "-srule") == 0 || strcmp(*argv, "-s") == 0) {
      argv++; argc--;
      
      if (argc == 0) {
	cout << "SymSIM-ERROR: \"srule\" command line option require one of the following  arguments:\n";
	cout << "             - all : for switch-all rule \n";
	cout << "             - best : for switch-best rule \n";
	cout << "             - random : for switch-random rule \n";	
	cout << "             - half : for switch-half rule \n";
	cout << "             - leastRecent : for switch-least-recently-considered rule \n";
	cout << "             - randomEdge : for switch-random-facet rule \n";
 	cout << "             - randomFacet : for switch-random-edge rule \n";
	cout << "             - zadeh : for Zadeh's rule \n";

        exit(1);
      }
      
      if (strcmp(*argv, "all") == 0) opt.switch_rule = SwitchAll;
      else if (strcmp(*argv, "best") == 0) opt.switch_rule= SwitchBest;
      else if (strcmp(*argv, "random") == 0) opt.switch_rule = SwitchRandom;
      else if (strcmp(*argv, "half") == 0) opt.switch_rule = SwitchHalf;
      else if (strcmp(*argv, "leastRecent") == 0) opt.switch_rule  = LeastRecentlyConsidered;
      else if (strcmp(*argv, "randomEdge") == 0) opt.switch_rule = RandomEdge;
      else if (strcmp(*argv, "randomFacet") == 0) opt.switch_rule = RandomFacet;
      else if (strcmp(*argv, "zadeh") == 0) opt.switch_rule = Zadeh;
      else {
	cout << "SymSIM-ERROR: \"-srule\" unknown option\n"; 
	cout << "SymSIM-ERROR: \"srule\" command line option require one of the following  arguments:\n";
	cout << "             - all : for switch-all rule \n";
	cout << "             - best : for switch-best rule \n";
	cout << "             - random : for switch-random rule \n";	
	cout << "             - half : for switch-half rule \n";
	cout << "             - leastRecent : for switch-least-recently-considered rule \n";
	cout << "             - randomEdge : for switch-random-facet rule \n";
 	cout << "             - randomFacet : for switch-random-edge rule \n";
	cout << "             - zadeh : for Zadeh's rule \n";

	exit(1);
      }
      
      argv++; argc--;
      
      continue;
    }
    
    else if (strcmp(*argv, "-i") == 0) {
      argv++; argc--;
      
      if (argc == 0) {
        cout << "SymSIM-ERROR: \"i\" command line option require an argument\n";
        exit(1);
      }
      
      opt.input_file = strdup(*argv);
      
      argv++; argc--;
      continue;
    }
    else if (strcmp(*argv, "-v") == 0) {
      argv++; argc--;
      if (argc == 0) {
        cout << "SymSIM-ERROR: \"v\" command line option require an argument\n";
        exit(1);
      }
      
      if (strcmp(*argv, "0") == 0) opt.verbosity = Normal;
      else if (strcmp(*argv, "1") == 0) opt.verbosity = Debug;
      else {
        cout << "SymSIM_WARNING: Verbosity level undefind, Normal Used instead.\n";
        opt.verbosity = Normal;
      }
      
      argv++; argc--;
    }
    else if (strcmp(*argv, "-d") == 0) {
      argv++; argc--;
      opt.dual = true;
    }
    else if (strcmp(*argv, "-g") == 0) {
      argv++; argc--;
      opt.show = true;
    }
    else {
      cout << "SymSIM-ERROR: unknown arguments \n";
      exit(1);
    }
  }
}

/**Function********************************************************************
   
   Synopsis    [This program calls the parser on the input file that upon
   successful completion creates a valid game arena.]
   
   Description []
   
   SideEffects []
   
   SeeAlso     [optional]
   
******************************************************************************/
parityGame::Graph parseInputGraph(string inpfile)
{
  try { 
    parityGame::Graph G = parse_graph(inpfile.c_str());
    return G;
  }
  catch (parityGame::SymSIMExceptions e) {
    cout << "SymSIM-ERROR: [Syntax_ERROR] ]Unable to parse the File " << inpfile <<"! \n"; 
    exit(1);
  }
}

