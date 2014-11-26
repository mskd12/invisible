/**CPPHeaderFile****************************************************************

  FileName    [Value.hpp]

  PackageName [parityGame]

  Synopsis    [This file exports the class Value.]

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
#ifndef __VALUE_HPP__
#define __VALUE_HPP__

#include <iostream>
#include <set>

namespace parityGame {
 
  class Value {
  private:
    
    int best_priority;     // the priority of the deciding vertex 
    std::set<int> transient_priority_set; // priorities of the transient significant verticies
    int distance; // distance to the deciding vertex
    
  public:
    /* Constructors */
    Value();
    Value(int p);
    Value(int p, int d);
    
    /* Setter functions */
    void set_best_priority(int p);
    void set_distance(int d);
    void set_transient_priority_set(std::set<int> S);
    
    void add_transient(int p);
    void inc_distance();
    
    /* Getter function */
    int get_best_priority();
    std::set<int> get_transient_priority_set();
    int get_distance();

    /* Pretty print thiese values */
    std::string to_string(); 
    void print(); 
    
    /* OVerloading assignment and comparison operators */
    Value& operator=(const Value &v);
    bool operator==(Value v);
    bool operator!=(Value v);
    bool operator<=(Value v);
    bool operator<(Value v);
    bool operator>(Value v);
    bool operator>=(Value v);  
 
  private:
    /* computes maximum of  symmetric differnece of A and B */
    int computeMaxDiff(std::set<int> A, std::set<int> B);
  };

}



#endif /* __VALUE_HPP__ */
