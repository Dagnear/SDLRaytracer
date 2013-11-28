# Raytracer makefile
CC = gcc
LDFLAGS = -lSDL
CFLAGS = -Wall -g

SRC = main.c input.c gfx.c pixel.c tracer.c mapping.c
OBJ = $(SRC:.c=.o)
TARGET = raytracer.elf


all: $(TARGET)

$(TARGET) : $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o : %.c
	$(CC) $< $(CFLAGS) -c -o $@

.PHONY : clean cleanobj
clean : cleanobj
	rm -f $(TARGET)
cleanobj:
	rm -f *.o


