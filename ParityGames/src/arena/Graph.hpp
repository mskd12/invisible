/**CPPHeaderFile****************************************************************

  FileName    [Graph.hpp]

  PackageName [parityGame]

  Synopsis    [This file exports the class Graph.]

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
#ifndef __PARITY_GAME_HPP__
#define __PARITY_GAME_HPP__

#include <assert.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include <set>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <limits>
#include <ctime>
#include <stack>

#include "Value.hpp"
#include "Valuation.hpp"
#include "Improvements.hpp"
#include "Strategy.hpp"
#include "Vertex.hpp"

#include "commonFile.hpp"

using namespace std;

namespace parityGame {
  
  class Graph {
  private:
    int n_vertices;
    vector<Vertex> vertices;
    set<int> preference_set; 
    set<int> priority_set; 
    
    vector<int> priority_sorted_vertex_list;  // priority sorted list
    vector<int> sorted_vertex_list;  // preference sorted list
    
    vector<int> even_vertices;
    vector<int> odd_vertices;

    vector<int> randomized_vertices_list;
  public:  
    /* Constructor */
    Graph() {n_vertices = 0;}
    
    /* Setter functions */
    void add_vertex(Vertex v);
    void add_vertex(string label, int id, int priority, PLAYER player); 
    void set_successor(string vertex, string succ);
    void fill_predecessors();
    void make_priorities_unique();
    
    /* Getter functions */    
    /* Getter functions */
    Vertex& get_vertex(const string label);
    Vertex& get_vertex(const int id);
    int get_num_of_vertices();
    bool is_player_trivial(PLAYER pl);
    
    /* Image computation */
    set<int> preImage(set<int> target, PLAYER pl); 
    set<int> computeAttractor(set<int> target, PLAYER pl);
    set<int> preImageClosed(set<int> target); // One player version of preImage
    set<int> computeClosedVertices(set<int> target); // One player version of computeAttractor
    set<int> computeAttractorVertex(set<int> vid);
        
    /* Parity Games Algorithms */
    pair<Strategy, int> strategyImprovement(PLAYER pl);
    pair<Strategy, int> symStrategyImprovement();
    pair<set<int>, set<int> >PGSolve();


    /* Pretty print */
    void show();    
    void show(Strategy s);    
    void show(Strategy s, Valuation v);    
    void show(set<int> v);    
    void show(Valuation val);
    
    /* Tester functions */
    Graph compute_dual_game();
    set<int> get_even_winning_set(Strategy sigma);
    
  private:
    /* Strategy computation */
    Strategy getStrategyFromWinningSet(set<int> even_win_set, STRAT_TYPE type);
    Strategy getArbitraryStrategy(STRAT_TYPE type);
    Strategy getRandomStrategy(STRAT_TYPE type);  
    Graph applyStrategy(Strategy s);

    /* Value computation */
    Valuation computeValue_zero(); 
    Valuation computeValue_one(Strategy s); 
    Valuation computeValueDirect_one(PLAYER pl);
    Valuation computeValue_two(Strategy s, PLAYER pl); 
    
    /* Strategy Improvement Algorithms Subroutines  */
    Strategy getImprovedStrategy(Strategy s, Valuation v, PLAYER pl);
    Strategy getImprovedStrategy(Strategy s, Valuation v, PLAYER pl, Strategy helper);
    //    Strategy getImprovedStrategyRF(Strategy sigma, Valuation v, PLAYER pl);


    /* Helper functions */
    Graph computeSubGame(set<int> vert_set);
    Graph computeSubGame1(set<int> vert_set);
    set<int> get_vertices_of_parity(int pr);
    set<int> get_even_winning_set(Valuation val);
    bool can_self_reach_one(int vid, PLAYER pl);
    bool can_self_reach_zero(int vid);
    bool DFS(int v);
    bool DFSUtil(int v, bool visited[], int curr_priority, int vid);
    void topologicalSortUtil(int v, bool visited[], stack<int> &Stack);
    void longestPath(int vid, Valuation &val);
    int minDistance(map<int, int> &dist, map<int, bool> &sptSet);
    void dijkstra(int src, Valuation &val);
    Valuation edgeRemove(int vid, PLAYER pl, Valuation &v);
    PLAYER opponent(PLAYER pl);
        
    void output_dot(ostream& out, set<int> v);
    void output_dot(ostream& out, Valuation val);
    void output_dot(ostream& out, Strategy s);
    void output_dot(ostream& out, Strategy s, Valuation v);
    void output_dot(ostream& out);
    
    Improvements get_improvements(Strategy sigma, Valuation valn, PLAYER pl);
    Improvements get_opt_improvement(Strategy sigma, Valuation valn, PLAYER pl);
    pair<Strategy, int> strategyImprovement_one(PLAYER pl);
    pair<Strategy, int> strategyImprovement_two(PLAYER pl);
    pair<Strategy, int>  symStrategyImprovement_two();
    //    pair<Strategy, int> randomFacet(PLAYER pl);
      
    set< set<int> > generateSCCs();
    int get_sample(const std::set<int>& s);
    bool toss_a_coin();
    void show_random();
  };
  



  
}

#endif /* __PARITY_GAME_HPP__ */
