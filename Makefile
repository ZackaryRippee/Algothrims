# makefile

CC = g++

CFLAGS = -g -Wall -Wextra

TARGET = main

default: all

all: main.o
	$(CC) $(CFlags) -o $(TARGET) main.o

main.o:
	$(CC) $(CFLAGS) -c main.cpp

clean:
	$(RM) $(TARGET)$(counting_result.txt) $(quick_result.txt) $(insertion_result.txt) $(numbers.txt) *.o *~
