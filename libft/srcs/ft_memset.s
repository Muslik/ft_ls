/*
** void *ft_memset(void *buff, char byte, size_t buffsize);
**       |               |         |           |
**       |               v         v           v
** %rax<-+               %rdi      %rsi        %rdx
*/

.text
.globl  _ft_memset

_ft_memset:
	pushq	%rdi
	mov		%rsi, %rax			/*	Помещаем заполнитель в RAX	*/
	shl		$8, %rax			/*	Сдвигаем его на 8 бит (RAX << 8)	*/
	or		%rax, %rsi			/*	получаем 0:0:0:0:0:0:b:b	*/
	or		%rsi, %rax			/*		*/
	shl		$16, %rax			/*		*/
	or		%rax, %rsi			/*	получаем 0:0:0:0:b:b:b:b	*/
	or		%rsi, %rax			/*		*/
	shl		$32, %rax			/*		*/
	or		%rax, %rsi			/*	получаем b:b:b:b:b:b:b:b	*/

	mov		%rdi, %rax			/*		*/
	and		$0b111, %rax		/*	В RAX кол-во невыровненных байт	*/
	mov		$8, %rcx			/*		*/
	sub		%rax, %rcx			/*	В RCX кол-во бай до начала слова	*/

	cmp		$7, %rdx			/*	Если size меньше 8	*/
	ja		above_seven			/*	то записываем только size байт	*/
	mov		%rdx, %rcx			/*		*/

above_seven:
	lea		(%rdi, %rdx), %rdx	/*	В RDX конец буфера	*/
	mov		%rsi, %rax			/*	В RAX заполнитель для получения байта (al)*/

	testq	$0b1, %rcx			/*	Если установлен бит 1, то записывае	м*/
	je		b1					/*	1 байт в память	*/
	movb	%al, (%rdi)
	inc		%rdi
b1:
	testq	$0b10, %rcx			/*	Если установлен бит 10, то записываем	*/
	je		b10					/*	2 байта в память	*/
	movw	%ax, (%rdi)
	add		$2, %rdi
b10:
	testq	$0b100, %rcx		/*	Если установлен бит 100, то записываем	*/
	je		b100				/*	4 байта в память	*/
	movl	%eax, (%rdi)
	add		$4, %rdi
b100:

/*
** buff:RDI byte:RAX buffend:RDX
*/

	sub		%rdi, %rdx			/*	Вычисление размера буфера */
	mov		%rdx, %rcx
	shr		$3, %rcx

	rep		stosq				/*	Копирование RAX в (RDI), RDI += 8, */
								/*	декремент ECX и проверка его на ноль*/
end:
	and		$0b111, %rdx
	testq	$0b1, %rdx			/*	Если установлен бит 1, то записываем	*/
	je		e1					/*	1 байт в память	*/
	movb	%al, (%rdi)
	inc		%rdi
e1:
	testq	$0b10, %rdx			/*	Если установлен бит 10, то записываем*/
	je		e10					/*	2 байта в память	*/
	movw	%ax, (%rdi)
	add		$2, %rdi
e10:
	testq	$0b100, %rdx		/*	Если установлен бит 100, то записываем	*/
	je		rtn 				/*	4 байта в память	*/
	movl	%eax, (%rdi)
	add		$4, %rdi
rtn:
	popq	%rax
	ret
