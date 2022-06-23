//
// This file is part of the alternative 80386 math library and is
// covered by the GNU General Public license with my modification
// as noted in the README file that accompanied this file.
//
// Copyright 1990 G. Geers
//
// Modified by H.J. Lu for Linux 1992
//

	.file	"acosh.s"

	.align	2
	.globl	_acosh
_acosh:
	fldl	4(%esp)
	fmull	4(%esp)

	fld1
	fsubrp
	fsqrt

	faddl	4(%esp)

	fldln2

	fxch	%st(1)
	fyl2x

	ret
