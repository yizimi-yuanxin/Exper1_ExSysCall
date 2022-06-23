# This is file Makefile
#
# Copyright (C) 1991 DJ Delorie, 24 Kirsten Ave, Rochester NH 03867-2954
#
# This file is distributed under the terms listed in the document
# "copying.dj", available from DJ Delorie at the address above.
# A copy of "copying.dj" should accompany this file; if not, a copy
# should be available from where this file was obtained.  This file
# may not be distributed without a verbatim copy of "copying.dj".
#
# This file is distributed WITHOUT ANY WARRANTY; without even the implied
# warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
LIB=../Libm.a
CC= gcc
CFLAGS = -Wall -O -fstrength-reduce -fomit-frame-pointer $(INC)
CPP=$(CC) -E $(INC)

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
