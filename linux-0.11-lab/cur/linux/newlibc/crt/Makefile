#
# Makefile for crt0.o of Linux
#
#AR	=/usr/local/bin/gar
AR	=/usr/local/bin/ar
#AS	=/usr/local/bin/gcc-as
AS	=/usr/local/bin/as
#LD	=/usr/local/bin/gld
LD	=/usr/local/bin/ld
RANLIB	=/usr/local/bin/ranlib
LDFLAGS	=-s -x
CC	=/usr/local/bin/gcc -B/usr/local/bin/ -v
#CC	=/local/bin/gcc-i386-sysv -v
INC	=-nostdinc -I. -I../include
CFLAGS	=-Wall -O -fstrength-reduce -fomit-frame-pointer \
	$(INC)# -DNEW_CRT0
CPP	=$(CC) -E $(INC)
RM	=/usr/bin/rm

.c.s:
	$(CC) $(CFLAGS) -S -o $*.s $<
.s.o:
	$(CC) -c -o $*.o $<
.c.o:
	$(CC) $(CFLAGS) -c -o $*.o $<

OBJS  = crt0.o

all: $(OBJS)

clean:
	$(RM) -f core *.o *.a tmp_make

dep:
	sed '/\#\#\# Dependencies/q' < Makefile > tmp_make
	(for i in *.c;do echo -n `echo $$i | sed 's,\.c,\.s,'`" "; \
		$(CPP) -M $$i;done) >> tmp_make
	cp tmp_make Makefile

### Dependencies:
