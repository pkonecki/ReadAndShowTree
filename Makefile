CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=-std=c++11
SOURCES=bitFile.cpp  codes.cpp  decode.cpp  encode.cpp  Huffman.cpp  huffTree.cpp  treeFile.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=huff

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
