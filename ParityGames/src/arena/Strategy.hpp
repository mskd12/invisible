/**CPPHeaderFile****************************************************************

  FileName    [Strategy.hpp]

  PackageName [parityGame]

  Synopsis    [This file exports the class Strategy.]

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
#ifndef __STRTEGY_HPP__
#define __STRTEGY_HPP__

#include <iostream>
#include <map>
#include "commonFile.hpp"
#include "../main.hpp" // For Undef 

namespace parityGame {
  
  class Strategy {
  public:
    STRAT_TYPE type;
    std::map<int, int> decision;
    
    Strategy(){}    
    
    void set_type(STRAT_TYPE t);
    void set_decision(int vid, int sid);
    
    STRAT_TYPE get_type();
    int get_decision(int vid);
    
    Strategy operator=(Strategy s);
    bool operator==(Strategy s);
  };
  
}

#endif // __STRTEGY_HPP__
