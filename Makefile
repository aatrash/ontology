OBJS = node.o ontology.o olink.o modinterface.o searchtree.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
EXEC = droid
TEST_INTERFACE = test_interface
ONT_2_DOT = ont2dot

all: $(OBJS) $(EXEC)
droid: droid.cpp $(OBJS)
	$(CC) -o $(EXEC) droid.cpp $(OBJS)
node.o: node.cpp node.h
	$(CC) -c node.cpp
ontology.o: ontology.cpp ontology.h
	$(CC) -c ontology.cpp
olink.o: olink.cpp olink.h
	$(CC) -c olink.cpp
modinterface.o: modinterface.cpp modinterface.h
	$(CC) -c modinterface.cpp
searchtree.o: searchtree.cpp searchtree.h
	$(CC) -c searchtree.cpp
test_interface: test_interface.cpp $(OBJS)
	$(CC) -o $(TEST_INTERFACE) test_interface.cpp $(OBJS)
ont2dot: ont2dot.cpp $(OBJS)
	$(CC) -o $(ONT_2_DOT) ont2dot.cpp $(OBJS)
clean:
	rm *.o $(EXEC) $(TEST_INTERFACE) $(ONT_2_DOT)
