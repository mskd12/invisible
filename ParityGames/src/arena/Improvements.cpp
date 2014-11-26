/**CPPFile*********************************************************************

  FileName    [Improvements.cpp]

  PackageName [parityGame]

  Synopsis    [Implements the class Improvements.]

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

#include "Improvements.hpp"
#include <assert.h>

using namespace std;
using namespace parityGame;


void Improvements::set_player (PLAYER pl) 
{
  player  = pl;
}

PLAYER Improvements::get_player ()
{
  return player;
}
    
void Improvements::set_switches (int vid, set<int> sw) 
{ 
  switch_list[vid] = sw;
}
    
void Improvements::set_switch (int vid, int sw) 
{ 
  switch_list[vid].insert(sw);
}

void Improvements::add_strictly_improving_vertex(int vid)
{
  strictly_improving_vertices.insert(vid);
}

    
bool Improvements::is_empty (int vid) 
{
  return switch_list.find(vid) == switch_list.end();
}

set<int> Improvements::get_switches (int vid) 
{
  assert(switch_list.find(vid) != switch_list.end());

  return switch_list[vid];
}
 
set<int> Improvements::get_strictly_improving_vertices()
{
  return strictly_improving_vertices;
}
   
string Improvements::to_string() 
{
  string out; 
      
  for (map<int, set<int> >::iterator it = switch_list.begin(); it != switch_list.end(); it++) {
    out =  out + std::to_string(it->first) + "->";
    for(set<int>::iterator jt = it->second.begin(); jt != it->second.end(); jt++) 
      out = out + std::to_string(*jt) + ", ";
    out = out + "\n";
  }
  
  return out;
}





