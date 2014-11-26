/**CPPHeaderFile****************************************************************

  FileName    [commonFile.hpp]

  PackageName [parityGame]

  Synopsis    [This file declares structures and types used in various classes
  in this directory.] 

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
#ifndef __COMMON_FILE_HPP__
#define __COMMON_FILE_HPP__

#include <set>
namespace parityGame {

  // const int Undef = std::numeric_limits<int>::min();
  // const int Undef = -1; 
  
  enum PLAYER {even, odd};
  enum STRAT_TYPE {s_even, s_odd, s_both, s_none};
  enum SymSIMExceptions {VertexNotFound, NoSuccessorFound, EndOfFile, FileNotFound};
  
  //  typedef vector<float> value;
  
  class SymSIMStat {
  public:
    std::set<int> even_winning_region;
    int iterations;
    double runningTimeInSecs;
  };
  

}

#endif // __COMMON_FILE_HPP__
