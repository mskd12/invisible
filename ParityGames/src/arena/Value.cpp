/**CPPFile*********************************************************************

  FileName    [Value.cpp]

  PackageName [parityGame]

  Synopsis    [Implements the class Value.]

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
#include<algorithm>
#include "Value.hpp"

#include <assert.h> // For assert 
#include "../main.hpp" // for Undef 

using namespace std;
using namespace parityGame;



Value::Value() 
{
  best_priority = 0; 
  distance = 0;
}

Value::Value(int p) 
{
  best_priority = p; 
  distance = 0;
}

Value::Value(int p, int d) 
{
  best_priority = p; 
  distance = d;
}
    
void Value::set_best_priority(int p) 
{
  best_priority = p;
}

void Value::set_distance(int d) 
{
  best_priority = d;
}
void Value::set_transient_priority_set(set<int> S) 
{
  transient_priority_set = S;
}

void Value::add_transient(int p) 
{
  if (p > best_priority) 
    transient_priority_set.insert(p);
}
void Value::inc_distance() 
{
  distance++;
}
    
int Value::get_best_priority() 
{
  return best_priority;
}

set<int> Value::get_transient_priority_set() 
{
  return transient_priority_set;
}

int Value::get_distance() 
{
  return distance;
}

string Value::to_string() 
{
  string out; 
  out = "<" + std::to_string(best_priority) + ", (";
  for(set<int>::iterator it = transient_priority_set.begin(); it != transient_priority_set.end(); it++) 
    out = out + std::to_string(*it) + ", ";
  out = out + "),"  + std::to_string(distance) + ">"; 
  
  return out;
}

void Value::print()
{
  cout << "Value: (" << best_priority <<", {";
  
  for (set<int>::iterator i = transient_priority_set.begin(); i != transient_priority_set.end(); i++) {
    cout << *i << ", ";
  }
  cout << "}, " << distance <<")\n"; 
}

Value& Value::operator=(const Value &v) 
{
  best_priority = v.best_priority;
  transient_priority_set = v.transient_priority_set;
  distance = v.distance;
  
  return *this;
}

bool Value::operator==(Value v)
{
  return ((v.distance == distance) && 
	  (v.best_priority == best_priority) && 
	  (v.transient_priority_set == transient_priority_set)); 
}

bool Value::operator!=(Value v)
{
  return !((v.distance == distance) && 
	   (v.best_priority == best_priority) && 
	   (v.transient_priority_set == transient_priority_set)); 
}

int Value::computeMaxDiff(set<int> A, set<int> B)
{
  if (A==B) return Undef;
  else {
    set<int> A_minus_B, B_minus_A;  
    
    set_difference(A.begin(), A.end(),
		   B.begin(), B.end(),
		   inserter(A_minus_B, A_minus_B.begin()));
    
    set_difference(
		   B.begin(), B.end(),
		   A.begin(), A.end(),
		   inserter(B_minus_A, B_minus_A.begin()));
    
    set<int> A_minus_B_union_B_minus_A; 
    
    set_union(A_minus_B.begin(), A_minus_B.end(),
	      B_minus_A.begin(), B_minus_A.end(),
	      inserter(A_minus_B_union_B_minus_A, A_minus_B_union_B_minus_A.begin()));
    
    return *(A_minus_B_union_B_minus_A.rbegin());
  }
}

bool Value::operator<=(Value v)
{
  int v1 = (best_priority%2==0)?best_priority:-1*best_priority;
  int v2 = (v.best_priority%2==0)?v.best_priority:-1*v.best_priority;
  
  if (v1 < v2) return true; 
  if (v1 > v2) return false; 
  
  if (v1==v2) {
    int max_diff = computeMaxDiff(transient_priority_set, v.transient_priority_set);
    if (max_diff == Undef)
      {  // transint sets are equal 
	if (v1 < 0) return (distance <= v.distance);
	else return (distance >= v.distance);
      }
    else {
      if (transient_priority_set.find(max_diff) != transient_priority_set.end()) 
	return (max_diff%2!=0);
      else return (max_diff%2==0);
    }
  }
  assert(false); // Control never reaches here
}

// bool operator<(Value v)
//    {
//      int v1 = (best_priority%2==0)?best_priority:-1*best_priority;
//      int v2 = (v.best_priority%2==0)?v.best_priority:-1*v.best_priority;

//      if (v1 < v2) return true; 
//      if (v1 > v2) return false; 

//      if (v1==v2) {
// 	set<int> tp1_minus_tp2, tp2_minus_tp1;  

// 	set_difference(transient_priority_set.begin(), transient_priority_set.end(),
// 		       v.transient_priority_set.begin(), v.transient_priority_set.end(),
// 		       inserter(tp1_minus_tp2, tp1_minus_tp2.end()));

// 	set_difference(
// 		       v.transient_priority_set.begin(), v.transient_priority_set.end(),
// 		       transient_priority_set.begin(), transient_priority_set.end(),
// 		       inserter(tp2_minus_tp1, tp2_minus_tp1.end()));

// 	int max_tp1_minus_tp2 = tp1_minus_tp2.empty()?Undef:*tp1_minus_tp2.rbegin();
// 	int max_tp2_minus_tp1 = tp2_minus_tp1.empty()?Undef:*tp2_minus_tp1.rbegin();

// 	if ((max_tp2_minus_tp1 == Undef) && (max_tp1_minus_tp2 == Undef)) {
// 	  // transint sets are equal 
// 	  if (v1 < 0) {return (v.distance >  distance);}
// 	  else {return (v.distance < distance);}
// 	}
// 	else {
// 	  if (max_tp1_minus_tp2 == Undef) return max_tp2_minus_tp1%2==0;
// 	  if (max_tp2_minus_tp1 == Undef) return max_tp1_minus_tp2%2!=0;
// 	  // none of them is empty
// 	  int t1 = (max_tp1_minus_tp2%2==0)?max_tp1_minus_tp2:-1*max_tp1_minus_tp2;
// 	  int t2 = (max_tp2_minus_tp1%2==0)?max_tp2_minus_tp1:-1*max_tp2_minus_tp1;

// 	  if (t1 < t2) return true; 
// 	  if (t1 > t2) return false; 
// 	  // t1==t2 is not possible.
// 	}

//      }

//      return false; // Control will never reach here
//    }

bool Value::operator<(Value v)
{
  return (*this <= v) &&  !(*this==v);
}

bool Value::operator>(Value v)
{
  return (v < *this);
}

bool Value::operator>=(Value v)
{
  return (v <= *this);
}



