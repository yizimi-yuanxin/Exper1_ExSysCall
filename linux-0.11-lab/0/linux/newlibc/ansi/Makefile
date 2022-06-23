#
# Makefile for some ansi-library functions
#

LIB	=../Libc.a
AR	=gar
AS	=gas
LD	=gld
LDFLAGS	=-s -x
CC	=/usr/local/bin/gcc -B/usr/local/bin/
#CC	=/local/bin/gcc-i386-sysv
INC	=-nostdinc -I../include
CFLAGS	=-Wall -O -fstrength-reduce -fomit-frame-pointer \
	-finline-functions $(INC)
CPP	=$(CC) -E $(INC)

.c.s:
	$(CC) $(CFLAGS) -S -v -o $*.s $<
.s.o:
	$(CC) -c -o $*.o $<
.c.o:
	$(CC) $(CFLAGS) -c -o $*.o $<

OBJS  = abs.o errno.o ctype.o string.o abort.o bsearch.o \
	strtol.o atoi.o rand.o div.o isatty.o strerror.o \
	getenv.o atof.o ctime.o qsort.o system.o strftime.o \
	tzset.o ftime.o
#	gettimeofday.o # why is it not here? unfinished?

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
