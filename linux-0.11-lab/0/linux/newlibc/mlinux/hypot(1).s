//
// This file is part of the alternative 80386 math library and is
// covered by the GNU General Public license with my modification
// as noted in the README file that accompanied this file.
//
// Copyright 1990 G. Geers
//
// Modified by H.J. Lu for Linux 1992
//

	.file "hypot.s"

	.text
	.align	2
	.globl	_hypot
_hypot:
	fldl 4(%esp)
	fmull 4(%esp)
	fldl 12(%esp)
	fmull 12(%esp)
	faddp
	fsqrt
	ret
