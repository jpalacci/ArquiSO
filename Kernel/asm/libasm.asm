GLOBAL cpuVendor
GLOBAL outputb
GLOBAL inputb
GLOBAL timerTickHandler
EXTERN timerTickHandlerC
GLOBAL sti
GLOBAL keyboardHandler
EXTERN keyboardHandlerC
GLOBAL syscallHandler
GLOBAL sys_write
EXTERN syscall_writeC
GLOBAL test
GLOBAL mouse_handler
EXTERN mouse_handlerC
GLOBAL keyboardInitialize
EXTERN keyboardInitializeC
GLOBAL cli

GLOBAL master
GLOBAL slave

EXTERN spure

section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

inputb:
	push rbp
	mov rbp, rsp
	sub rsp, 0x04
	mov [rbp-0x04], edi
	mov dx, word[rbp-0x04]
	in al, dx
	mov rsp,rbp
	pop rbp
	ret

outputb:
	push rbp
	mov rbp, rsp
	sub rsp, 0x08
	mov[rbp-4], edi
	mov [rbp-8], esi
	mov dx, word[rbp-4]
	mov al, byte[rbp-8]
	out dx, al
	mov rsp, rbp
	pop rbp
	ret

sti:
	sti
	ret

keyboardHandler:
	cli
	push rbp
	mov rbp, rsp
	call keyboardHandlerC
	mov al, 20h
	out 20h, al

	mov rsp, rbp
	pop rbp
	sti
	iretq

timerTickHandler:
	cli
	push rbp
	mov rbp, rsp

	call timerTickHandlerC
	mov al, 20h
	out 20h, al	

	mov rsp, rbp
	pop rbp
	sti
	iretq

syscallHandler:
      	push rbp
	mov rbp, rsp
        cmp rax,0x04
        je sys_write
        mov al, 20h
        out 20h, al
        mov rsp,rbp
        pop rbp
        iretq

master:
	call spure
	mov al, 20h
	out 20h, al
	ret

slave:

	call spure
	mov al, 20h
	out 0A0h, al
	out 20h, al
	ret

	
sys_write:
    
        push rbp
        mov rbp,rsp
        mov rdi,  rbx
        mov rsi, rcx
        call syscall_writeC
        mov al, 20h
        out 20h, al
        mov rsp,rbp
        pop rbp
        iretq

test:
        mov al, 11101111b
	out 0A1h,al
	ret
    
mouse_handler:
	cli
	push rbp
	mov rbp, rsp
	call mouse_handlerC
	mov al, 0x20
		
	
	out 0xA0, al

	out 0x20, al

	mov rsp, rbp
	pop rbp
	sti
	iretq

cli:
	cli
	ret


keyboardInitialize:
	push rbp
	mov rbp, rsp
	mov rsi,0;
	mov rdi, KeyBoardBuffer
	mov rsi,0
	mov rsi,100
	call keyboardInitializeC
	mov rsp, rbp
	pop rbp
	ret

section .data

msg db "hola mundo",0

section .bss
KeyBoardBuffer resb 100






