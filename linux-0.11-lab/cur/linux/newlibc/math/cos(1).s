/* This is file COS.S */
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

L0:
	.quad	0xffffffffffffffff

	.globl	_cos
_cos:
	fldl	4(%esp)
	fcos
	fstsw
	sahf
	jnp	L1
	fstp	%st(0)
	fldl	L0
L1:
	ret

