CC = gcc
INC=-nostdinc -I. -I../include
CFLAGS=-O $(INC)
OBJS=free.o malloc.o mcheck.o mstats.o realloc.o unix.o valloc.o
ONESRC=ansidecl.h limits.h stddef.h stdlib.h string.h malloc.h \
 free.c malloc.c realloc.c unix.c valloc.c

all: library

library: gmalloc.o
	$(AR) uvc ../Libc.a gmalloc.o
	sync

#gmalloc.c: $(ONESRC) gmalloc.sed gmalloc.skel
#	sed -f gmalloc.sed gmalloc.skel > gmalloc.c

clean:
	$(RM) -f $(OBJS) gmalloc.o
