/**CPPFile*********************************************************************

  FileName    [Graph.cpp]

  PackageName [parityGame]

  Synopsis    [Implements the class Graph.]

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

#include "Graph.hpp" 
#include <random>       // std::default_random_engine
#include <algorithm>    // std::shuffle
#include <stack>
#include <limits.h>
#define NINF INT_MIN

// #include <boost/graph/directed_graph.hpp> // A subclass to provide reasonable arguments to adjacency_list for a typical directed graph
// #include <boost/graph/graphviz.hpp> // to display

  // boost::directed_graph<> g;
  
  // boost::directed_graph<>::vertex_descriptor v0 = g.add_vertex();
  // boost::directed_graph<>::vertex_descriptor v1 = g.add_vertex();
 
  // g.add_edge(v0, v1);
  
  // boost::write_graphviz(std::cout, g);


using namespace std;
using namespace parityGame;

/******************************************************************************
 *    PUBLIC FUNCTION DEFINITIONS
 *****************************************************************************/
void Graph::add_vertex(Vertex v) 
{
  this->vertices.push_back(v);
  
  if (v.get_player() == even) {
    this->even_vertices.push_back(n_vertices);
  }
  else {
    this->odd_vertices.push_back(n_vertices);
  }
  
  n_vertices++; 
}

void Graph::add_vertex(string label, int id, int priority, PLAYER player)
{
  Vertex v(label, id, priority, player);
  
  this->vertices.push_back(v);
  
  if (v.get_player() == even) {
    this->even_vertices.push_back(n_vertices);
  }
  else {
    this->odd_vertices.push_back(n_vertices);
  }
  
  n_vertices++; 
}

void Graph::set_successor(string vertex, string succ)
{
  get_vertex(vertex).add_succ(get_vertex(succ).get_id());
}

void Graph::fill_predecessors()
{
  vector<Vertex>::iterator i;

  // fill predecessors list
  for (i = vertices.begin(); i != vertices.end(); i++) {
    int vertex_id = (*i).get_id();
    
    vector<int> succ_list = (*i).get_succ_list();
    vector<int>::iterator j = succ_list.begin();
    
    while (j != succ_list.end()) {
      get_vertex(*j).add_pred(vertex_id);
      j++;
    }
  }

  // Fill preference_set and priority_set list 
  for (i = vertices.begin(); i != vertices.end(); i++) {
    int vertex_priority = (*i).get_priority();
  
    preference_set.insert((vertex_priority%2)==0?vertex_priority:-1*vertex_priority); 
    priority_set.insert(vertex_priority); 
  }
  
  // Fill priority_sorted_vertex_list 
  for(set<int>::reverse_iterator rit  = priority_set.rbegin(); rit!= priority_set.rend(); ++rit) { 
    int t_priority = (*rit);
    
    for(vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); it++) {
      if ((*it).get_priority()==t_priority) priority_sorted_vertex_list.push_back((*it).get_id());
    }
  }

  // Fill preference_sorted_vertex_list 
  for(set<int>::reverse_iterator rit  = preference_set.rbegin(); rit!= preference_set.rend(); ++rit) { 
    int t_priority = (*rit)>=0?(*rit):-1*(*rit);
    
    for(vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); it++) {
      if ((*it).get_priority()==t_priority) sorted_vertex_list.push_back((*it).get_id());
    }
  }

  // Give a random order on vertices
  for (vector<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
    randomized_vertices_list.push_back((*i).get_id());
  }
  random_shuffle(randomized_vertices_list.begin(), randomized_vertices_list.end());
  
}


Vertex& Graph::get_vertex(const string label)
{

  vector<Vertex>::iterator i;
  
  for (i = vertices.begin(); i != vertices.end(); i++) {
    if ((*i).get_label() == label) return (*i);
  }
  
  throw VertexNotFound; 

}

Vertex& Graph::get_vertex(const int id)
{
  vector<Vertex>::iterator i;
  
  for (i = vertices.begin(); i != vertices.end(); i++) {
    if ((*i).get_id() == id) return (*i);
  }
  
  throw VertexNotFound; 
}

int Graph::get_num_of_vertices() 
{ 
  return n_vertices;
} 

bool Graph::is_player_trivial(PLAYER pl) 
{
  for(vector<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
    if ((*i).get_player() == pl) {
      assert((*i).get_succ_list().begin() != (*i).get_succ_list().end());
      
      if ((*i).get_succ_list().size() > 1) return false;
    }
  }
  return true;
}

set<int> Graph::computeAttractor(set<int> target, PLAYER pl) 
{
  set<int> result = target;
  set<int> frontier;
  
  do {
    
    frontier = Graph::preImage(result, pl);
    
    result.insert(frontier.begin(), frontier.end());
    
  } while (!frontier.empty());
  
  return result;
}

set<int> Graph::computeAttractorVertex(set<int> vidSet)
{
	int vid = *(vidSet.begin());
	map<int, bool> visited;
	map<int, bool> present;
	for (vector<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++)
	{
		int id = (*i).get_id();
		visited[id] = false;
		present[id] = false;
	}
	
	set<int> result;
	stack<int> traverse;
	traverse.push(vid);
	int curr;
	while(traverse.empty() == false) {
		curr = traverse.top();
		traverse.pop();
		vector<int> pred = get_vertex(curr).get_pred_list();
		visited[curr] = true;
		result.insert(curr);
		for(vector<int>::iterator it = pred.begin(); it!=pred.end(); it++)
		{
			if(!visited[*it] && !present[*it]) 
			{
				present[*it] = true;
				traverse.push(*it);
			}
		}
	}
	return result;
}

set<int> Graph::computeClosedVertices(set<int> target)
{
  set<int> result = target;
  set<int> frontier;
  
  do {
    frontier = Graph::preImageClosed(result);
    result.insert(frontier.begin(), frontier.end());
  } while (!frontier.empty());
  
  return result;
}


set<int> Graph::preImage(set<int> target, PLAYER pl) 
{
  set<int> result;
  
  for(vector<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
    if (target.find((*i).get_id())== target.end()) { 
      //if the vertex is not already inside the target
 
      vector<int> t_succ = (*i).get_succ_list();
      assert(t_succ.size() != 0);

      if ((*i).get_player() == pl) {
	// Only one of the successor needs to be inside target
	bool flag = false;
	
	for(vector<int>::iterator j = t_succ.begin(); j != t_succ.end(); j++) {
	  if (target.find(*j) != target.end())  flag = true; 
	}
	
	if (flag) result.insert((*i).get_id()); 
      }
      else {
	//All of the succressors need to be in the target
	bool flag = true;
	
	for(vector<int>::iterator j = t_succ.begin(); j != t_succ.end(); j++) {
	  if (target.find(*j) == target.end()) flag = false;
	}

	if (flag) result.insert((*i).get_id());
	
      }
    }
  }
  
  return result;
}

// changed
set<int> Graph::preImageClosed(set<int> target)
{
  set<int> result;
  
  for(vector<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
    if (target.find((*i).get_id())== target.end()) { 
      //if the vertex is not already inside the target 
      vector<int> t_succ = (*i).get_succ_list();
      bool flag=false;
      for(vector<int>::iterator j = t_succ.begin(); j != t_succ.end(); j++) {
		if (target.find(*j) != target.end()) { flag = true; break;}//changed '==' to '!='
      }
      if (flag) result.insert((*i).get_id());//changed '!flag' to 'flag'
    }   
  }
  
  return result;
}

Graph Graph::computeSubGame(set<int> vert_set_original)
{
  Graph result;
  set<int> vert_set = vert_set_original;
  //  set<int> vert_set = Graph::computeClosedVertices(vert_set_original);
  
  for (vector<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
    if (vert_set.find((*i).get_id()) == vert_set.end()) {
      // If the vertex *i is not in the vert_set 
      result.add_vertex((*i).get_label(), (*i).get_id(), (*i).get_priority(), (*i).get_player());  
      
      vector<int> succ_list = (*i).get_succ_list();
      vector<int>::iterator j = succ_list.begin();
      
      while (j != succ_list.end()) {
	if (vert_set.find(*j) == vert_set.end()) {
	  // If the vertex_id *j  is not in the vert_set 
	  result.get_vertex((*i).get_id()).add_succ(*j);
	}
	j++;
      }
    }
  }
  result.fill_predecessors();
  
  return result;
}

		
Graph Graph::computeSubGame1(set<int> vert_set_original)
{
  Graph result;
  set<int> vert_set = vert_set_original;
  //  set<int> vert_set = Graph::computeClosedVertices(vert_set_original);
  
  for (vector<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
    if (vert_set.find((*i).get_id()) != vert_set.end()) {
      // If the vertex *i is not in the vert_set 
      result.add_vertex((*i).get_label(), (*i).get_id(), (*i).get_priority(), (*i).get_player());  
      
      vector<int> succ_list = (*i).get_succ_list();
      vector<int>::iterator j = succ_list.begin();
      
      while (j != succ_list.end()) {
	if (vert_set.find(*j) != vert_set.end()) {
	  // If the vertex_id *j  is not in the vert_set 
	  result.get_vertex((*i).get_id()).add_succ(*j);
	}
	j++;
      }
    }
  }
  result.fill_predecessors();
  
  return result;
}
		
		
		
		


Strategy Graph::getStrategyFromWinningSet(set<int> even_win_set, STRAT_TYPE type)
{
  Strategy sigma;

  sigma.set_type(type);
  
  switch (type) {
    
  case s_even:
    for (vector<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
      if ((*i).get_player()==even) {
	vector<int> succ_list = (*i).get_succ_list();
	// Every vertex has at least one successor
	assert(succ_list.begin() != succ_list.end());
	
	bool flag = true;
	for (vector<int>::iterator it = succ_list.begin(); it != succ_list.end(); it++) {
	  if (even_win_set.find(*it) != even_win_set.end()) {
	    sigma.set_decision((*i).get_id(), (*it));
	    flag = false;
	    break;
	  }
	}
	if (flag) {
	  int dec = *(succ_list.begin());
	  
	  sigma.set_decision((*i).get_id(), dec);
	}
      }
    }  
    break;
  
  case s_odd:
    for (vector<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
      if ((*i).get_player()==odd) {
	vector<int> succ_list = (*i).get_succ_list();
	// Every vertex has at least one successor
	assert(succ_list.begin() != succ_list.end());
	
	bool flag = true;
	for (vector<int>::iterator it = succ_list.begin(); it != succ_list.end(); it++) {
	  if (even_win_set.find(*it) == even_win_set.end()) {
	    sigma.set_decision((*i).get_id(), (*it));
	    flag = false;
	    break;
	  }
	}
	if (flag) {
	  int dec = *(succ_list.begin());
	  
	  sigma.set_decision((*i).get_id(), dec);
	}
      }
    }  
    break;
        
  case s_both:
    for (vector<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
	vector<int> succ_list = (*i).get_succ_list();
	// Every vertex has at least one successor
	assert(succ_list.begin() != succ_list.end());
	
	bool flag = true;
	for (vector<int>::iterator it = succ_list.begin(); it != succ_list.end(); it++) {
	  if ((*i).get_player()==odd) {
	    if (even_win_set.find(*it) == even_win_set.end()) {
	      sigma.set_decision((*i).get_id(), (*it));
	      flag = false;
	      break;
	    }
	  }
	  else  {
	    if (even_win_set.find(*it) == even_win_set.end()) {
	      sigma.set_decision((*i).get_id(), (*it));
	      flag = false;
	      break;
	    }
	  }
	}
	if (flag) {
	  int dec = *(succ_list.begin());
	  
	  sigma.set_decision((*i).get_id(), dec);
	}
    }  
    break;

  case s_none:
    break;
  }
  
  return sigma;
}


Strategy Graph::getArbitraryStrategy(STRAT_TYPE type)
{
  Strategy sigma;

  sigma.set_type(type);
  
  switch (type) {
    
  case s_even:
    for (vector<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
      if ((*i).get_player()==even) {
	vector<int> succ_list = (*i).get_succ_list();
	// Every vertex has at least one successor
	assert(succ_list.begin() != succ_list.end());
	
	int dec = *(succ_list.begin());
	
	sigma.set_decision((*i).get_id(), dec);
      }
    }  
    break;
  
  case s_odd:
    for (vector<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
      if ((*i).get_player()==odd) {
	vector<int> succ_list = (*i).get_succ_list();
	vector<int>::iterator j = succ_list.begin();
	
	// Every vertex has at least one successor
	assert(succ_list.begin() != succ_list.end());
	
	int dec = *(succ_list.begin());
	
	sigma.set_decision((*i).get_id(), dec);
      }
    }  
    break;
        
  case s_both:
    for (vector<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
      vector<int> succ_list = (*i).get_succ_list();
      vector<int>::iterator j = succ_list.begin();
      
      // Every vertex has at least one successor
     	 assert(succ_list.begin() != succ_list.end());
      
	 int dec = *(succ_list.begin());
	 
      sigma.set_decision((*i).get_id(), dec);
    }  
    break;

  case s_none:
    break;
  }
  
  return sigma;
}


Strategy Graph::getRandomStrategy(STRAT_TYPE type)
{
  Strategy sigma;

  //  srand(time(NULL));

  sigma.set_type(type);
  
  switch (type) {
    
  case s_even:
    for (vector<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
      if ((*i).get_player()==even) {
	vector<int> succ_list = (*i).get_succ_list();
	// Every vertex has at least one successor
	assert(succ_list.begin() != succ_list.end());
	
		int dec = succ_list[rand()%succ_list.size()];
	//	int dec = *(succ_list.begin());
	
	sigma.set_decision((*i).get_id(), dec);
      }
    }  
    break;
  
  case s_odd:
    for (vector<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
      if ((*i).get_player()==odd) {
	vector<int> succ_list = (*i).get_succ_list();
	vector<int>::iterator j = succ_list.begin();
	
	// Every vertex has at least one successor
	assert(succ_list.begin() != succ_list.end());
	
	int dec = succ_list[rand()%succ_list.size()];
	// int dec = *(succ_list.begin());
	
	sigma.set_decision((*i).get_id(), dec);
      }
    }  
    break;
        
  case s_both:
    for (vector<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
      vector<int> succ_list = (*i).get_succ_list();
      vector<int>::iterator j = succ_list.begin();
      
      // Every vertex has at least one successor
     	 assert(succ_list.begin() != succ_list.end());
      
   
	 int dec = succ_list[rand()%succ_list.size()];
	 // int dec = *(succ_list.begin());
	 
      sigma.set_decision((*i).get_id(), dec);
    }  
    break;

  case s_none:
    break;
  }
  
  return sigma;
}

Graph Graph::applyStrategy(Strategy sigma)
{
  Graph result;
  
  for (vector<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
    
    result.add_vertex((*i).get_label(), (*i).get_id(), (*i).get_priority(), (*i).get_player()); 
    
    switch (sigma.type) {
    case s_odd:
      if ((*i).get_player()==odd) {
	result.get_vertex((*i).get_id()).add_succ(sigma.get_decision((*i).get_id()));
      }
      else {
	vector<int> succ_list = (*i).get_succ_list();
	vector<int>::iterator j = succ_list.begin();
	
	while (j != succ_list.end()) {
	  result.get_vertex((*i).get_id()).add_succ(*j);
	  j++;
	}
      }
      break;
      
    case s_even:
      if ((*i).get_player()==even) {
    	result.get_vertex((*i).get_id()).add_succ(sigma.get_decision((*i).get_id()));
      }
      else {
    	vector<int> succ_list = (*i).get_succ_list();
    	vector<int>::iterator j = succ_list.begin();
	
    	while (j != succ_list.end()) {
    	  result.get_vertex((*i).get_id()).add_succ(*j);
    	  j++;
    	}
      }
      break;
      
    case s_both:
      result.get_vertex((*i).get_id()).add_succ(sigma.get_decision((*i).get_id()));
      break;
   
    case s_none:
      vector<int> succ_list = (*i).get_succ_list();
      vector<int>::iterator j = succ_list.begin();
      
      while (j != succ_list.end()) {
	result.get_vertex((*i).get_id()).add_succ(*j);
    	  j++;
    	}
    	break;
    }
  }
  
  result.fill_predecessors();

  return result;
}



PLAYER Graph::opponent(PLAYER pl) 
{
  if (pl==even) return odd; else return even;
}

bool Graph::toss_a_coin()
{
  if (rand()%2 == 0) return true;
  else return false;
}

int Graph::get_sample(const std::set<int>& s) 
{
  double r = rand() % s.size();
  std::set<int>::iterator it = s.begin();
  
  for (; r != 0; r--) it++;
  return *it;
}

pair<set<int>, set<int> > Graph::PGSolve()
{
  set<int> even_win_set;
  set<int> odd_win_set;

    if (vertices.begin() == vertices.end()) {
    assert(even_win_set.begin()==even_win_set.end());
    assert(odd_win_set.begin()==odd_win_set.end());
    
    return make_pair(even_win_set, odd_win_set); 
  }
  else {
    int highest_priority = *(priority_set.rbegin());
    PLAYER pl = highest_priority%2==0?even:odd;
    set<int> Y = get_vertices_of_parity(highest_priority);
    
    if (pl == even) {
      pair< set<int>, set<int> > result = (computeSubGame(computeAttractor(Y, even))).PGSolve(); 
      
      if ((result.second).begin() == (result.second).end()) {
	// if W_1 is empty then W_0 = V
	for(vector<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
	  even_win_set.insert((*i).get_id());
	}
	
	assert(odd_win_set.begin() == odd_win_set.end());
	
	return make_pair(even_win_set, odd_win_set);
      }
      else {
	// W_0 is the winning region in G minus Atrr_1(W_1), and W_1 is the remaining.
	result = (computeSubGame(computeAttractor(result.second, odd))).PGSolve(); 
	even_win_set = result.first;
	
	for(vector<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
	  if (even_win_set.find((*i).get_id()) == even_win_set.end()) 
	    odd_win_set.insert((*i).get_id());
	}
	
	return make_pair(even_win_set, odd_win_set);
      }
    }
    else { 
      pair< set<int>, set<int> > result = (computeSubGame(computeAttractor(Y, odd))).PGSolve(); 
      
      if ((result.first).begin() == (result.first).end()) {
      	// if W_0 is empty then W_1 = V
	for(vector<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
      	  odd_win_set.insert((*i).get_id());
      	}
	
	assert(even_win_set.begin() == even_win_set.end());

      	return make_pair(even_win_set, odd_win_set);
      }
      else {
	// W_1 is the winning region in G minus Atrr_0(W_0), and W_0 is the remaining.
	result = (computeSubGame(computeAttractor(result.first, even))).PGSolve(); 
	odd_win_set = result.second;
	
	for(vector<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
	  if (odd_win_set.find((*i).get_id()) == odd_win_set.end()) 
	    even_win_set.insert((*i).get_id());
	}
	
	return make_pair(even_win_set, odd_win_set);
      }
    }
  }
}
//
// Can vid reach itself while avoiding vertices of higher priorities? 
//
bool Graph::can_self_reach_one(int vid, PLAYER pl) 
{
  set<int> target;
  set<int> frontier;

  do {
    frontier.clear();
    for(vector<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
      if ((target.find((*i).get_id())== target.end()) && ((*i).get_priority() <= get_vertex(vid).get_priority())) { 

	vector<int> t_succ = (*i).get_succ_list();
	
	bool flag = false;
	
	for(vector<int>::iterator j = t_succ.begin(); j != t_succ.end(); j++) {
	  if (((*j)==vid) || (target.find(*j) != target.end()))  flag = true; 
	}
	
	if (flag) {
	  if ((*i).get_id() == vid) return true;
	  else frontier.insert((*i).get_id()); 
	}
      }
    }
  
    target.insert(frontier.begin(), frontier.end());
    
  } while (!frontier.empty());
  
  return false;
}
set< set<int> > Graph::generateSCCs()
{
  set< set<int> > result;
  
  return result;
}


bool Graph::can_self_reach_zero(int vid) 
{
  set<int> traversed;
  int curr = vid;
  
  // A vertex can not reach itself if the vertex has no predecessor
  if (get_vertex(vid).get_pred_list().empty())
    return false;
  
  while (true) {
    int succ = (*get_vertex(curr).get_succ_list().begin());
  
    if (succ == vid) return true;
    if (traversed.find(succ) != traversed.end()) return false;
    
    traversed.insert(curr);
    curr = succ;
  }
}

/*
bool Graph::can_self_reach_itself(int vid)
{
  set<int> traversed;
  int curr = vid;
  int curr_priority = get_vertex(vid).priority;
  
  // A vertex can not reach itself if the vertex has no predecessor
  if (get_vertex(vid).get_pred_list().empty())
    return false;
	
  while(true) {
	  vector<int> successors = (*get_vertex(curr).get_succ_list());
	  
	  for(vector<int>::iterator it = successors.begin(); it!=successors.end(); it++) {
		  int succ = *it;
		  if(curr_priority < get_vertex(succ).priority) break;
		  if(succ == vid) return true;
	  }
	  
  }
}
*/
bool Graph::DFSUtil(int v, bool visited[], int curr_priority, int vid)
{
    // Mark the current node as visited and print it
    visited[v] = true;
    //cout << v << " ";
    bool temp = false;
    // Recur for all the vertices adjacent to this vertex
	vector<int> successors = get_vertex(v).get_succ_list();
	for(vector<int>::iterator it = successors.begin(); it!=successors.end(); it++) {
		if(*it == vid) return true;
		if(!visited[*it]) {
			if(curr_priority < get_vertex(*it).get_priority()) continue;
			if(!DFSUtil(*it, visited, curr_priority, vid)) continue;
			else return true;
		}
	}
	return false;
}
 
// DFS traversal of the vertices reachable from v. It uses recursive DFSUtil()
bool Graph::DFS(int v)
{
    // Mark all the vertices as not visited
    int V = get_num_of_vertices();
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;
	int curr_priority = get_vertex(v).get_priority();
    // Call the recursive helper function to print DFS traversal
    return DFSUtil(v, visited, curr_priority, v);
}

// A recursive function used by longestPath. See below link for details
// http://www.geeksforgeeks.org/topological-sorting/
void Graph::topologicalSortUtil(int v, bool visited[], stack<int> &Stack)
{
    // Mark the current node as visited
    visited[v] = true;
    
 
    // Recur for all the vertices adjacent to this vertex
    vector<int> pred = get_vertex(v).get_pred_list();
    for (vector<int>::iterator it = pred.begin(); it != pred.end(); ++it)
    {
        if (!visited[*it])
            topologicalSortUtil(*it, visited, Stack);
    }
 
    // Push current vertex to stack which stores topological sort
    //cout << get_vertex(v).get_priority() << " ";
    Stack.push(v);
 
}
 
// The function to find longest distances from a given vertex. It uses
// recursive topologicalSortUtil() to get topological sorting.
void Graph::longestPath(int vid, Valuation &val)
{
    stack<int> Stack;
    int V = get_num_of_vertices();
    int dist[V];
    map<int, vector<int> > list_priority;
 
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
 
    // Call the recursive helper function to store Topological Sort
    // starting from all vertices one by one
    //cout << "Topological Sort - ";
    topologicalSortUtil(vid, visited, Stack);
    
    //cout  << endl;
    //Initialize distances to all vertices as infinite and distance
    // to source as 0
    for (int i = 0; i < V; i++)
        dist[i] = NINF;
    dist[vid] = 0;
    vector <int> temp;
    temp.push_back(get_vertex(vid).get_priority());    
    list_priority[vid] = temp;
 
    // Process vertices in topological order
    while (Stack.empty() == false)
    {
        // Get the next vertex from topological order
        int u = Stack.top();
        Stack.pop();
 
        // Update distances of all adjacent vertices
        //cout << "u - " << u << endl;
        vector<int> pred = get_vertex(u).get_pred_list();
        if (dist[u] != NINF)
        {
		  //cout << "in" << endl;
          for (vector<int>::iterator it = pred.begin(); it != pred.end(); ++it)
             if (dist[*it] < dist[u] + 1) {
				vector<int> t5 = list_priority[u];
				t5.push_back(get_vertex(*it).get_priority());
                list_priority[*it] = t5; 
                dist[*it] = dist[u] + 1;
			}
        }
    }
    int key_priority = get_vertex(vid).get_priority();
 
    // Print the calculated longest distances
    for (vector<Vertex>::iterator it1 = vertices.begin(); it1!= vertices.end(); it1++) {
		int i = (*it1).get_id();
        if(dist[i] == NINF){
			cout << "INF - Check something is wrong" << endl;
			exit(1);
		}
		else {
			Value v(key_priority,dist[i]);
			//cout << get_vertex(i).get_priority() << " " << dist[i] << " ";
			vector<int> s = list_priority[i];
			set<int> temp;
			v.set_transient_priority_set(temp);
			for(vector<int>::iterator it = s.begin(); it!= s.end(); it++) 
			{
				//cout << *it << " ";
				v.add_transient(*it);
			}
			val.set_value(i, v);
			//cout << endl;
		}
	}
	//show(val);
	return;
	
	//exit(1);
}

int Graph::minDistance(map<int, int> &dist, map<int, bool> &sptSet)
{
   // Initialize min value
   int min = INT_MAX, min_index;
 
   for (vector<Vertex>::iterator it1 = vertices.begin(); it1!= vertices.end(); it1++) {
     int v = (*it1).get_id();
     if (sptSet[v] == false && dist[v] <= min)
         min = dist[v], min_index = v;
	 }
 
   return min_index;
}
  
// Funtion that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void Graph::dijkstra(int src, Valuation &val)
{
     //int dist[V];     // The output array.  dist[i] will hold the shortest
                      // distance from src to i
     map<int, int> dist;
     map<int, vector<int> > list_priority;
 
     //bool sptSet[V]; // sptSet[i] will true if vertex i is included in shortest
                     // path tree or shortest distance from src to i is finalized
	 map<int, bool> sptSet;
     // Initialize all distances as INFINITE and stpSet[] as false
     for (vector<Vertex>::iterator it1 = vertices.begin(); it1!= vertices.end(); it1++) {
        int i = (*it1).get_id();
        dist[i] = INT_MAX, sptSet[i] = false;
	 }
 
     // Distance of source vertex from itself is always 0
     dist[src] = 0;
     vector <int> temp;
	 temp.push_back(get_vertex(src).get_priority());    
     list_priority[src] = temp;
 
     // Find shortest path for all vertices
     for (int count = 0; count < get_num_of_vertices()-1; count++)
     {
       // Pick the minimum distance vertex from the set of vertices not
       // yet processed. u is always equal to src in first iteration.
       int u = minDistance(dist, sptSet);
       
       // Mark the picked vertex as processed
       sptSet[u] = true;
 
       // Update dist value of the adjacent vertices of the picked vertex.
       vector<int> pred = get_vertex(u).get_pred_list();
       for(vector<int>::iterator it = pred.begin(); it!=pred.end(); it++) {
		   if(!sptSet[*it] && dist[u] != INT_MAX && dist[u]+1 < dist[*it]) {
				dist[*it] = dist[u] + 1;
				vector<int> temp = list_priority[u];
				temp.push_back(get_vertex(*it).get_priority());
				list_priority[*it] = temp;
		   }
	   }
     }
     int key_priority = get_vertex(src).get_priority();
     
     for(vector<Vertex>::iterator it1 = vertices.begin(); it1!= vertices.end(); it1++) 
     {
		 int id = (*it1).get_id();
		 if(dist[id] == INT_MAX) 
		 {
			 cout << "Check - Something is wrong" << endl;
			 exit(1);
		 }
		 Value v(key_priority, dist[id]);
		 set<int> temp;
		 v.set_transient_priority_set(temp);	
		 //cout << "Shortest distances" ;
		 //cout << (*it1).get_priority() << " " << dist[id] << " ";
		 for(vector<int>::iterator it = list_priority[id].begin(); it!=list_priority[id].end(); it++)
		 {
			 //cout << *it << " ";
			 v.add_transient(*it);
		 }
		 //cout << endl;
		 val.set_value(id, v);
	 }
	 //show(val);
	 //exit(1);
	 return;
}


Valuation Graph::edgeRemove(int vid, PLAYER pl, Valuation &result)
{
	vector<int> succ = get_vertex(vid).get_succ_list();
	for(vector<int>::iterator it = succ.begin(); it!=succ.end(); it++)
	{
		get_vertex(vid).delete_succ(*it);
		get_vertex(*it).delete_pred(vid);
	}
	
	int curr_priority = get_vertex(vid).get_priority();
	for(vector<int>::iterator it = priority_sorted_vertex_list.begin(); it!=priority_sorted_vertex_list.end();it++)
	{
		//cout << *it << " " << get_vertex(*it).get_priority() << endl;
		if(get_vertex(*it).get_priority() <= curr_priority) continue;
		// We have got our r
		if((get_vertex(*it).get_priority())%2 == 0)
		//r is in R+ - parity even
		{
			//cout << *it << " " << get_vertex(*it).get_priority() << " edgeRemove - case 1" << endl;
			set<int> updatedVertices;
			set<int> setVertices;
			for (vector<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++)
			{
				setVertices.insert((*i).get_id());
				if((*i).get_id()!= *it)
				{
					updatedVertices.insert((*i).get_id());
				}
			}
			Graph updatedGraph = computeSubGame1(updatedVertices);
			set<int> target;
			target.insert(vid);
			set<int> requiredVertices = updatedGraph.computeAttractorVertex(target);//W
			//set<int> check = updatedGraph.computeClosedVertices(target);
			//if(requiredVertices!=check) cout << "Wrong" << endl;
			set<int> set2;
			set_difference(setVertices.begin(),setVertices.end(),
				requiredVertices.begin(),requiredVertices.end(),
				inserter(set2,set2.begin()));
			//set<int> set1 = 
			requiredVertices.insert(*it);
			for(set<int>::iterator i=requiredVertices.begin();i!=requiredVertices.end();i++)
			{
				for(set<int>::iterator j=set2.begin(); j!=set2.end();j++)
				{
					vector<int> tempSuccessors = get_vertex(*i).get_succ_list();
					for(vector<int>::iterator k=tempSuccessors.begin();k!=tempSuccessors.end();k++)
					{
						if(*j==*k) 
						{
							get_vertex(*i).delete_succ(*j);
							get_vertex(*j).delete_pred(*i);
						}
					}
				}
			}
			//break;
		}
		else
		//r is in R- odd
		{
			//break;
			//cout << *it << " " << get_vertex(*it).get_priority() << " edgeRemove - case 2" << endl;
			//set<int> updatedVertices;
			set<int> setVertices;
			for (vector<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++)
			{
				setVertices.insert((*i).get_id());
			}
			set<int> target;
			target.insert(*it);
			set<int> requiredVertices = computeAttractorVertex(target);//U
			set<int> set2;// V\U
			set_difference(setVertices.begin(),setVertices.end(),
				requiredVertices.begin(),requiredVertices.end(),
				inserter(set2,set2.begin()));
			for(set<int>::iterator i=requiredVertices.begin();i!=requiredVertices.end();i++)
			// U\{r}
			{
				if((*i)==(*it)) requiredVertices.erase(i);
			}
			for(set<int>::iterator i=requiredVertices.begin();i!=requiredVertices.end();i++)
			{
				for(set<int>::iterator j=set2.begin(); j!=set2.end();j++)
				{
					vector<int> tempSuccessors = get_vertex(*i).get_succ_list();
					for(vector<int>::iterator k=tempSuccessors.begin();k!=tempSuccessors.end();k++)
					{
						if(*j==*k) 
						{
							get_vertex(*i).delete_succ(*j);
							get_vertex(*j).delete_pred(*i);
						}
					}
				}
			}
			//break;
		}
		
	}

	int key_priority = get_vertex(vid).get_priority();
	Value key_vertex_val(key_priority, 0);
	
	result.set_value(vid, key_vertex_val);
	if((get_vertex(vid).get_priority())%2 == 0)
	// t is in R+
	{
		// longest distances
		longestPath(vid, result);
		//cout << "Came - longest distances" << endl;
	}
	else
	{
		// shortest distances
		dijkstra(vid, result);
		//cout << "Came - shortest distances" << endl;
	}
	return result;
}
	

pair<Strategy, int>  Graph::strategyImprovement(PLAYER pl)
{
  pair<Strategy, int> result;;
  
  if (even_vertices.size() == 0) {
    result = strategyImprovement_one(odd);
  }
  
  else if (odd_vertices.size() == 0) {
    result = strategyImprovement_one(even);
  }
  else {
    result = strategyImprovement_two(pl);
  }
    
  return result;
}


pair<Strategy, int> Graph::symStrategyImprovement()
{
  //cout << "I am here" << endl;
  pair<Strategy, int> result;;
  
  if (even_vertices.size() == 0) {
    result = strategyImprovement_one(odd);
  }
  
  else if (odd_vertices.size() == 0) {
    result = strategyImprovement_one(even);
  }
  
  else result  = symStrategyImprovement_two();

  return result;
}



pair<Strategy, int> Graph::strategyImprovement_one(PLAYER pl)
{
  assert(is_player_trivial(opponent(pl)));

  // Strategy sigma  = (pl==even)?getStrategyFromWinningSet(PGSolve().first, s_even):getStrategyFromWinningSet(PGSolve().first, s_odd);
  //  Strategy sigma  = (pl==even)?getRandomStrategy(s_even):getRandomStrategy(s_odd);
  
  Strategy sigma  = (pl==even)?getArbitraryStrategy(s_even):getArbitraryStrategy(s_odd);
  Strategy sigma_prime;
  Valuation val;
  int iter = 0; 
  
  while (true) {
    val = computeValue_one(sigma);
    
    sigma_prime = getImprovedStrategy(sigma, val, pl);
    iter++;
    
    if (sigma == sigma_prime) break;
    else sigma = sigma_prime; 
  } 
  
  return make_pair(sigma, iter);
}
 
pair<Strategy, int> Graph::strategyImprovement_two(PLAYER pl)
{
  Strategy sigma  = (pl==even)?getArbitraryStrategy(s_even):getArbitraryStrategy(s_odd);
  // Strategy sigma  = (pl==even)?getRandomStrategy(s_even):getRandomStrategy(s_odd);
  Strategy sigma_prime;
  Valuation val;
  int iter = 0; 

  while (true) {
    val = computeValue_two(sigma, pl);
    
    sigma_prime = getImprovedStrategy(sigma, val, pl);
    iter++;
    
    if (sigma == sigma_prime) break;
    else sigma = sigma_prime;
   
    if (iter == SymSIM_TIMEOUT) break; // Time-out 
  }

  return make_pair(sigma, iter);
}


// pair<Strategy, int> Graph::randomFacet(PLAYER pl) 
// {
//   Strategy sigma  = (pl==even)?getArbitraryStrategy(s_even):getArbitraryStrategy(s_odd);
//   Strategy sigma_prime;
//   Valuation val;
//   int iter = 0; 
  
//   while (true) {
//     val = computeValue_two(sigma, pl);
    
//     sigma_prime = getImprovedStrategyRF(sigma, val, pl);
//     iter++;

//     if (sigma == sigma_prime) break;
//     else sigma = sigma_prime;
   
//     if (iter == SymSIM_TIMEOUT) break; // Time-out 
//   }

//   return make_pair(sigma, iter);
// }

void Graph::show_random()
{
  for (vector<int>::iterator it = randomized_vertices_list.begin(); it != randomized_vertices_list.end(); it++) 
    {
      cout <<  *it << " ";
    }
  cout << "\n";
  getchar();
}


pair<Strategy, int> Graph::symStrategyImprovement_two()
{
  Strategy sigma = getArbitraryStrategy(s_even);
  Strategy tau  = getArbitraryStrategy(s_odd);
  Strategy sigma_prime, sigma_counter_tau;
  Strategy tau_prime, tau_counter_sigma;

  Strategy sigma_dprime, tau_dprime;;

  PLAYER pl = even;

  Valuation val_sigma;
  Valuation val_tau;
  
  int iter = 0; 
  
  while (true) {
    
    val_sigma = computeValue_two(sigma, pl);
    val_tau  = computeValue_two(tau, opponent(pl));

    sigma_counter_tau = applyStrategy(tau).strategyImprovement_one(pl).first;
    tau_counter_sigma = applyStrategy(sigma).strategyImprovement_one(opponent(pl)).first;

    sigma_prime = getImprovedStrategy(sigma, val_sigma, pl, sigma_counter_tau);
    tau_prime = getImprovedStrategy(tau, val_tau, opponent(pl), tau_counter_sigma);

    sigma_dprime = getImprovedStrategy(sigma, val_sigma, pl);
    tau_dprime = getImprovedStrategy(tau, val_tau, opponent(pl));

    iter++;
    
    if ((sigma == sigma_dprime))
      return make_pair(sigma, iter);

    if ((tau == tau_dprime))
      return make_pair(tau, iter);

    if ((sigma == sigma_prime) && (tau == tau_prime)) 
      return make_pair(sigma, iter);
    
    sigma = sigma_prime;
    tau = tau_prime;
    
    if (iter == SymSIM_TIMEOUT) make_pair(sigma, iter); // Time-out 
    
  }
  
  assert(false);
}


// pair<Strategy, int> Graph::symStrategyImprovement_two()
// {
//   Strategy sigma = getArbitraryStrategy(s_even);
//   Strategy tau  = getArbitraryStrategy(s_odd);
//   Strategy sigma_prime, sigma_counter_tau;
//   Strategy tau_prime, tau_counter_sigma;

//   PLAYER pl = even;

//   Valuation val_sigma;
//   Valuation val_tau;
  
//   int iter = 0; 
  
//   while (true) {
//     val_sigma = computeValue_two(sigma, pl);
//     val_tau  = computeValue_two(tau, opponent(pl));

//     sigma_counter_tau = applyStrategy(tau).strategyImprovement_one(pl).first;
//     tau_counter_sigma = applyStrategy(sigma).strategyImprovement_one(opponent(pl)).first;

//     sigma_prime = getImprovedStrategy(sigma, val_sigma, pl, sigma_counter_tau);
//     tau_prime = getImprovedStrategy(tau, val_tau, opponent(pl), tau_counter_sigma);

//     iter++;
    
//     if ((sigma == sigma_prime) && (tau == tau_prime)) return make_pair(sigma, iter);
    
//     sigma = sigma_prime;
//     tau = tau_prime;
//   }
  
//   assert(false);
// }


Strategy Graph::getImprovedStrategy(Strategy sigma, Valuation v, PLAYER pl, Strategy sigma_helper)
{
  Strategy sigma_prime;
  sigma_prime.set_type(sigma.type);
  Improvements improvements = get_improvements(sigma, v, pl);
  
  for (vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); it++) {
    int curr_v_id = (*it).get_id();
    PLAYER curr_v_player = (*it).get_player();
    
    if (curr_v_player == pl) {
      set<int> improving_switches = improvements.get_switches(curr_v_id);
      int vx_in_helper_edge = sigma_helper.get_decision(curr_v_id);

      if (improving_switches.find(vx_in_helper_edge) != improving_switches.end()) 
	sigma_prime.set_decision(curr_v_id, vx_in_helper_edge);
      else {
	//	int opt = *improvements.get_switches(curr_v_id).rbegin();
	//	sigma_prime.set_decision(curr_v_id, opt);
	sigma_prime.set_decision(curr_v_id, sigma.get_decision(curr_v_id));
      }
    }
  }
  
  return sigma_prime;
}


Strategy Graph::getImprovedStrategy(Strategy sigma, Valuation v, PLAYER pl)
{
  Strategy sigma_prime;
  sigma_prime.set_type(sigma.type);

  Improvements improvements = get_improvements(sigma, v, pl);

  if (improvements.get_strictly_improving_vertices().empty()) {
    for (vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); it++) {
      int curr_v_id = (*it).get_id();
      PLAYER curr_v_player = (*it).get_player();
      if (curr_v_player == pl) {
	sigma_prime.set_decision(curr_v_id, sigma.get_decision(curr_v_id));
      } 
    }
    
    return sigma_prime;
  }
  
  else {
 
  switch (options.switch_rule) {
  
  case SwitchRandom: // At each vertex randmly choose an optimizing switch

    for (vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); it++) {
      int curr_v_id = (*it).get_id();
      PLAYER curr_v_player = (*it).get_player();
      
      if (curr_v_player == pl) {
	int opt = get_sample(improvements.get_switches(curr_v_id));
	sigma_prime.set_decision(curr_v_id, opt);
      }
    }
    break;

    case RandomEdge: // Randomly choose a vertex and apply a random improving switch there 
    {   
      int random_impr_vertex = get_sample(improvements.get_strictly_improving_vertices());
      
      for (vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); it++) {
	if ((*it).get_player() == pl) {
	  int curr_v_id = (*it).get_id();
	  
	  if (curr_v_id == random_impr_vertex) {
	    int opt = get_sample(improvements.get_switches(curr_v_id));
	    sigma_prime.set_decision(curr_v_id, opt);
	  } 
	  else {
	    sigma_prime.set_decision(curr_v_id, sigma.get_decision(curr_v_id));
	  }
	}
      }
    }
    break;
    
  case RandomFacet: // RandomFacet implemented
    {
      bool flag = false;
    
      for (vector<int>::iterator it = randomized_vertices_list.begin(); it != randomized_vertices_list.end(); it++) {
	if (get_vertex(*it).get_player() == pl) {
	  int curr_v_id = *it;
	  if (!flag) {
	    int opt = get_sample(improvements.get_switches(curr_v_id));
	    sigma_prime.set_decision(curr_v_id, opt);
	    
	    if 
	      (improvements.get_strictly_improving_vertices().find(curr_v_id) != improvements.get_strictly_improving_vertices().end()
	       && 
	       sigma.get_decision(curr_v_id) != sigma_prime.get_decision(curr_v_id)
	       ) 
	      {
		random_shuffle(randomized_vertices_list.begin(), it);
		flag = true;
	      }
	  }
	  else {
	    sigma_prime.set_decision(curr_v_id, sigma.get_decision(curr_v_id));
	  }
	}
      }
    }
    break;
    
 case SwitchHalf: 
   // At each vertex toss_a_coin to decide whether to apply switch. 
   // Can return incorrect value 
   {  
     bool flag = false;
     
     for (vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); it++) {
       int curr_v_id = (*it).get_id();
       PLAYER curr_v_player = (*it).get_player();
       if (curr_v_player == pl) {
	 if (toss_a_coin()) {
	   int opt = get_sample(improvements.get_switches(curr_v_id));
	   sigma_prime.set_decision(curr_v_id, opt);
	   if 
	     (improvements.get_strictly_improving_vertices().find(curr_v_id) != improvements.get_strictly_improving_vertices().end()
	      &&
	      sigma.get_decision(curr_v_id) != sigma_prime.get_decision(curr_v_id)
	      ) 
	     {
	       flag = true;
	     }
	 }
	 else {
	   sigma_prime.set_decision(curr_v_id, sigma.get_decision(curr_v_id));
	 } 
       }
     }
     // The following code is not strictly switchhalf, but added to ensure correctness 
     if (!flag)  {
       int random_impr_vertex = get_sample(improvements.get_strictly_improving_vertices());
       sigma_prime.set_decision(random_impr_vertex, get_sample(improvements.get_switches(random_impr_vertex)));
     }
   }
   break;
   
  default: 
    // SwitchAll  or locally optmizing rule
    //  case SwitchBest:
    //  case SwitchAll:
    // SwitchBest is not implemented 
    //    cout << "default--switchall \n";      
    improvements = get_opt_improvement(sigma, v, pl);
    
    for (vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); it++) {
      int curr_v_id = (*it).get_id();
      PLAYER curr_v_player = (*it).get_player();
      
      if (curr_v_player == pl) {
	int opt = *improvements.get_switches(curr_v_id).rbegin();
	
	sigma_prime.set_decision(curr_v_id, opt);
      }
    }
    break;
  }
  return sigma_prime;
  }
  
}


// Strategy Graph::getImprovedStrategyRF(Strategy sigma, Valuation v, PLAYER pl)
// {
//   Strategy sigma_prime;
//   sigma_prime.set_type(sigma.type);
  
//   Improvements improvements = get_improvements(sigma, v, pl);

//   // if (improvements.get_strictly_improving_vertices().empty()) {
//   //   for (vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); it++) {
//   //     int curr_v_id = (*it).get_id();
//   //     PLAYER curr_v_player = (*it).get_player();
//   //     if (curr_v_player == pl) {
//   // 	sigma_prime.set_decision(curr_v_id, sigma.get_decision(curr_v_id));
//   //     } 
//   //   }
//   //   return sigma_prime;
//   // }
//   //else {
//   //    vector<int>::iterator c_idx; 
//   bool flag = false;
  
//   for (vector<int>::iterator it = randomized_vertices_list.begin(); it != randomized_vertices_list.end(); it++) {
//     PLAYER curr_v_player =  get_vertex(*it).get_player();
//     if (curr_v_player == pl) {
//       if (flag) {
// 	sigma_prime.set_decision(*it, sigma.get_decision(*it));
//       }
//       else {
// 	if (improvements.get_strictly_improving_vertices().find(*it) != improvements.get_strictly_improving_vertices().end()) 
// 	  {
// 	    random_shuffle(randomized_vertices_list.begin(), it);
// 	    //flag = true;
// 	  }
// 	int opt = *improvements.get_switches(*it).rbegin();
// 	sigma_prime.set_decision(*it, opt);
//       }
//     }
//   }

//   //assert(flag);

//   return sigma_prime;
// }

  /*
Strategy Graph::getImprovedStrategy(Strategy sigma, Valuation v, PLAYER pl)
{
Strategy sigma_prime;

  sigma_prime.set_type(sigma.type);

  for (vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); it++) {
    int curr_v_id = (*it).get_id();
    PLAYER curr_v_player = (*it).get_player();
    
    if (curr_v_player == pl) { 
      int opt = get_optimal_successor(curr_v_id, v, sigma.get_decision(curr_v_id), pl); 
      
      sigma_prime.set_decision(curr_v_id, opt);
    }
  }
  
  return sigma_prime;
}
  */

Improvements Graph::get_improvements(Strategy sigma, Valuation valn, PLAYER pl) 
{
  Improvements result;
  result.set_player(pl);

  for (vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); it++) {
    int curr_v_id = (*it).get_id();
    PLAYER curr_v_player = (*it).get_player();
    vector<int> succ_v = (*it).get_succ_list();
    
    if (curr_v_player == pl) {
      int curr_succ  = sigma.get_decision(curr_v_id);
      Value curr_succ_val = valn.get_value(curr_succ);
      set<int> impr_sw; 

      for (vector<int>::iterator j = succ_v.begin(); j != succ_v.end(); j++) {
      	Value this_val = valn.get_value(*j);

      	if (pl == odd) {
	  if (this_val < curr_succ_val)  impr_sw.insert(*j); 
      	}
      	else {
      	  if (this_val > curr_succ_val)   impr_sw.insert(*j); 
      	}
      }
      
      if (impr_sw.empty()) {
	impr_sw.insert(curr_succ);
      }
      else {
	// This assert is temporary and catches the case when improving switch is the older one
	assert(impr_sw.find(curr_succ)==impr_sw.end());
	result.add_strictly_improving_vertex(curr_v_id);
      }
      
      result.set_switches(curr_v_id, impr_sw);
    }
  }
  
  return result;
}

Improvements Graph::get_opt_improvement(Strategy sigma, Valuation valn, PLAYER pl) 
{
  Improvements result;
  result.set_player(pl);
  
  for (vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); it++) {
    int curr_v_id = (*it).get_id();
    PLAYER curr_v_player = (*it).get_player();
    vector<int> succ_v = (*it).get_succ_list();
    
    if (curr_v_player == pl) {
      int opt_succ  = sigma.get_decision(curr_v_id);
      Value opt_val = valn.get_value(opt_succ);
      bool strict_impr_flag = false; 
      set<int> impr_sw; 

      for (vector<int>::iterator j = succ_v.begin(); j != succ_v.end(); j++) {
      	Value this_val = valn.get_value(*j);

      	if (pl == odd) {
	  if (this_val < opt_val)  {opt_val = this_val; opt_succ = *j; strict_impr_flag = true;}
      	}
      	else {
      	  if (this_val > opt_val)   {opt_val = this_val; opt_succ = *j; strict_impr_flag = true;}
      	}
      }
      
      impr_sw.insert(opt_succ);
      
      if (strict_impr_flag) result.add_strictly_improving_vertex(curr_v_id); 
      
      result.set_switches(curr_v_id, impr_sw);
    }
  }
  
  return result;
}

// int Graph::get_optimal_successor(int id, Valuation valn, int present_succ, PLAYER pl) 
// {
//   Vertex vx = get_vertex(id);
//   vector<int> succ_v = vx.get_succ_list();
  
//   Value opt_val = valn.get_value(present_succ);
//   int opt = present_succ;
  
//   for (vector<int>::iterator j = succ_v.begin(); j != succ_v.end(); j++) {
//     Value this_val = valn.get_value(*j);
    
//     if (pl == odd) {
//       if (this_val < opt_val) {
// 	//	cout << this_val.to_string() << "is < " << opt_val.to_string() << "\n";
// 	opt = (*j);
//         opt_val = this_val;
//       }
//     }
//     else {
//       if (this_val > opt_val) {
// 	//	cout << this_val.to_string() << "is >  " << opt_val.to_string() << "\n";
// 	opt = (*j);
//         opt_val = this_val;
//       }
//     }
//   }
  
//   return opt;
// }

Valuation Graph::computeValue_two(Strategy sigma, PLAYER pl) 
{
  //show(sigma);
  Graph sub_game = applyStrategy(sigma);
  //sub_game.show(sigma);

  assert(sub_game.is_player_trivial(pl));

  //Strategy optimal_counter_strategy  = sub_game.strategyImprovement_one(opponent(pl)).first;
 
  //Valuation v = sub_game.computeValue_one(optimal_counter_strategy);
  //sub_game.show(v);
  //return v;
  return sub_game.computeValueDirect_one(opponent(pl));
}

Valuation Graph::computeValue_one(Strategy s)
{
  Graph sub_game =  applyStrategy(s);

  assert(sub_game.is_player_trivial(even));
  assert(sub_game.is_player_trivial(odd));
  //sub_game.show();
  return sub_game.computeValue_zero();

}

Valuation Graph::computeValueDirect_one(PLAYER pl)
{
  assert(is_player_trivial(opponent(pl)));
  
  Valuation result;
  set<int> waiting;
  
  for (vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); it++) {
    waiting.insert((*it).get_id());
  }
  //show();
  if (pl==even) {
	cout << "pl is even When?" << endl;
	exit(1);  
    for (vector<int>::iterator i = priority_sorted_vertex_list.begin(); i != priority_sorted_vertex_list.end(); i++)  
      { // Consider the vertices from most profitable to least profitable for Player Even
	if (waiting.find(*i) != waiting.end()) 
	  { // If the current vertex is still in the waiting list 
	    if (can_self_reach_one((*i), even)) 
	      { // set distance to 0 and continue for all other vertices that can reach him
		// HERE>>>>>	setValuation(result, *i, backwar 
		// set<int> considering;
		// int key_priority = get_vertex(*i).get_priority();
		// Value key_vertex_val(key_priority, 0);
		
		// considering.insert(*i);
		// result.set_value(*i, key_vertex_val);
		
		// while (!considering.empty()) {
		//   int curr_vertex = *(considering.begin());
		//   considering.erase(considering.begin());
		//   waiting.erase(curr_vertex);
		
		//   vector<int> pred_list = get_vertex(curr_vertex).get_pred_list();
		
		//   for (vector<int>::iterator pit = pred_list.begin(); pit != pred_list.end(); pit++) {
		//     if (waiting.find(*pit) != waiting.end()) {
		// 	// If the vertex is not yet processed 
		// 	// Also check if it is not in considering.. It can not happen in zero player setting.... 
		// 	Value new_vertex_val(key_priority, result.get_value(curr_vertex).get_distance()+1);
		
		// 	new_vertex_val.set_transient_priority_set(result.get_value(curr_vertex).get_transient_priority_set()); 
		// 	new_vertex_val.add_transient(get_vertex(*pit).get_priority());
		
		// 	considering.insert(*pit);
		// 	result.set_value(*pit, new_vertex_val);
		//     }
		//   }
		// }
	      }
	  }
      }
  } // if player is even, also add  else case.
  else {
	set<int> temp;
	for(vector<Vertex>::iterator it = vertices.begin(); it!= vertices.end(); it++)
	{
		temp.insert((*it).get_id());
	}
	//Graph copy = computeSubGame1(temp);
	for (vector<int>::reverse_iterator i = sorted_vertex_list.rbegin(); i != sorted_vertex_list.rend(); ++i)
	{
		if(temp.find(*i) == temp.end()) continue;
		//cout << *i << " " << get_vertex(*i).get_priority() << " ";
		Graph copy = computeSubGame1(temp);
		bool t = copy.DFS(*i);
		//cout << t << endl;
		if(t)
		{
			//cout << "found a t" << endl;
			set<int> defining_vertex ;
			defining_vertex.insert(*i);
			//cout << get_vertex(*i).get_priority() << " - " ;
			set<int> t = copy.computeAttractorVertex(defining_vertex);
			/*
			for(set<int>::iterator it = t.begin(); it!=t.end(); it++) {
				cout << get_vertex(*it).get_priority() << " " ;
			}
			cout << endl;
			*/
			Graph subGame = copy.computeSubGame1(t);
			//cout << get_vertex(*i).get_priority() << " - " ;
			//cout << "Number of vertices - " << subGame.get_num_of_vertices() << endl;
			subGame.edgeRemove(*i,pl,result);
			set<int> tempSet;
			set_difference(temp.begin(), temp.end(), t.begin(), t.end(), inserter(tempSet, tempSet.begin()));
			temp = tempSet;
			//show(result);
			
			//break;
		}
	}
	//cout << "Over" << endl;
	//show(result);
	//exit(1);
  }
  return result;
}

Valuation Graph::computeValue_zero()
{
  
  assert(is_player_trivial(even));
  assert(is_player_trivial(odd));
  
  Valuation result;
  set<int> waiting;
  
  for (vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); it++) {
    waiting.insert((*it).get_id());
  }
  
  for (vector<int>::iterator i = priority_sorted_vertex_list.begin(); i != priority_sorted_vertex_list.end(); i++)  {
    if (waiting.empty()) break;
    
    if (waiting.find(*i) != waiting.end()) {
      if (can_self_reach_zero(*i)) { 
	
	set<int> considering;
	int key_priority = get_vertex(*i).get_priority();
	Value key_vertex_val(key_priority, 0);
	
	considering.insert(*i);
	result.set_value(*i, key_vertex_val);
	
	while (!considering.empty()) {
	  int curr_vertex = *(considering.begin());
	  considering.erase(considering.begin());
	  waiting.erase(curr_vertex);
	  
	  vector<int> pred_list = get_vertex(curr_vertex).get_pred_list();
	  
	  for (vector<int>::iterator pit = pred_list.begin(); pit != pred_list.end(); pit++) {
	    if (waiting.find(*pit) != waiting.end()) {
	      Value new_vertex_val(key_priority, result.get_value(curr_vertex).get_distance()+1);
	      
	      new_vertex_val.set_transient_priority_set(result.get_value(curr_vertex).get_transient_priority_set()); 
	      new_vertex_val.add_transient(get_vertex(*pit).get_priority());
	      
	      considering.insert(*pit);
	      result.set_value(*pit, new_vertex_val);
	    }
	  }
	}
      }
    }
  }
  
  return result;
}


void Graph::show(set<int> v)
{
  string dot_file = (!options.dual)?options.input_file+".dot":options.input_file+"_dual.dot";
  string pdf_file = (!options.dual)?options.input_file+".pdf":options.input_file+"_dual.pdf";
  ofstream outs(dot_file);

  this->output_dot(outs, v);
  outs.close();

  string cmd1 = "dot -Tpdf " + dot_file + " -o" + pdf_file;
  string cmd2 = "xdg-open " + pdf_file + "&"; 
   
  system(cmd1.c_str());
  system(cmd2.c_str());
  
  getchar();
}

void Graph::show(Valuation val)
{
  string dot_file = options.input_file+".dot";
  string pdf_file = options.input_file+".pdf";
  ofstream outs(dot_file);

  this->output_dot(outs, val);
  outs.close();

  string cmd1 = "dot -Tpdf " + dot_file + " -o" + pdf_file;
  string cmd2 = "xdg-open " + pdf_file + "&"; 
   
  system(cmd1.c_str());
  system(cmd2.c_str());
  
  getchar();

}

void Graph::show(Strategy s)
{
  string dot_file = options.input_file+".dot";
  string pdf_file = options.input_file+".pdf";
  ofstream outs(dot_file);
  

  this->output_dot(outs, s);
  
  outs.close();

  string cmd1 = "dot -Tpdf " + dot_file + " -o" + pdf_file;
  string cmd2 = "xdg-open " + pdf_file + "&"; 
   
  system(cmd1.c_str());
  system(cmd2.c_str());
  
  getchar();
}

void Graph::show(Strategy s, Valuation v)
{
  string dot_file = options.input_file+".dot";
  string pdf_file = options.input_file+".pdf";
  ofstream outs(dot_file);
    
  this->output_dot(outs, s, v);
  outs.close();

  string cmd1 = "dot -Tpdf " + dot_file + " -o" + pdf_file;
  string cmd2 = "xdg-open " + pdf_file + "&"; 
   
  system(cmd1.c_str());
  system(cmd2.c_str());
  
  getchar();
  
}

void Graph::show()
{
  string dot_file = options.input_file+".dot";
  string pdf_file = options.input_file+".pdf";
  ofstream outs(dot_file);
    
  this->output_dot(outs);
  outs.close();

  string cmd1 = "dot -Tpdf " + dot_file + " -o" + pdf_file;
  string cmd2 = "xdg-open " + pdf_file + "&"; 
   
  system(cmd1.c_str());
  system(cmd2.c_str());
  
  getchar();
  
}

set<int> Graph::get_vertices_of_parity(int pr){
  set<int> result;

  for(vector<Vertex>::iterator i = vertices.begin(); i!= vertices.end(); i++) {
    if ((*i).get_priority() == pr) result.insert((*i).get_id());
  }
  
  return result;

}

void Graph::make_priorities_unique()
{
  for (vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); it++) {
    int curr_priority = (*it).get_priority();
    int curr_vid = (*it).get_id();
    bool flag = false;
    
    for (vector<Vertex>::iterator jt = vertices.begin(); jt != vertices.end(); jt++) {
      int pr = (*jt).get_priority();
      
      if (((*jt).get_id() != curr_vid) && pr == curr_priority) {
	flag = true; break;
      }
    }
    
    if (flag) {
      // If there are more than one vertices with curr_priority
      for (vector<Vertex>::iterator jt = vertices.begin(); jt != vertices.end(); jt++) {
	int pr = (*jt).get_priority();
	
	if (((*jt).get_id() != curr_vid) && pr >= curr_priority) {
	  (*jt).set_priority(pr+2);
	}
      }
    }
  }
}






Graph Graph::compute_dual_game()
{
  Graph result;
  int K = get_num_of_vertices()+1;
  
  for (vector<Vertex>::iterator i = vertices.begin(); i!= vertices.end(); i++) {
    int o_id = (*i).get_id();
    int o_pr = (*i).get_priority();
    string o_lab = (*i).get_label();
    PLAYER o_pl = (*i).get_player();
    vector<int> o_succ_list = (*i).get_succ_list();
    
    int n_id = K + o_id;
    int n_pr = 1 + o_pr;
    string n_lab =  "\"T_" + o_lab.substr(1, o_lab.size()-1);
    PLAYER n_pl = opponent(o_pl);
    vector<int> n_succ_list;
    
    result.add_vertex(o_lab, o_id, o_pr, o_pl);
    result.add_vertex(n_lab, n_id, n_pr, n_pl);

    for(vector<int>::iterator j = o_succ_list.begin(); j != o_succ_list.end(); j++) {
      result.get_vertex(o_id).add_succ(*j);
      result.get_vertex(n_id).add_succ(K+(*j));
    }
  }
  
  result.fill_predecessors();
  result.make_priorities_unique();
  
  return result;
}

/******************************************************************************
 *    PRIVATE FUNCTION DEFINITIONS
 *****************************************************************************/
void Graph::output_dot(ostream& out)
{
  vector<Vertex>::iterator i;
  
  out << "digraph G { \n";
  for (i = vertices.begin(); i != vertices.end(); i++) {
    string v = (*i).get_label();
    
    if ((*i).get_player() == odd) {
      out << v <<"[label=\"\\N (" << (*i).get_priority() << ")\", color=black, shape=polygon ]\n";
    }
    else {
      out << v <<"[label=\"\\N (" << (*i).get_priority() << ")\" , color=black ]\n";
    }
    
    vector<int> succ_list = (*i).get_succ_list();
    vector<int>::iterator j = succ_list.begin();
    
    while (j != succ_list.end()) {
      out << v << "->"<< get_vertex(*j).get_label() <<"\n";
      j++;
    }
  }
  out << "}\n";
}

void Graph::output_dot(ostream& out, Valuation val)
{
  vector<Vertex>::iterator i;
  
  out << "digraph G { \n";
  for (i = vertices.begin(); i != vertices.end(); i++) {
    string v = (*i).get_label();
    
    if ((*i).get_player() == odd) {
      out << v <<"[label=\"\\N (" << (*i).get_priority() << ") : " << val.get_value((*i).get_id()).to_string() << "\", color=black, shape=polygon ]\n";
    }
    else {
      out << v <<"[label=\"\\N (" << (*i).get_priority() << ") : " << val.get_value((*i).get_id()).to_string() << "\", color=black]\n";
    }
    
    vector<int> succ_list = (*i).get_succ_list();
    vector<int>::iterator j = succ_list.begin();
    
    while (j != succ_list.end()) {
      out << v << "->"<< get_vertex(*j).get_label() <<"\n";
      j++;
    }
  }
  out << "}\n";
}

set<int> Graph::get_even_winning_set(Valuation val)
{
  set<int> result;
  
  for (vector<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
    if (val.get_value((*i).get_id()).get_best_priority()%2==0) 
      result.insert((*i).get_id());
  }
  
  return result;
}

set<int> Graph::get_even_winning_set(Strategy sigma)
{
  if (sigma.get_type() == s_even) return get_even_winning_set(computeValue_two(sigma, even));
  if (sigma.get_type() == s_odd) return get_even_winning_set(computeValue_two(sigma, odd));

  assert(false);
}


void Graph::output_dot(ostream& out, Strategy s, Valuation val)
{
  vector<Vertex>::iterator i;
  
  out << "digraph G { \n";
  for (i = vertices.begin(); i != vertices.end(); i++) {
    string v = (*i).get_label();
    
    if ((*i).get_player() == odd) {
      out << v <<"[label=\"\\N (" << (*i).get_priority() << ") : " << val.get_value((*i).get_id()).to_string() << "\", color=black, shape=polygon ]\n";
    }
    else {
      out << v <<"[label=\"\\N (" << (*i).get_priority() << ") : " << val.get_value((*i).get_id()).to_string() << "\", color=black]\n";
    }
    
    vector<int> succ_list = (*i).get_succ_list();
    vector<int>::iterator j = succ_list.begin();
    
    while (j != succ_list.end()) {
      if ((*j) == s.get_decision((*i).get_id())) {
        if ((*i).get_player() == odd) 
	  out << v << "->"<< get_vertex(*j).get_label() <<"[color=red]\n";
	else 
	  out << v << "->"<< get_vertex(*j).get_label() <<"[color=blue]\n";
	
      }
      else out << v << "->"<< get_vertex(*j).get_label() <<"\n";
      
      j++;
    }
  }
  out << "}\n";
}

void Graph::output_dot(ostream& out, Strategy s)
{
  vector<Vertex>::iterator i;
  
  out << "digraph G { \n";
  for (i = vertices.begin(); i != vertices.end(); i++) {
    string v = (*i).get_label();
    
    if ((*i).get_player() == odd) {
      out << v <<"[label=\"\\N (" << (*i).get_priority() << ")\", color=black, shape=polygon ]\n";
    }
    else {
      out << v <<"[label=\"\\N (" << (*i).get_priority() << ")\" , color=black ]\n";
    }
    
    vector<int> succ_list = (*i).get_succ_list();
    vector<int>::iterator j = succ_list.begin();
    
    while (j != succ_list.end()) {
      if ((*j) == s.get_decision((*i).get_id())) {
        if ((*i).get_player() == odd) 
	  out << v << "->"<< get_vertex(*j).get_label() <<"[color=red]\n";
	else 
	  out << v << "->"<< get_vertex(*j).get_label() <<"[color=blue]\n";
	
      }
      else out << v << "->"<< get_vertex(*j).get_label() <<"\n";
      
      j++;
    }
  }
  out << "}\n";
}

void Graph::output_dot(ostream& out, set<int> vtx)
{
  vector<Vertex>::iterator i;
  
  out << "digraph G { \n";
  for (i = vertices.begin(); i != vertices.end(); i++) {
    string v = (*i).get_label();
    
    if (vtx.find((*i).get_id()) != vtx.end()) {
      if ((*i).get_player() == odd) {
	out << v <<"[label=\"\\N (" << (*i).get_priority() << ")\", fillcolor=green, style=filled, shape=polygon ]\n";
      }
      else {
	out << v <<"[label=\"\\N (" << (*i).get_priority() << ")\" , style=filled, fillcolor=green ]\n";
      }
    }
    else {
      if ((*i).get_player() == odd) {
	out << v <<"[label=\"\\N (" << (*i).get_priority() << ")\", color=black, shape=polygon ]\n";
      }
      else {
	out << v <<"[label=\"\\N (" << (*i).get_priority() << ")\" , color=black ]\n";
      }
    }
    vector<int> succ_list = (*i).get_succ_list();
    vector<int>::iterator j = succ_list.begin();
    
    while (j != succ_list.end()) {
      out << v << "->"<< get_vertex(*j).get_label() <<"\n";
      j++;
    }
  }
  out << "}\n";
}

