	.globl	_fabs
_fabs:
	fldl	4(%esp)
	fabs
	ret
