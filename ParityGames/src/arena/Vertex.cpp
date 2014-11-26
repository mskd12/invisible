/**CPPFile*********************************************************************

  FileName    [Vertex.cpp]

  PackageName [parityGame]

  Synopsis    [Implements the class Vertex.]

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
#include "Vertex.hpp"
#include <assert.h>

using namespace std;
using namespace parityGame;

Vertex::Vertex(string lab, int id, int pr, PLAYER pl) 
{ 
  this->label = lab; 
  this->index = id; 
  this->priority = pr;
  this->original_priority = pr;
  this->player = pl;
}

string Vertex::get_label()
{ 
  return label;
}

int Vertex::get_id() 
{ 
  return index; 
}

int Vertex::get_priority()
{ 
  return priority;
}

int Vertex::get_original_priority()
{ 
  return original_priority;
}
    
PLAYER Vertex::get_player()
{ 
  return player;
}

vector<int> Vertex::get_succ_list() 
{
  return succ_v;
}

vector<int> Vertex::get_pred_list() 
{
  return pred_v;
}
    
void Vertex::set_priority(int p) 
{ 
  priority = p;
}

void Vertex::add_succ(int succ_id) 
{
  this->succ_v.push_back(succ_id); 
} 

void Vertex::delete_succ(int succ_id)
{
  for(vector<int>::iterator it = succ_v.begin(); it!=succ_v.end(); it++)
  {
	  if(*it == succ_id) 
	  {
		  succ_v.erase(it);
		  return;
	  }
  }
  cout << "NoSuccessorFound" << endl;
  //throw  NoSuccessorFound;
}
	   
void Vertex::add_pred(int pred_id) 
{
  this->pred_v.push_back(pred_id); 
} 

void Vertex::delete_pred(int pred_id)
{
  for(vector<int>::iterator it = pred_v.begin(); it!=pred_v.end(); it++)
  {
	  if(*it == pred_id) 
	  {
		  pred_v.erase(it);
		  return;
	  }
  }
  cout << "NoPredecessorFound" << endl;
  //throw  NoSuccessorFound;
}

