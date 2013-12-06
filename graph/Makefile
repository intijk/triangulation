objects=triGraph.o 
CC=gcc
LD=gcc
CFLAGS=`pkg-config --cflags cairo`
LDFLAGS=-lm `pkg-config --libs cairo` 

all: triGraph hullGraph
hullGraph:hullGraph.o
	$(LD) -o hullGraph hullGraph.o $(LDFLAGS) 
triGraph:$(objects)
	$(LD) -o triGraph triGraph.o $(LDFLAGS) 
clean:
	rm -rf triGraph hullGraph $(objects)
