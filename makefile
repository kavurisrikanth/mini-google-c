CC=gcc
CFLAGS=-I. -Wall -g -lm
TARGET=mini-google
DEPS=file_struct.h
OBJ = file_ops.o memory.o string_ops.o testing.o

%.o: %.c %.h
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	\rm -f *.exe *.o *.stackdump
