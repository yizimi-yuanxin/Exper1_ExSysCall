//
// This file is part of the math library for Linux and is
// covered by the GNU General Public license version 2, or
// any later version.
//
// Copyright 1992 by H.J. Lu
//
	.file	"tan.s"
	.text
	.align	2
	.globl	_tan
_tan:
	fldl	4(%esp)
	jmp	L3
L1:
	fldpi
	fxch	%st(1)
L2:
	fprem1
	fstsw	%ax
	sahf
	jp	L2
	fxch	%st(1)
	fstp	%st(0)
L3:
	fptan
	fstsw	%ax
	sahf
	jp	L1
	fstp	%st(0)
	ret
