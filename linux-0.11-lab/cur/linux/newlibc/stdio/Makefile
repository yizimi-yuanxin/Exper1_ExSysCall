#
# Makefile for BSD compatible stdio library functions
#

LIB	=../Libc.a
#AR	=gar
#AS	=gas
#LD	=gld
AR	=ar
AS	=as
LD	=ld
LDFLAGS	=-s -x
CC	=gcc 
INC	=-nostdinc -I/../include
CFLAGS	=-Wall -O -fstrength-reduce -fomit-frame-pointer \
	$(INC)# -DUSG -DSTDC_HEADERS
CPP	=$(CC) -E $(INC)

.c.s:
	$(CC) $(CFLAGS) \
	-S -o $*.s $<
.s.o:
	$(CC) -c -o $*.o $<
.c.o:
	$(CC) $(CFLAGS) \
	-c -o $*.o $<

OBJS  = clrerr.o doprnt.o doscan.o fdopen.o fgetc.o fgets.o filbuf.o \
	findiop.o flsbuf.o fopen.o fprintf.o fputc.o fputs.o fread.o \
	freopen.o fseek.o ftell.o fwrite.o getchar.o gets.o getw.o \
	printf.o putchar.o puts.o putw.o rew.o scanf.o setbuf.o \
	setbuffe.o sprintf.o ungetc.o vfprintf.o vprintf.o \
	vsprintf.o setvbuf.o

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
