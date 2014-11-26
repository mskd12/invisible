/**CPPHeaderFile****************************************************************

  FileName    [Valuation.hpp]

  PackageName [parityGame]

  Synopsis    [This file exports the class Valuation.]

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
#ifndef __VALUATION_HPP__
#define __VALUATION_HPP__

#include <iostream>
#include <map>
#include "Value.hpp"
#include "../main.hpp" // for Undef 

namespace parityGame {
  
  class Valuation {
  private:
    std::map<int, Value> value;
    
  public:
    Valuation(){}
    
    void set_value (int vid, Value v);
    Value get_value (int vid);

    bool operator==(Valuation v);
  };

}

#endif // __VALUATION_HPP__
