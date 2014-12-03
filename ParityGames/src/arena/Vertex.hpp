/**CPPHeaderFile****************************************************************

  FileName    [Vertex.hpp]

  PackageName [parityGame]

  Synopsis    [This file exports the class Vertex.]

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
#ifndef __VERTEX_HPP__
#define __VERTEX_HPP__

#include <iostream>
#include <map>
#include <vector>
#include "commonFile.hpp"
#include "../main.hpp" // For Undef 

namespace parityGame {
  
  class Vertex {
  private:
    std::string label;      // Label of the vertex
    int index;              // index of the vertex 
    int priority;           // priority of the vertex
    int original_priority;  // priority given in the input file 
    PLAYER player;          // Player corresponding to the vertex
    
    std::vector<int> succ_v; // List of successors
    std::vector<int> pred_v; // List of predecessors
    
  public: 
    Vertex(std::string lab, int id, int pr, PLAYER pl); //Constructor 

    std::string get_label(); 
    int get_id();
    int get_priority();
    int get_original_priority();
    PLAYER get_player();
    std::vector<int> get_succ_list();
    std::vector<int> get_pred_list();

    /* OVerloading assignment and comparison operators */
    Vertex& operator=(const Vertex &v);
    bool operator==(Vertex v);
    
    void set_priority(int p);
    void add_succ(int succ_id); // Add a successor to this vertex
    void delete_succ(int succ_id);
    void add_pred(int pred_id); // Add a predecessor to this vertex
    void delete_pred(int succ_id);
  };
  
}

#endif // __VERTEX_HPP__
