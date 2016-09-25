CC=g++
CFLAGS=-c -Wall -MMD

all: pp9k

pp9k: gamepiece.o pawn.o rook.o knight.o bishop.o queen.o king.o board.o textdisplay.o window.o graphicdisplay.o controller.o player.o humanplayer.o computerone.o
	$(CC) -g main.cc gamepiece.o pawn.o rook.o knight.o bishop.o queen.o king.o board.o textdisplay.o window.o graphicdisplay.o controller.o player.o humanplayer.o computerone.o -o pp9k -lX11

board.o: board.cc
	$(CC) $(CFLAGS) board.cc

gamepiece.o: gamepiece.cc
	$(CC) $(CFLAGS) gamepiece.cc

pawn.o: pawn.cc
	$(CC) $(CFLAGS) pawn.cc

rook.o: rook.cc
	$(CC) $(CFLAGS) rook.cc

knight.o: knight.cc
	$(CC) $(CFLAGS) knight.cc

bishop.o: bishop.cc
	$(CC) $(CFLAGS) bishop.cc

queen.o: queen.cc
	$(CC) $(CFLAGS) queen.cc

king.o: king.cc
	$(CC) $(CFLAGS) king.cc

player.o: player.cc
	$(CC) $(CFLAGS) player.cc

humanplayer.o: humanplayer.cc
	$(CC) $(CFLAGS) humanplayer.cc

computerone.o: computerone.cc
	$(CC) $(CFLAGS) computerone.cc

controller.o: controller.cc
	$(CC) $(CFLAGS) controller.cc

textdisplay.o: textdisplay.cc
	$(CC) $(CFLAGS) textdisplay.cc

window.o: window.cc
	$(CC) $(CFLAGS) window.cc

graphicdisplay.o: graphicdisplay.cc
	$(CC) $(CFLAGS) graphicdisplay.cc

clean:
	rm *.d *.o pp9k
