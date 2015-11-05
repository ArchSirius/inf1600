# Makefile pour le TP4 d'INF1600

DEST=tp4

TP4_S=tp4_s.S

SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o) $(TP4_S:.S=.o)

DEBUG=-g
CC=g++
CXXFLAGS=-Wall $(DEBUG) -O2 -m32
ASFLAGS=$(DEBUG) -m32
LDFLAGS=-lglut -lGLU -lGL -m32


.PHONY: s c

all: $(DEST)

$(DEST): $(OBJ)
	$(CC) $(LDFLAGS) -o $(DEST) $(OBJ)


.PHONY: clean
clean:
	rm -f *.o $(DEST) *.bmp
