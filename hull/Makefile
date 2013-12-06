objects=hull.o random_edge.o
CC=gcc
LD=gcc
CFLAGS=
LDFLAGS=

all:hull random_edge 

hull:hull.o
	$(LD) -o hull hull.o $(LDFLAGS) 

random_edge:random_edge.o
	$(LD) -o random_edge random_edge.o $(LDFLAGS) 

clean:
	rm -rf $(objects) hull random_edge
