/* This is file EXP.S */
/*
** Copyright (C) 1991 DJ Delorie, 24 Kirsten Ave, Rochester NH 03867-2954
**
** Modified O.ROBERT 24, Avenue de Verdun 92170 VANVES, FRANCE
**
** E-mail: roberto@germinal.ibp.fr
**
** This file is distributed under the terms listed in the document
** "copying.dj", available from DJ Delorie at the address above.
** A copy of "copying.dj" should accompany this file; if not, a copy
** should be available from where this file was obtained.  This file
** may not be distributed without a verbatim copy of "copying.dj".
**
** This file is distributed WITHOUT ANY WARRANTY; without even the implied
** warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
**
** or	03-Apr-1991	corrected bug about argument zero to pow
**			fyl2x didn't like it
*/

/* History:15,24 */
	.data
LCW1:
	.word	0
LCW2:
	.word	0

	.text

LC0:
	.double	0d1.0e+00

	.globl	_pow2
_pow2:
	fldl	4(%esp)
Lpow2:
	fstcww	LCW1
	fstcww	LCW2
	fwait
	andl	$0xf3ff,LCW2
	orl	$0x0400,LCW2
	fldcww	LCW2
	fldl	%st(0)
	frndint
	fldcww	LCW1
	fxch	%st(1)
	fsub	%st(1),%st
	f2xm1
	faddl	LC0
	fscale
	fstp	%st(1)
	ret

	.globl	_exp
_exp:
	fldl	4(%esp)
	fldl2e
	fmulp
	jmp	Lpow2

	.globl	_pow10
_pow10:
	fldl	4(%esp)
	fldl2t
	fmulp
	jmp	Lpow2

	.globl	_pow
_pow:
	fldl	4(%esp)
	ftst
	fnstsww %ax
	sahf
	je	zero1
	fldl	12(%esp)
	ftst
	fnstsww %ax
	sahf
	je	zero2
	fxch	%st(1)
	fyl2x
	jmp	Lpow2
zero1:
	fstpl	4(%esp)
	fldzl
	ret
zero2:
	fstpl	4(%esp)
	fstpl	4(%esp)
	fld1l
	ret
