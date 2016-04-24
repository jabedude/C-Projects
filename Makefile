CC = clang

all: ansi clean cprog passbyref userlimits wc

ansi:
	$(CC) -o bin/ansi ansicolor.c

clean:
	$(CC) -o bin/clean cleandownloads.c

cprog:
	$(CC) -o bin/cprog cprog.c

passbyref:
	$(CC) -o bin/passbyref passbyref.c

userlimits:
	$(CC) -o bin/userlimits userlimits.c

wc:
	$(CC) -o bin/wc wc.c

