/* This is file FMOD.S */
/*
** Copyright (C) 1991 O. ROBERT, 24, Avenue de Verdun, 92170 VANVES, FRANCE
**
** Internet:	roberto@germinal.ibp.fr
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
	.text
	.globl	_fmod
	.align	2
_fmod:
	fldl	4(%esp)
	fldl	12(%esp)
	ftst
	fnstsw	%ax
	fxch	%st(1)
	sahf
	jnz	next
	fstpl	%st(0)
	jmp	out
next:
	fpreml
	fnstsw	%ax
	sahf
	jpe	next
	fstpl	%st(1)
out:
	ret
