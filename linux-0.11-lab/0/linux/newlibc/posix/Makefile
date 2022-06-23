#
# Makefile for some ansi-library functions
#

LIB	=../Libc.a
#AR	=gar
#AS	=gas
#LD	=gld
AR	=ar
AS	=as
LD	=ld
LDFLAGS	=-s -x
CC	=/usr/local/bin/gcc -B/usr/local/bin/
#CC	=/local/bin/gcc-i386-sysv -v -DPRE_GCC_2
INC	=-nostdinc -I. \
	-I../include
CFLAGS	=-Wall -O -fstrength-reduce -fomit-frame-pointer \
	-finline-functions $(INC)
#CFLAGS	=-Wall -O -fstrength-reduce -finline-functions $(INC)
CPP	=$(CC) -E $(INC)

.SUFFIXES: .C .c

.c.C:
	$(CPP) $(CFLAGS) -S -o $*.C $<

.c.s:
	$(CC) $(CFLAGS) -S -o $*.s $<

.s.o:
	$(CC) -c -o $*.o $<

.c.o:
	$(CC) $(CFLAGS) -c -o $*.o $<

OBJS  = sigmask.o tcattr.o sysconf.o sleep.o tcsetpgrp.o rename.o \
	ttyname.o cfsetget.o tcflow.o

all: library

library: $(OBJS)
	$(AR) uvc $(LIB) $(OBJS)
	sync

clean:
	$(RM) -f core *.o *.a tmp_make
	for i in *.c;do $(RM) -f `basename $$i .c`.s;done

dep:
	sed '/\#\#\# Dependencies/q' < Makefile > tmp_make
	(for i in *.c;do echo -n `echo $$i | sed 's,\.c,\.s,'`" "; \
		$(CPP) -M $$i;done) >> tmp_make
	cp tmp_make Makefile

### Dependencies:
