/*
 *  linux/kernel/sys.c
 *
 *  (C) 1991  Linus Torvalds
 */

#include <errno.h>

#include <linux/sched.h>
#include <linux/tty.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/segment.h>
#include <sys/times.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <signal.h>
#include <unistd.h>
#include <fcntl.h>


int sys_ftime()
{
	return -ENOSYS;
}

int sys_break()
{
	return -ENOSYS;
}

int sys_ptrace()
{
	return -ENOSYS;
}

int sys_stty()
{
	return -ENOSYS;
}

int sys_gtty()
{
	return -ENOSYS;
}

int sys_rename()
{
	return -ENOSYS;
}

int sys_prof()
{
	return -ENOSYS;
}

int sys_setregid(int rgid, int egid)
{
	if (rgid>0) {
		if ((current->gid == rgid) || 
		    suser())
			current->gid = rgid;
		else
			return(-EPERM);
	}
	if (egid>0) {
		if ((current->gid == egid) ||
		    (current->egid == egid) ||
		    suser()) {
			current->egid = egid;
			current->sgid = egid;
		} else
			return(-EPERM);
	}
	return 0;
}

int sys_setgid(int gid)
{
/*	return(sys_setregid(gid, gid)); */
	if (suser())
		current->gid = current->egid = current->sgid = gid;
	else if ((gid == current->gid) || (gid == current->sgid))
		current->egid = gid;
	else
		return -EPERM;
	return 0;
}

int sys_acct()
{
	return -ENOSYS;
}

int sys_phys()
{
	return -ENOSYS;
}

int sys_lock()
{
	return -ENOSYS;
}

int sys_mpx()
{
	return -ENOSYS;
}

int sys_ulimit()
{
	return -ENOSYS;
}

int sys_time(long * tloc)
{
	int i;

	i = CURRENT_TIME;
	if (tloc) {
		verify_area(tloc,4);
		put_fs_long(i,(unsigned long *)tloc);
	}
	return i;
}

/*
 * Unprivileged users may change the real user id to the effective uid
 * or vice versa.
 */
int sys_setreuid(int ruid, int euid)
{
	int old_ruid = current->uid;
	
	if (ruid>0) {
		if ((current->euid==ruid) ||
                    (old_ruid == ruid) ||
		    suser())
			current->uid = ruid;
		else
			return(-EPERM);
	}
	if (euid>0) {
		if ((old_ruid == euid) ||
                    (current->euid == euid) ||
		    suser()) {
			current->euid = euid;
			current->suid = euid;
		} else {
			current->uid = old_ruid;
			return(-EPERM);
		}
	}
	return 0;
}

int sys_setuid(int uid)
{
/*	return(sys_setreuid(uid, uid)); */
	if (suser())
		current->uid = current->euid = current->suid = uid;
	else if ((uid == current->uid) || (uid == current->suid))
		current->euid = uid;
	else
		return -EPERM;
	return(0);
}

int sys_stime(long * tptr)
{
	if (!suser())
		return -EPERM;
	startup_time = get_fs_long((unsigned long *)tptr) - jiffies/HZ;
	return 0;
}

int sys_times(struct tms * tbuf)
{
	if (tbuf) {
		verify_area(tbuf,sizeof *tbuf);
		put_fs_long(current->utime,(unsigned long *)&tbuf->tms_utime);
		put_fs_long(current->stime,(unsigned long *)&tbuf->tms_stime);
		put_fs_long(current->cutime,(unsigned long *)&tbuf->tms_cutime);
		put_fs_long(current->cstime,(unsigned long *)&tbuf->tms_cstime);
	}
	return jiffies;
}

int sys_brk(unsigned long end_data_seg)
{
	if (end_data_seg >= current->end_code &&
	    end_data_seg < current->start_stack - 16384)
		current->brk = end_data_seg;
	return current->brk;
}

/*
 * This needs some heave checking ...
 * I just haven't get the stomach for it. I also don't fully
 * understand sessions/pgrp etc. Let somebody who does explain it.
 */
int sys_setpgid(int pid, int pgid)
{
	int i;

	if (!pid)
		pid = current->pid;
	if (!pgid)
		pgid = current->pid;
	for (i=0 ; i<NR_TASKS ; i++)
		if (task[i] && task[i]->pid==pid) {
			if (task[i]->leader)
				return -EPERM;
			if (task[i]->session != current->session)
				return -EPERM;
			task[i]->pgrp = pgid;
			return 0;
		}
	return -ESRCH;
}

int sys_getpgrp(void)
{
	return current->pgrp;
}

int sys_setsid(void)
{
	if (current->leader && !suser())
		return -EPERM;
	current->leader = 1;
	current->session = current->pgrp = current->pid;
	current->tty = -1;
	return current->pgrp;
}

int sys_getgroups()
{
	return -ENOSYS;
}

int sys_setgroups()
{
	return -ENOSYS;
}

int sys_uname(struct utsname * name)
{
	static struct utsname thisname = {
		"linux .0","nodename","release ","version ","machine "
	};
	int i;

	if (!name) return -ERROR;
	verify_area(name,sizeof *name);
	for(i=0;i<sizeof *name;i++)
		put_fs_byte(((char *) &thisname)[i],i+(char *) name);
	return 0;
}

int sys_sethostname()
{
	return -ENOSYS;
}

int sys_getrlimit()
{
	return -ENOSYS;
}

int sys_setrlimit()
{
	return -ENOSYS;
}

int sys_getrusage()
{
	return -ENOSYS;
}

int sys_gettimeofday()
{
	return -ENOSYS;
}

int sys_settimeofday()
{
	return -ENOSYS;
}


int sys_umask(int mask)
{
	int old = current->umask;

	current->umask = mask & 0777;
	return (old);
}

int sys_execve2(const char *path, char * argv[], char * envp[]) {
	printk("execve2");
	return -1;
}

struct linux_dirent {
	long           	d_ino;
	off_t          	d_off;
	unsigned short 	d_reclen;
	char 			d_name[14];
};

int sys_getdents(unsigned int fd, struct linux_dirent *dirp, unsigned int count) {
	printk("getdents");
	return -1;
}

int sys_pipe2() {
	printk("pipe2");
	return -1;
}

void sig_alrm(int signo) {					// by yizimi
	printk("please wake up!");
}

int sys_sleep(unsigned int seconds) { 		// by yizimi
	sys_signal(SIGALRM, SIG_IGN, NULL);
    sys_alarm(seconds);
    sys_pause();
	return 0;
}

extern int errno;
#define BUF_MAX 4096

long sys_getcwd(char * buf, size_t size) { 	// by yizimi
	// printk("getcwd");
	char buf_name[BUF_MAX];
	char *nowbuf; 
	struct dir_entry * de;
	struct dir_entry * det;
	struct buffer_head * bh;
	nowbuf = (char *)malloc(BUF_MAX * sizeof(char));
	struct m_inode *now_inode = current->pwd;
	int idev, inid, block;

	// printk("[buf-pos] %d\n", buf);

	int prev_inode_num = now_inode->i_num;
	if (now_inode == current->root)
		strcpy(nowbuf, "/");

	while (now_inode != current->root) {
		// printk("[debug] try find_entry2...\n");
		// bh = find_entry2(&now_inode, "..", 2, &det, 0);
		bh = find_father_dir(&now_inode, &det);
		// printk("[dir_entry now] %d %s\n", det->inode, det);
		idev = now_inode->i_dev;
		inid = det->inode;
		// printk("[debug] try iget... \n");
		now_inode = iget(idev, inid);
		// printk("[debug] try find_entry3...\n");
		// bh = find_same_inode(&now_inode, "lala", 4, &de, prev_inode_num);
		bh = find_same_inode(&now_inode, &de, prev_inode_num);
		prev_inode_num = det->inode;
		strcpy(buf_name, "/");
		strcat(buf_name, de->name);
		strcat(buf_name, nowbuf);
		strcpy(nowbuf, buf_name);
		// printk("[nowbuf] %s\n", nowbuf);
	}
	// printk("[debug] try strcpy...\n");
	int chars = size;
	// printk("[buf-pos] %d\n", buf);
	char *p1 = nowbuf, *p2 = buf;
	++size;
	while (size-- > 0)
		put_fs_byte(*(p1++), p2++);
	// printk("[buf-pos] %d\n", buf);
	return (long)buf;
}  