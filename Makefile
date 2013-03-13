
CC=gcc
CFLAGS= -O2 -Wall
PROGNAME=itun

OBJ= icmp_proto.o itun.o tun_dev.o

.c.o:
	$(CC) -c $(CFLAGS) $<

all: $(PROGNAME)

$(PROGNAME): $(OBJ) Makefile
	$(CC) -O2 -Wall -o $(PROGNAME) $(OBJ)
	strip $(PROGNAME)

dep: clean
	$(CC) -MM *.c > Makefile.dep

clean:
	rm -f *.o $(PROGNAME)

include Makefile.dep
