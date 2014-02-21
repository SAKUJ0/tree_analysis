EXECUTABLE=tree_analysis
SOURCES=analysis.cpp Tree.cpp Branch.cpp
OBJECTS=$(SOURCES:.cpp=.o)
CC=g++
CFLAGS=$(shell root-config --cflags) -Wall -c
LDFLAGS=$(shell root-config --libs)

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS)
