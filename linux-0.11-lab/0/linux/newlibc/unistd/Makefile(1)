#
# Makefile for some ansi-library functions
#

OBJS = _exit.o access.o acct.o alarm.o brk.o chdir.o chmod.o chown.o \
chroot.o close.o creat.o dup.o dup2.o exec.o execp.o execve.o fcntl.o \
fork.o fstat.o getegid.o geteuid.o getgid.o getpid.o getppid.o getuid.o \
getpgrp.o ioctl.o kill.o link.o lseek.o mkdir.o mknod.o mount.o nice.o \
open.o pause.o pipe.o read.o rmdir.o setgid.o setpgrp.o setsid.o setuid.o \
signal.o stat.o stime.o sync.o time.o times.o ulimit.o umask.o umount.o \
uname.o unlink.o ustat.o utime.o wait.o write.o setreuid.o setregid.o \
sigsusp.o sigpend.o sethostnam.o gethostnam.o \
getgroups.o setgroups.o \
symlink.o lstat.o readlink.o uselib.o
#select.o setrlimit.o getrlimit.o getrusage.o gettime.o settime.o 

LIB	=../Libc.a
AR	=/usr/local/bin/ar
AS	=/usr/local/bin/as
LD	=/usr/local/bin/ld
LDFLAGS	=-s -x
CC	=/usr/local/bin/gcc -B/usr/local/bin/
INC	=-nostdinc  \
	-I../include
CFLAGS	=-Wall -O -fstrength-reduce -fomit-frame-pointer \
	-finline-functions $(INC)
CPP	=$(CC) -E $(INC)

.c.s:
	$(CC) $(CFLAGS) -S -o $*.s $<
.s.o:
	$(CC) -c -o $*.o $<

.c.o:
	$(CC) $(CFLAGS) -c -o $*.o $<

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
