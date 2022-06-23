//
// This file is part of the math library for Linux and is
// covered by the GNU General Public license version 2, or
// any later version.
//
// Copyright 1992 by H.J. Lu
//
	.file	"sin.s"
	.text
	.align	2
	.globl	_sin
_sin:
	fldl	4(%esp)
	jmp	L3
L1:
	fldpi
	fld	%st(0)
	faddp	%st,%st(1)
	fxch	%st(1)
L2:
	fprem1
	fstsw	%ax
	sahf
	jp	L2
	fxch	%st(1)
	fstp	%st(0)
L3:
	fsin
	fstsw	%ax
	sahf
	jp	L1
	ret
