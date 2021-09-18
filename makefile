CC = gcc
CFLAGS = -Wall -lmenu -lncurses -I$(IDIR) -g

IDIR = ./include/
SRCDIR = ./src/

SOURCES = $(SRCDIR)*.c\
		  $(SRCDIR)windows/*.c\
		  $(SRCDIR)entities/*.c\
		  $(SRCDIR)entities/items/*.c\
		  $(SRCDIR)utils/*.c

all: rogue

rogue: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o $@

run:
	./rogue

clean:
	rm rogue