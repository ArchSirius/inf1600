CC=gcc
CFLAGS= -g -m32 -O2 -Wall
RM=rm -f
TARGET=tp3
OBJECTS=tp3.o dot.o mac.o mul.o
LIBS= -lm 

.PHONY: clean

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

tp3.o: tp3.c 
	$(CC) $(CFLAGS) -c -o $@ $<
	
dot.o: dot.s 
	$(CC) $(CFLAGS) -c -o $@ $<

mac.o: mac.s 
	$(CC) $(CFLAGS) -c -o $@ $<

mul.o: mul.s 
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) *.o $(TARGET)
