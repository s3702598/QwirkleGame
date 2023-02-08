.default: all

all: qwirkle

clean:
	rm -rf qwirkle *.o *.dSYM

qwirkle: Tile.o Node.o LinkedList.o Main.o Messages.o Driver.o  Player.o Board.o Synchronize.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^
