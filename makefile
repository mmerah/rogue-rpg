CC = gcc
CFLAGS = -Wall -I$(CONDA_PREFIX)/include -L$(CONDA_PREFIX)/lib -lmenu -lncurses -I$(IDIR) -g

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