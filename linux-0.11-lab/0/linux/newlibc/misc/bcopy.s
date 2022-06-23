/*
 * Copyright 1990,91 by Thomas Roell, Dinkelscherben, Germany.
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of Thomas Roell not be used in
 * advertising or publicity pertaining to distribution of the software without
 * specific, written prior permission.  Thomas Roell makes no representations
 * about the suitability of this software for any purpose.  It is provided
 * "as is" without express or implied warranty.
 *
 * THOMAS ROELL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THOMAS ROELL BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 * Author:  Thomas Roell, roell@informatik.tu-muenchen.de
 *
 * $Header: /proj/X11/mit/server/ddx/at386/bsdemul/RCS/bcopy.s,v 1.5 91/02/10 16:23:21 root Exp $
 */

/*
 * bcopy (b1, b2, length)
 * register unsigned char *b1, *b2;
 * register length;
 * {
 *   if (b1 < b2) {
 *	b2 += length;
 *	b1 += length;
 *	while (length--) {
 *	    *--b2 = *--b1;
 *	}
 *   }  
 *   else {
 *      while (length--) {
 *	    *b2++ = *b1++;
 *	}
 *   }
 * }
 */

	.text
	.globl _bcopy
	.align 2
_bcopy:
	pushl	%ebp
	movl	%esp,%ebp
	pushl	%esi		/* save register */
	pushl	%edi

	movl	8(%ebp),%esi	/* unsigned char * b1  */
	movl	12(%ebp),%edi	/* unsigned char * b2  */
	movl	16(%ebp),%ecx	/* length */
	
	cmpl	%esi,%edi
	jbe	.uploop

	std
	addl	%ecx,%esi	/* adjust pointer, so that we can move */
	addl	%ecx,%edi

	movl	%ecx,%edx
	shrl	$2,%ecx
	subl	$4,%esi
	subl	$4,%edi
	rep			/* move longwords */
	movsl
	addl	$4,%esi
	addl	$4,%edi
	
	movl	%edx,%ecx
	andl	$3,%ecx

	decl	%esi
	decl	%edi
	rep			/* move bytes */
	movsb

	cld
	popl	%edi
	popl	%esi
	leave
	ret

.uploop:
	movl	%ecx,%edx
	shrl	$2,%ecx
	rep			/* move longwords */
	movsl
	
	movl	%edx,%ecx
	andl	$3,%ecx

	rep			/* move bytes */
	movsb

	popl	%edi
	popl	%esi
	leave
	ret
