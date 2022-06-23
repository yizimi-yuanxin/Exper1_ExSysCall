#
# Makefile for the Linux library
#

# define this for now. it used in modf.c. it will be dropped when 0.13
# kernel is released.
XCFLAGS = -DSOFT_387

LIBS	= Libc.a Libm.a Libtermcap.a
#AR	=/usr2/linux/cross/lib/gar
AR	=/usr/local/bin/ar
#AS	=/usr2/linux/cross/lib/gcc-as
AS	=/usr/local/bin/as
#LD	=/usr2/linux/cross/bin/gld
LD	=/usr/local/bin/ld
#RANLIB	=/usr2/linux/cross/bin/ranlib
RANLIB	=/usr/local/bin/ranlib
LDFLAGS	=-s -x
CC	=/usr/local/bin/gcc -B/usr/local/bin/
#CC	=/local/bin/gcc-i386-sysv -DPRE_GCC_2
INC	=-nostdinc -I. -I../soft -I../include
#INC	=-nostdinc -I. -I../soft \
#	-I/usr2/linux/src/lib.new/2.0 \
#	-I/usr2/linux/usr/include
CFLAGS	=-Wall -O -fstrength-reduce -fomit-frame-pointer \
	-fcombine-regs -finline-functions -mstring-insns $(INC)
CPP	=$(CC) -E $(INC)
RM	=/usr/bin/rm

#DIRS	=ansi crt dirent grp malloc math misc other posix pwd \
#	stdio termcap unistd
#DIRS	=ansi crt dirent grp malloc mlinux misc other posix pwd \
#	termcap unistd
DIRS	=ansi crt dirent malloc other posix unistd

MFLAGS	=CC="$(CC)" AR="$(AR)" LD="$(LD)" CPP="$(CPP)" AS="$(AS)" \
	RANLIB="$(RANLIB)" INC="$(INC)" RM="$(RM)" \
	XCFLAGS="$(XCFLAGS)"

# To record the "newlibc" directory, by yjwen. 
# Maybe a bug exists in the "make" of Linux 0.11.
SRCDIR =/usr/root/newlibc

all:
	for i in $(DIRS); \
	do \
		(cd $(SRCDIR)/$$i; make $(MFLAGS)); \
	done
	$(RANLIB) $(LIBS)

dep:
	for i in $(DIRS); \
	do \
		(cd $(SRCDIR)/$$i; make dep $(MFLAGS)); \
	done

clean:
	rm -f $(LIBS)
	for i in $(DIRS); \
	do \
		(cd $(SRCDIR)/$$i; make clean $(MFLAGS)); \
	done
