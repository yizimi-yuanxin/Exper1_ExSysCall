//
// This file is part of the alternative 80386 math library and is
// covered by the GNU General Public license with my modification
// as noted in the README file that accompanied this file.
//
// Copyright 1990 G. Geers
//
// Modified by H.J. Lu for Linux 1992
//
//

	.file	"atanh.s"

	.text
	.align	2
Lhalf:
	.double 0d5.0000000000000000000000e-01

	.align	2
	.globl	_atanh
_atanh:
	fld1
	faddl	4(%esp)
	fld1
	fsubl	4(%esp)
	fdivrp

	fldln2
	fxch %st(1)
	fyl2x

	fldl Lhalf
	fmulp

	ret
