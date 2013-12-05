objects=triGraph.o
CC=gcc
LD=gcc
CFLAGS=
LDFLAGS=-lm

triGraph:$(objects)
	$(LD) -o triGraph $(LDFLAGS) $(objects)

clean:
	rm -rf triGraph $(objects)
