#
# Makefile for some odd library functions
#

XCFLAGS =-DSOFT_387
LIB	=../Libc.a
AR	=/usr/local/bin/ar
AS	=/usr/local/bin/as
LD	=/usr/local/bin/ld
LDFLAGS	=-s -x
CC	=/usr/local/bin/gcc -B/usr/local/bin/
INC	=-nostdinc -I. -I../include
CFLAGS	=-Wall -O -fstrength-reduce -fomit-frame-pointer $(INC) \
	$(XCFLAGS)
CPP	=$(CC) -E $(INC) $(XCFLAGS)

.SUFFIXES: .S .o

.S.o:
	$(CPP) -c -o $*.s $<
	$(AS) -c -o $*.o $*.s
	$(RM) -f $*.s
.c.s:
	$(CC) $(CFLAGS) -S -o $*.s $<
.s.o:
	$(CC) -c -o $*.o $<
.c.o:
	$(CC) $(CFLAGS) -c -o $*.o $<

OBJS  = bcopy.o ldexp.o modf.o tmpnam.o \
	readv.o writev.o values.o perror.o 
#atexit.o exit.o
#OBJS  = bcopy.o ldexp.o modf.o perror.o tmpnam.o readv.o writev.o
#OBJS  = bcopy.o frexp.o ldexp.o modf.o

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
