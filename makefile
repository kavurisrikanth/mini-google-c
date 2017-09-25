CC=gcc
CFLAGS=-I. -Wall -g -lm
TARGET=testing
DEPS=file_struct.h
OBJ = file_ops.o memory.o string_ops.o

%.o: %.c %.h
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	\rm -f testing.exe *.o *.stackdump
