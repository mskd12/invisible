/**CPPFile*********************************************************************

  FileName    [Strategy.cpp]

  PackageName [parityGame]

  Synopsis    [Implements the class Strategy.]

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
#include "Strategy.hpp"
#include <assert.h>

using namespace std;
using namespace parityGame;

void Strategy::set_type(STRAT_TYPE t) 
{
  type = t;
}

void Strategy::set_decision(int vid, int sid) 
{
  decision[vid] = sid;
}
 
STRAT_TYPE Strategy::get_type() 
{
  return type;
}

int Strategy::get_decision (int vid) 
{
  
  if (decision.find(vid) == decision.end()) 
    return Undef;
  else 
    return decision[vid];
}
    

Strategy Strategy::operator=(Strategy s) 
{
  type = s.type;
  decision = s.decision;
  
  return *this;
}
    
bool Strategy::operator==(Strategy s)
{
  if (type != s.type) return false;
  
  for(map<int, int>::iterator it = decision.begin(); it != decision.end(); it++) {
    if (s.decision.at(it->first) != it->second) 
      return false; 
  }
  
  return true;
}







