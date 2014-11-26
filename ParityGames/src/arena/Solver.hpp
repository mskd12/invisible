/**CPPHeaderFile****************************************************************

  FileName    [Solver.hpp]

  PackageName [parityGame]

  Synopsis    [This file exports the class Solver.]

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
#ifndef __SOLVER_HPP__
#define __SOLVER_HPP__

#include "commonFile.hpp"
#include "Graph.hpp"
#include "../main.hpp"

namespace parityGame {
  
  class Solver {
  public:
    Solver(){}
    ~Solver(){}
    
    SymSIMStat solve(Graph G, AlgorithmName algo); 
  private:
    
    SymSIMStat zielonkaAlgorithm(Graph PG);
    SymSIMStat localStrategyImprovementAlgorithm(Graph PG, PLAYER pl);
    SymSIMStat symmetricStrategyImprovementAlgorithm(Graph PG);
  
    
  };
  
}
#endif // __SOLVER_HPP__

