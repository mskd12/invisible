/**CPPHeaderFile****************************************************************

  FileName    [Improvements.hpp]

  PackageName [parityGame]

  Synopsis    [This file exports the class Improvements.]

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
#ifndef __IMPROVEMENTS_HPP__
#define __IMPROVEMENTS_HPP__

#include <iostream>
#include <map>
#include "commonFile.hpp"
#include "../main.hpp" // For Undef 

namespace parityGame {
  
  class Improvements {
  private:
    std::map<int, std::set<int> > switch_list;
    std::set<int> strictly_improving_vertices;
    
    PLAYER player;
    
  public:
    Improvements() {}
    
    void set_player (PLAYER pl);
    void set_switches (int vid, std::set<int> sw);
    void set_switch (int vid, int sw);
    void add_strictly_improving_vertex(int vid);
    

    PLAYER get_player ();
    std::set<int> get_switches (int vid);
    std::set<int> get_strictly_improving_vertices();
    bool is_empty (int vid);
    
    std::string to_string();
  };
  
}

#endif // __IMPROVEMENTS_HPP__
