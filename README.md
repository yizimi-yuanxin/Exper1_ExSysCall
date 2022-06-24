1.  # 操作系统 Linux 系统调用扩充实验报告

    <p align="right">小组：202002001021 李天豪 | 202002001037 谭承浩</p>

    ## 一、实验目的及分工

    扩充 linux0.11 内核 0 版本的系统调用库，并使用测试样例测试所写的系统调用。

    实现的系统调用为：

    ```c++
    execve2, getdents, sleep, getcwd
    ```

    | 小组分工 | 实现函数          | GitHub用户名     | commit log 署名 |
    | -------- | ----------------- | ---------------- | --------------- |
    | 李天豪   | sleep, getcwd     | yizimi-yuanxin   | yizimi          |
    | 谭承浩   | execve2, getdents | TCH-202002001037 | TCH             |

    ## 二、实验环境

    Windows系统，UbuntuKylin14.10虚拟机，bochs虚拟机，linux0.11内核，VSCode，GitHub

    GitHub地址：https://github.com/yizimi-yuanxin/Exper1_ExSysCall

    最终版本的分支：dev

    ## 三、设计思路

    ### 1. execve2

    ### 2. getdents

    ### 3. sleep

    考虑调用alarm来实现。在alarm超时时间时，接收到一个SIGALRM的信号，来判断是否结束，且使用SIG_IGN忽略发出信号时所调用的函数。

    ### 4. getcwd

    对于getcwd的功能，我们可以从当前目录开始，每次记录他本身的目录项 inode 节点号，然后在该目录中找到 ".." 来到达父目录，并在父目录中找到刚刚目录的相同 inode 节点号的目录项，并记录目录名称。依此递归到根节点。

    

    ## 四、实现方法及关键源码

    ### 1. execve2

    ### 2. getdents

    ### 3. sleep

    我们先调用 signal 函数，发送出 SIGALRM 信号，并传递 SIG_IGN 参数忽略信号处理函数。然后调用 sys_alarm，然后通过调用 sys_pause 实现进程调度，并在 alarm 超时时间时结束即可。

    ```C
    int sys_sleep(unsigned int seconds) { 		// by yizimi
    	sys_signal(SIGALRM, SIG_IGN, NULL);		
        sys_alarm(seconds);
        sys_pause();
    	return 0;
    }
    ```

    ### 4. getcwd

    current->pwd 记录了指向当前目录 inode 节点的指针，如果我们 current->pwd == current->root，即当前目录为根目录，直接返回 "/"。如果不是根目录，则一直跳到根目录。首先通过 find_father_dir(自定义) 来找到父目录的 inode 的节点号，记录下设备号(i_dev)，调用 iget 函数来访问父目录。再在父目录中调用 find_same_inode 来查找刚刚与目录 inode 节点号相同的目录项，然后将目录项中的 name 整合到目录中。

    我们观察 find_entry 函数，find_entry 函数主要实现的是在该inode节点所指向的目录项中查找名字为 name 的目录项并可以返回目录项。我们可以以 find_entry 为原型，把 match 函数更改为相应的判断条件，实现 find_father_dir, find_same_inode，来满足上述操作。

    最后，我们需要把目录项通过 put_fs_byte 将内核态中缓存内容拷贝入用户态的 buf 中。

    ```C
    // a part of kernel/sys.c
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
    	int prev_inode_num = now_inode->i_num;
    	if (now_inode == current->root)
    		strcpy(nowbuf, "/");
    	while (now_inode != current->root) {
    		bh = find_father_dir(&now_inode, &det);
    		idev = now_inode->i_dev;
    		inid = det->inode;
    		now_inode = iget(idev, inid);
    		bh = find_same_inode(&now_inode, &de, prev_inode_num);
    		prev_inode_num = det->inode;
    		strcpy(buf_name, "/");
    		strcat(buf_name, de->name);
    		strcat(buf_name, nowbuf);
    		strcpy(nowbuf, buf_name);
    	}
    	int chars = size;
    	char *p1 = nowbuf, *p2 = buf;
    	++chars;
    	while (chars-- > 0)
    		put_fs_byte(*(p1++), p2++);
    	return (long)buf;
    }  
    ```

    ```C
    // a part of namei.c
    struct buffer_head * find_father_dir(struct m_inode ** dir, struct dir_entry ** res_dir) {
    	int entries;
    	int block,i;
    	struct buffer_head * bh;
    	struct dir_entry * de;
    	struct super_block * sb; 
    	int namelen = 2;
    	const char name[] = "..";
    #ifdef NO_TRUNCATE
    	if (namelen > NAME_LEN)
    		return NULL;
    #else
    	if (namelen > NAME_LEN)
    		namelen = NAME_LEN;
    #endif
    	entries = (*dir)->i_size / (sizeof (struct dir_entry)); 
    	*res_dir = NULL;
    	if (!namelen)
    		return NULL;
    	if (namelen==2 && get_fs_byte(name)=='.' && get_fs_byte(name+1)=='.') {
    		if ((*dir) == current->root)
    			namelen=1;
    		else if ((*dir)->i_num == ROOT_INO) {
    			sb=get_super((*dir)->i_dev);    
    			if (sb->s_imount) {				
    				iput(*dir);					
    				(*dir)=sb->s_imount;
    				(*dir)->i_count++;			
    			}
    		}
    	}
    	if (!(block = (*dir)->i_zone[0])) 		
    		return NULL;
    	if (!(bh = bread((*dir)->i_dev,block))) 
    		return NULL;
    	i = 0;
    	de = (struct dir_entry *) bh->b_data;   
    	while (i < entries) {					
    		if ((char *)de >= BLOCK_SIZE+bh->b_data) {
    			brelse(bh);
    			bh = NULL;
    			if (!(block = bmap(*dir,i/DIR_ENTRIES_PER_BLOCK)) ||
    			    !(bh = bread((*dir)->i_dev,block))) {
    				i += DIR_ENTRIES_PER_BLOCK;
    				continue;
    			}
    			de = (struct dir_entry *) bh->b_data;
    		}
    		// The only changed code there...
    		if ((de->name[0] == '.' && de->name[1] == '.' && de->name[2] == '\0')) {
    			*res_dir = de;
    			return bh;
    		}
    		de++;
    		i++;
    	}
    	brelse(bh);
    	return NULL;
    }
    struct buffer_head * find_same_inode(struct m_inode ** dir, struct dir_entry ** res_dir, int yizimi) {
    	int entries;
    	int block,i;
    	struct buffer_head * bh;
    	struct dir_entry * de;
    	struct super_block * sb; 
    	int namelen = 7;
    	const char name[] = "yizimi";
    #ifdef NO_TRUNCATE
    	if (namelen > NAME_LEN)
    		return NULL;
    #else
    	if (namelen > NAME_LEN)
    		namelen = NAME_LEN;
    #endif
    	entries = (*dir)->i_size / (sizeof (struct dir_entry)); 
    	*res_dir = NULL;
    	if (!namelen)
    		return NULL;
    	if (namelen==2 && name[0]=='.' && name[1]=='.') {
    		if ((*dir) == current->root)
    			namelen=1;
    		else if ((*dir)->i_num == ROOT_INO) {
    			sb=get_super((*dir)->i_dev);    
    			if (sb->s_imount) {				
    				iput(*dir);					
    				(*dir)=sb->s_imount;
    				(*dir)->i_count++;			
    			}
    		}
    	}
    	if (!(block = (*dir)->i_zone[0])) 		 
    		return NULL;
    	if (!(bh = bread((*dir)->i_dev,block))) 
    		return NULL;
    	i = 0;
    	de = (struct dir_entry *) bh->b_data;   
    	while (i < entries) {					
    		if ((char *)de >= BLOCK_SIZE+bh->b_data) {
    			brelse(bh);
    			bh = NULL;
    			if (!(block = bmap(*dir,i/DIR_ENTRIES_PER_BLOCK)) ||
    			    !(bh = bread((*dir)->i_dev,block))) {
    				i += DIR_ENTRIES_PER_BLOCK;
    				continue;
    			}
    			de = (struct dir_entry *) bh->b_data; 
    		}
    		if (yizimi == de->inode) { // The only changed code there...
    			*res_dir = de;
    			return bh;
    		}
    		de++;
    		i++;
    	}
    	brelse(bh);
    	return NULL;
    }
    ```

    

    ## 五、测试过程及画面

    以下测试环境已配置好测试文件，文件夹位置为 /usr/root/1

    测试环境：bochs + linux0.11

    ### 1. execve2

    首先在相应位置打补丁（指令打补丁出现问题，故通过补丁文件自行添加补丁代码）

    

    ### 2. getdents

    指令（虚拟机开机后）

    ```
    cd 1
    make clean
    make getdents
    ./getdents
    ```

    效果：

    ![pic_getdents](Z:\os\README.assets\pic_getdents-16560369930822.png)

    ### 3. sleep

    指令（虚拟机开机后）

    ```shell
    cd 1
    make clean
    make sleep
    ./sleep
    ```

    效果：

    ![](Z:\os\README.assets\pic_sleep.png)

    ### 4. getcwd

    指令（虚拟机开机后）

    ```shell
    cd 1
    make clean
    make getcwd
    ./getcwd
    ```

    效果：

    ![](Z:\os\README.assets\pic_getcwd.png)
