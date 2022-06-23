/* This is file ACOS.S */
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

	.text
	.globl	_acos
	.align	2
_acos:
	fldl	4(%esp)
	fld1
	fsubp	%st(0),%st(1)
	fsqrt

	fldl	4(%esp)
	fld1
	faddp	%st(0),%st(1)
	fsqrt

	fpatan

	fld	%st(0)
	faddp
	ret
