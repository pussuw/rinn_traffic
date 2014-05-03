.PHONY: clean

SRC=main.cpp genericthread.cpp 
HDR=genericthread.h
CC= g++
DEBUG = -g
CFLAGS = -pthread -Wall -Wextra -pedantic -Werror
EX_NAME = traffic

all: prog

prog: $(SRC) $(HDR)
			g++ $(CFLAGS) $(SRC) -o $(EX_NAME)

clean:
			rm -f $(EX_NAME)

