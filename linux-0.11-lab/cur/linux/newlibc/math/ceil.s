/* This is file CEIL.S */
/*
** Copyright (C) 1991 DJ Delorie, 24 Kirsten Ave, Rochester NH 03867-2954
**
** This file is distributed under the terms listed in the document
** "copying.dj", available from DJ Delorie at the address above.
** A copy of "copying.dj" should accompany this file; if not, a copy
** should be available from where this file was obtained.  This file
** may not be distributed without a verbatim copy of "copying.dj".
**
** This file is distributed WITHOUT ANY WARRANTY; without even the implied
** warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

	.globl	_ceil
_ceil:
	pushl	%ebp
	movl	%esp,%ebp
	sub	$8,%esp		/* -4 = old CW, -2 = new CW */

	fstcw	-4(%ebp)
	fwait
	movw	-4(%ebp),%ax
	andw	$0xf3ff,%ax
	orw	$0x0800,%ax
	movw	%ax,-2(%ebp)
	fldcww	-2(%ebp)

	fldl	8(%ebp)
	frndint

	fldcww	-4(%ebp)

	movl	%ebp,%esp
	popl	%ebp
	ret

