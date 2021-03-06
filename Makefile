.PHONY: clean

SRC=main.cpp genericthread.cpp genericsignal.cpp syncthread.cpp ferry.cpp routemanager.cpp car.cpp trafficlight.cpp randomizer.cpp printer.cpp
HDR=genericthread.h genericsignal.h syncthread.h ferry.h routemanager.h car.h trafficlight.h randomizer.h printer.h

CC= g++
DEBUG = -g
CFLAGS = -pthread -Wall -Wextra -pedantic -Werror
EX_NAME = traffic

all: prog

prog: $(SRC) $(HDR)
			g++ $(CFLAGS) $(SRC) -o $(EX_NAME)

clean:
			rm -f $(EX_NAME)

