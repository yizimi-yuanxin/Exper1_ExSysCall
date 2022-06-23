//
// This file is part of the alternative 80386 math library and is
// covered by the GNU General Public license with my modification
// as noted in the README file that accompanied this file.
//
// Copyright 1990 G. Geers
//
// Modified by H.J. Lu
//

	.file	"values.s"

	.align	2
	.globl	_isnan
_isnan:
	movl	8(%esp),%eax
	andl	$0x7ff00000,%eax
	cmpl	$0x7ff00000,%eax
	jne	Lnotnan
	movl	8(%esp),%eax
	andl	$0xfffff,%eax
	orl	4(%esp),%eax
	je	Lnotnan

	xorl	%eax,%eax
	incl	%eax
	ret

Lnotnan:
	xorl	%eax,%eax
	ret

	.align	2
	.globl	_isinf
_isinf:
	movl	8(%esp),%eax
	andl	$0x7ff00000, %eax
	cmpl	$0x7ff00000, %eax
	je	Lcouldbeinf

Lnotinf:
	xorl	%eax,%eax
	ret

Lcouldbeinf:
	movl	8(%esp),%eax
	andl	$0xfffff,%eax
	orl	4(%esp),%eax
	jne	Lnotinf

	xorl	%eax,%eax
	incl	%eax
	ret
