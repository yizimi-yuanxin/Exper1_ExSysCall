LIB=../Libsoft.a
AR      =/usr2/linux/cross/bin/gar
AS      =/usr2/linux/cross/lib/gcc-as
LD      =/usr2/linux/cross/bin/gld
RANLIB  =/usr2/linux/cross/bin/ranlib
LDFLAGS =-s -x
CC      =/usr2/linux/cross/bin/gcc -B/usr2/linux/cross/lib/gcc-
INC     =-nostdinc -I. -I/usr2/linux/src/lib.new/new \
	-I/usr2/linux/usr/include
CFLAGS = -Wall -O -fstrength-reduce -fomit-frame-pointer $(INC)
CPP=$(CC) -E $(INC)
LIBS= -lm

.s.o :
	$(CC) $(CFLAGS) -c $*.s

.c.o :
	$(CC) $(CFLAGS) -c $*.c

OBJS = asin.o atan.o const.o exp.o fabs.o floor.o frexp.o hypot.o \
	j0.o j1.o jn.o log.o pow.o sin.o sinh.o sqrt.o tan.o tanh.o \
	erf.o lgamma.o

library: $(OBJS)
	$(AR) uvc $(LIB) $(OBJS)
	sync

test: $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)

clean:
	$(RM) -f core *.o *.a tmp_make
	for i in *.c;do $(RM) -f `basename $$i .c`.s;done

dep:
	sed '/\#\#\# Dependencies/q' < Makefile > tmp_make
	(for i in *.c;do echo -n `echo $$i | sed 's,\.c,\.s,'`" "; \
	$(CPP) -M $$i;done) >> tmp_make
	cp tmp_make Makefile

### Dependencies:
