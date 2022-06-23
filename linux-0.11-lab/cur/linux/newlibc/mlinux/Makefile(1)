# This is Makefile of the math lib for Linux
#
LIB=../Libm.a
CC= /usr2/linux/cross/bin/gcc -B/usr2/linux/cross/lib/gcc-
CFLAGS = -Wall -O -fstrength-reduce -fomit-frame-pointer $(INC)
INC=-nostdinc -I. -I/usr2/linux/lib.new/2.0 -I/usr2/linux/usr/include
CPP=$(CC) -E $(INC)
AR=/usr2/linux/cross/bin/ar
RM=/bin/rm

.s.o :
	$(CC) $(CFLAGS) -c $*.s

.c.o :
	$(CC) $(CFLAGS) -c $*.c

OBJS = acos.o acosh.o asin.o asinh.o atan.o atan2.o atanh.o ceil.o \
	cos.o cosh.o exp.o fabs.o floor.o fmod.o frexp.o hypot.o  \
	log.o log10.o sin.o sinh.o sqrt.o tan.o tanh.o \
	erf.o j0.o j1.o jn.o lgamma.o

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
