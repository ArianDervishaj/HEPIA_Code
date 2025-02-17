	.file	"peterson.c"
	.local	n
	.comm	n,4,4
	.local	intention
	.comm	intention,2,1
	.local	turn
	.comm	turn,4,4
	.text
	.type	error, @function
error:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	perror
	movl	$1, %edi
	call	exit
	.cfi_endproc
.LFE2:
	.size	error, .-error
	.type	peterson, @function
peterson:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -12(%rbp)
	movl	$0, -16(%rbp)
	jmp	.L3
.L6:
	movl	-12(%rbp), %eax
	cltq
	movb	$1, intention(%rax)
	movl	$1, %eax
	subl	-12(%rbp), %eax
	movl	%eax, turn(%rip)
	mfence
	nop
.L5:
	movl	$1, %eax
	subl	-12(%rbp), %eax
	cltq
	movzbl	intention(%rax), %eax
	testb	%al, %al
	je	.L4
	movl	$1, %eax
	subl	-12(%rbp), %eax
	movl	%eax, %edx
	movl	turn(%rip), %eax
	cmpl	%eax, %edx
	je	.L5
.L4:
	movl	n(%rip), %eax
	addl	$1, %eax
	movl	%eax, n(%rip)
	movl	-12(%rbp), %eax
	cltq
	movb	$0, intention(%rax)
	addl	$1, -16(%rbp)
.L3:
	cmpl	$4999999, -16(%rbp)
	jle	.L6
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	peterson, .-peterson
	.section	.rodata
.LC0:
	.string	"pthread_create"
.LC1:
	.string	"pthread_join"
	.align 8
.LC2:
	.string	"%d ERRORS out of %d concurrent iterations!\n"
	.align 8
.LC3:
	.string	"OK: 0 errors in %d concurrent iterations\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$0, -36(%rbp)
	movl	$1, -32(%rbp)
	leaq	-36(%rbp), %rdx
	leaq	-24(%rbp), %rax
	movq	%rdx, %rcx
	movl	$peterson, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_create
	testl	%eax, %eax
	je	.L9
	movl	$.LC0, %edi
	call	error
.L9:
	leaq	-32(%rbp), %rdx
	leaq	-16(%rbp), %rax
	movq	%rdx, %rcx
	movl	$peterson, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_create
	testl	%eax, %eax
	je	.L10
	movl	$.LC0, %edi
	call	error
.L10:
	movq	-24(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_join
	testl	%eax, %eax
	je	.L11
	movl	$.LC1, %edi
	call	error
.L11:
	movq	-16(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_join
	testl	%eax, %eax
	je	.L12
	movl	$.LC1, %edi
	call	error
.L12:
	movl	n(%rip), %eax
	movl	$10000000, %edx
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -28(%rbp)
	cmpl	$0, -28(%rbp)
	je	.L13
	movl	-28(%rbp), %eax
	movl	$5000000, %edx
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	jmp	.L14
.L13:
	movl	$5000000, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
.L14:
	movl	$0, %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L16
	call	__stack_chk_fail
.L16:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
