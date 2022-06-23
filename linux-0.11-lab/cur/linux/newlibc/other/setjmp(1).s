/*
 * setjmp & longjmp for gcc.
 *
 * We need to save all regs except %eax,%ecx,%edx, as these are
 * used by calls.
 *
 * Jump buffer looks like this (same as bruce evans for minix):
 *
 * 00: %ebp
 * 04: %esp
 * 08: %eip
 * 0C: %ebx
 * 10: %esi
 * 14: %edi
 *
 * Total length hex 18 = 24 bytes.
 */

.text
.globl _setjmp,_longjmp
.align	2
_setjmp:
	popl %ecx		# get return address
	movl 0(%esp),%edx	# and jump buffer address
	movl %ebp,0(%edx)
	movl %esp,4(%edx)
	movl %ecx,8(%edx)
	movl %ebx,12(%edx)
	movl %esi,16(%edx)
	movl %edi,20(%edx)
	xorl %eax,%eax		# non-jump return
	jmpl *%ecx

.align	2
_longjmp:
	movl 4(%esp),%edx	# jump buffer address
	movl 8(%esp),%eax	# val
	cmpl $1,%eax		# Value may not be zero (code by bruce?)
	adcb $0,%al		# nice code, somewhat cryptic, no?
	movl 0(%edx),%ebp	# restore %ebp
	movl 4(%edx),%esp
	movl 12(%edx),%ebx
	movl 16(%edx),%esi
	movl 20(%edx),%edi
	jmp 8(%edx)
