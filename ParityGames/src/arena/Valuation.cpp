/**CPPFile*********************************************************************

  FileName    [Valuation.cpp]

  PackageName [parityGame]

  Synopsis    [Implements the class Valuation.]

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
#include "Valuation.hpp"

using namespace std;
using namespace parityGame;

void Valuation::set_value (int vid, Value v) 
{ 
  value[vid] = v;
}

Value Valuation::get_value (int vid) 
{
  if (value.find(vid) == value.end()) {
    Value t_val(Undef, 0);
    return t_val;
  }
  else return value[vid];
}

bool Valuation::operator==(Valuation v)
{
  std::map<int, Value> lhs, rhs;
  lhs = value;
  rhs = v.value;
  
  if (lhs.size() != rhs.size()) return false; 
  
  map<int, Value>::const_iterator i, j;
  for(i = lhs.begin(), j = rhs.begin(); i != lhs.end(); ++i, ++j)
    {
      Value v1 = i-> second;
      Value v2 = j-> second; 

      if (i->first != j->first)  return false;
      //      if (i->second != j->second)  return false; 
      if (v1 != v2)  return false; 
    }

  return true;
}

