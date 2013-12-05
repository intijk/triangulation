objects=triGraph.o
CC=gcc
LD=gcc
CFLAGS=`pkg-config --cflags cairo`
LDFLAGS=-lm `pkg-config --libs cairo` 

triGraph:$(objects)
	$(LD) -o triGraph $(objects) $(LDFLAGS) 

clean:
	rm -rf triGraph $(objects)
