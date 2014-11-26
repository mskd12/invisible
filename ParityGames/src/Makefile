###############################################################################
#
#  TOP LEVEL MAKEFILE
#
###############################################################################
PARSERDIR = parser
PARITYGAMEDIR = arena

SUBDIRS = $(PARSERDIR) 	$(PARITYGAMEDIR)	

# Default target
all: 
	@echo "####################################################################"
	@echo "### Building all targets in root                                 ###"
	@echo "####################################################################"
	@echo
	for i in $(SUBDIRS) ; do \
	(cd $$i; make); \
	done

	@echo "#####################################################################"
	@echo "### Making SymSIM                                                ####"
	@echo "#####################################################################"
	g++ -std=c++11 -w $(PARITYGAMEDIR)/*.o   $(PARSERDIR)/lex.yy.o  $(PARSERDIR)/parser.cc   main.cpp -o symSIM

#Rules to build individual targets

parser:
	@cd $(PARSERDIR); make

arena:
	@cd $(PARITYGAMEDIR); make

clean:
	@echo
	for i in $(SUBDIRS) ; do \
	(cd $$i; make clean); \
	done

