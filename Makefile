SHELL:=/bin/bash

SRCDIR = ./src
BINDIR = ./bin
OBJDIR = ./obj
TARGET = $(BINDIR)/dijkstra

pre-compil: $(BINDIR) $(OBJDIR) $(TARGET)
	

$(TARGET): $(OBJDIR)/main.o $(OBJDIR)/Graph.o
	g++ $(OBJDIR)/main.o $(OBJDIR)/Graph.o -o $(TARGET)

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp
	g++ -c $(SRCDIR)/main.cpp -o $(OBJDIR)/main.o

$(OBJDIR)/Graph.o: $(SRCDIR)/Graph.cpp $(SRCDIR)/Graph.hpp
	g++ -c $(SRCDIR)/Graph.cpp -o $(OBJDIR)/Graph.o

$(BINDIR):
	mkdir "$(BINDIR)"

$(OBJDIR):
	mkdir "$(OBJDIR)"

clean:
	rm -rf "$(BINDIR)" "$(OBJDIR)"
