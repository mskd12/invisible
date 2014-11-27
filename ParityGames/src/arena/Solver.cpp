/**CPPFile*********************************************************************

  FileName    [Solver.cpp]

  PackageName [parityGame]

  Synopsis    [Implements the class Solver.]

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
#include "Solver.hpp"

using namespace std;
using namespace parityGame;

SymSIMStat Solver::solve(Graph PG, AlgorithmName algo) 
{
  SymSIMStat result;
  
  switch (algo) {
    
  case LocalStrategyImprovementEven: 
    result = localStrategyImprovementAlgorithm(PG, even);
    cerr << options.input_file << "\t" << result.iterations << "\t" << result.runningTimeInSecs << "\n ";
    break;
    
  case LocalStrategyImprovementOdd: 
    result =localStrategyImprovementAlgorithm(PG, odd);
    cerr << options.input_file << "\t" << result.iterations << "\t" << result.runningTimeInSecs << "\n ";
   break;
 
  case SymmetricStrategyImprovement:
    result = symmetricStrategyImprovementAlgorithm(PG);
    cerr << options.input_file << "\t" << result.iterations << "\t" << result.runningTimeInSecs << "\n";
    break;
  
  case Zielonka:
    result = zielonkaAlgorithm(PG);
    cerr << options.input_file  << result.runningTimeInSecs << "\n";
    break;
    
  case All: 
    {
    SymSIMStat lsi_even, lsi_odd, ssi, zie; 
    
    lsi_even = localStrategyImprovementAlgorithm(PG, parityGame::even);
    //lsi_odd = localStrategyImprovementAlgorithm(PG, parityGame::odd);
    //ssi = symmetricStrategyImprovementAlgorithm(PG);
    zie = zielonkaAlgorithm(PG);    
    
    if (lsi_even.iterations <  SymSIM_TIMEOUT) assert(lsi_even.even_winning_region == zie.even_winning_region);
    //if (lsi_odd.iterations <  SymSIM_TIMEOUT)  assert(lsi_odd.even_winning_region == zie.even_winning_region);
    //if (ssi.iterations <  SymSIM_TIMEOUT) assert(ssi.even_winning_region  == zie.even_winning_region);
    
    result = lsi_even;

    if (options.dual) cerr << options.input_file << "_dual\t";
    else cerr << options.input_file << "\t";
    
    cerr << "lsi_even " << lsi_even.iterations << "\t" << lsi_even.runningTimeInSecs << "\t";
    //cerr << "lsi_odd " << lsi_odd.iterations << "\t" << lsi_odd.runningTimeInSecs << "\t";
    //cerr << "ssi " << ssi.iterations << "\t" << ssi.runningTimeInSecs << "\t";
    cerr << "Zielonka " << zie.runningTimeInSecs << "\n";
    }
    break;
  default:
    break;
  };

  if (options.show) PG.show(result.even_winning_region);  

  return result;
}


SymSIMStat Solver::zielonkaAlgorithm(Graph PG)
{
  SymSIMStat result;
  clock_t startTime = clock();
  
  result.even_winning_region = PG.PGSolve().first;
  result.iterations = Undef;
  result.runningTimeInSecs = (clock() - startTime)/(double) CLOCKS_PER_SEC;

  return result;
}

/**Function********************************************************************

   Synopsis    [Executes local strategy improvement algorithm]

  Description [Executed local strategy improvement algorithm for the player 
  given by parameter pl.]

  SideEffects [none]

  SeeAlso     [symmetricStrategyImprovementAlgorithm]

******************************************************************************/
SymSIMStat Solver::localStrategyImprovementAlgorithm(Graph PG, PLAYER pl)
{
  SymSIMStat result;
  clock_t startTime = clock();
  
  pair<Strategy, int> tmp = PG.strategyImprovement(pl);  
  
  result.even_winning_region = PG.get_even_winning_set(tmp.first);
  result.iterations = tmp.second;
  
  result.runningTimeInSecs = (clock() - startTime)/(double) CLOCKS_PER_SEC;

  return result;
}

SymSIMStat Solver::symmetricStrategyImprovementAlgorithm(Graph PG)
{
  SymSIMStat result;
  clock_t startTime = clock();
  
  pair<Strategy, int> tmp = PG.symStrategyImprovement();  
  
  result.even_winning_region = PG.get_even_winning_set(tmp.first);
  result.iterations = tmp.second;
  
  result.runningTimeInSecs = (clock() - startTime)/(double) CLOCKS_PER_SEC;
  
  return result;
}

