%{
#include "parserInt.h" // includes definition of parityGames 
#include <stdio.h>
  
  parityGame::Graph Gg;
  vector<int>  tmp_succ_list;
  extern "C"
  {
    void yyerror(char *s);
    int yyparse(void);
    int yylex(void);  
  }
  
  %}

%union {
  int num;
  char* id;
};

%start graph

%token <num>INT
%token <id>IDEN 
%token PARITY SEMI COMMA 

%%                   
 /* beginning of rules section */

graph : head body {
  Gg.fill_predecessors(); 
  Gg.make_priorities_unique();
 }
      ;

head : PARITY INT SEMI {}
     ;

body : vertices_list {}
     ;

vertices_list : vertex  {} 
              | vertices_list vertex {}
              ;

vertex : INT INT INT succ_list IDEN SEMI 
{
  int cid = $1;
  string tmp = "\"" + (string) $5 + "\"";
    if ($3==0)  Gg.add_vertex(tmp, cid, $2, parityGame::even); 
  else Gg.add_vertex(tmp, cid, $2, parityGame::odd); 
  
  for(vector<int>::iterator j = tmp_succ_list.begin(); j != tmp_succ_list.end(); j++) {
    Gg.get_vertex(cid).add_succ(*j);
  }
  tmp_succ_list.clear();
}

| INT INT INT succ_list SEMI 
{
  int cid = $1;
  
  if ($3==0)  Gg.add_vertex(to_string($1), cid, $2, parityGame::even); 
  else Gg.add_vertex(to_string($1), cid, $2, parityGame::odd); 

  for(vector<int>::iterator j = tmp_succ_list.begin(); j != tmp_succ_list.end(); j++) {
    Gg.get_vertex(cid).add_succ(*j);
  }
  tmp_succ_list.clear();
}
;

succ_list: INT {tmp_succ_list.push_back($1);}
| succ_list COMMA INT {tmp_succ_list.push_back($3);}
;
 
%%

parityGame::Graph parse_graph(const char * filename) 
{
  extern FILE *yyin;
  yyin = fopen(filename, "r");
  
  if (!yyin) throw parityGame::FileNotFound;
  
  yyparse(); 
  
  fclose(yyin);
  return Gg;
}

extern "C"
{
  
  void yyerror(char *s)
  {
    fprintf(stderr, " --- %s -- \n", s);
  }
  
  int  yywrap()
  {
    return(1);
  }
  
}
