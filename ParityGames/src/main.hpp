/**CPPHeaderFile****************************************************************

  FileName    [main.hpp]

  PackageName [none]

  Synopsis    [Main header file.]

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
#ifndef __MAIN_HPP__
#define __MAIN_HPP__

#include <iostream>
#include <limits>

/*---------------------------------------------------------------------------*/
/* Type declarations                                                         */
/*---------------------------------------------------------------------------*/

enum AlgorithmName {
  LocalStrategyImprovementEven,
  LocalStrategyImprovementOdd, 
  SymmetricStrategyImprovement,
  Zielonka,
  All
};

enum SwitchRule {
  SwitchAll,
  SwitchBest,
  SwitchRandom,
  SwitchHalf,
  LeastRecentlyConsidered,
  RandomFacet,
  RandomEdge,
  Zadeh
};

enum Verbosity {
  Normal,
  Debug
};

struct Options {
  std::string  input_file;
  AlgorithmName algo;
  int vertex;
  Verbosity verbosity;
  SwitchRule switch_rule;
  bool dual;
  bool show;
};

/*---------------------------------------------------------------------------*/
/* Constant declarations                                                     */
/*---------------------------------------------------------------------------*/
#define DEBUG(s) cout << "SymSIM_DEBUG: " << s << endl; getchar();
extern const int Undef; 
extern const int SymSIM_TIMEOUT; 

/*---------------------------------------------------------------------------*/
/* Global variable declarations                                              */
/*---------------------------------------------------------------------------*/
extern Options options; // Options specified during program invocation 

#endif /* __MAIN_HPP__ */
