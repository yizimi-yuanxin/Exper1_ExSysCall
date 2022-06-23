	.text

	.globl _environ

__entry:
	fldcw init_cw
#	movl $45,%eax
#	movl $0,%ebx
#	int $0x80
#	movl %eax,____brk_addr
	movl 8(%esp),%eax
	movl %eax,_environ
	call _main
	pushl %eax
1:      call _exit
	jmp 1b

	.data
	.align 2
_environ:
	.long 0
init_cw:
	.word 0x0262

/* Here is the dirty part. Settup up your 387 through the control word
 * (cw) register. 
 *
 *     15-13    12  11-10  9-8     7-6     5    4    3    2    1    0
 * | reserved | IC | RC  | PC | reserved | PM | UM | OM | ZM | DM | IM
 *
 * IM: Invalid operation mask
 * DM: Denormalized operand mask
 * ZM: Zero-divide mask
 * OM: Overflow mask
 * UM: Underflow mask
 * PM: Precision (inexact result) mask
 * 
 * Mask bit is 1 means no interrupt.
 *
 * PC: Precision control
 * 11 - round to extended precision
 * 10 - round to double precision
 * 00 - round to single precision
 *
 * RC: Rounding control
 * 00 - rounding to nearest
 * 01 - rounding down (toward - infinity)
 * 10 - rounding up (toward + infinity)
 * 11 - rounding toward zero
 *
 * IC: Infinity control
 * That is for 8087 and 80287 only.
 *
 * The hardware default is 0x037f. I choose 0x0262.
 */
