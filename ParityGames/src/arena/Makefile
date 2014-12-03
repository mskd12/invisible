SRCDIR = ../
objects = Graph.o Value.o Valuation.o Improvements.o Strategy.o Vertex.o Solver.o
sources= Graph Value Valuation Improvements Strategy Vertex Solver
cppfiles= Graph.cpp Value.cpp Valuation.cpp Improvements.cpp Strategy.cpp Vertex.cpp Solver.cpp
headers= Graph.hpp Value.hpp Valuation.hpp Improvements.hpp commonFile.hpp Strategy.hpp Vertex.hpp Solver.hpp

all: parity_game

parity_game: $(cppfiles) $(headers) $(SRCDIR)/main.hpp 
	for i in $(sources) ; do \
	(g++ -std=c++11 -Wall -c $$i.cpp -o $$i.o); \
	done

	ar rcs libPG.a $(objects)

clean:
	rm -rf $(objects)
	rm -rf libPG.a
