#
# Makefile for some odd library functions
#

LIB	=../Libc.a
#AR	=gar
AR	=ar
#AS	=gas
AS	=as
#LD	=gld
LD	=ld
LDFLAGS	=-s -x
CC	=gcc 
INC	=-nostdinc -I/../include
CFLAGS	=-Wall -O -fstrength-reduce -fomit-frame-pointer \
	-finline-functions $(INC) -DUSG -DSTDC_HEADERS
CPP	=$(CC) -E $(INC)

.c.s:
	$(CC) $(CFLAGS) \
	-S -o $*.s $<
.s.o:
	$(CC) -c -o $*.o $<
.c.o:
	$(CC) $(CFLAGS) \
	-c -o $*.o $<

OBJS  = sig_restore.o setjmp.o getcwd.o mktemp.o \
	popen.o getopt.o

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
