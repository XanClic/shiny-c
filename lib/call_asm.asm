format ELF64
use64


public __asm_call

__asm_call:
push    rbx
push    rcx
push    rsi
mov     rbx,rdi
test    r8,r8
jz      no_fpargs
movsd   xmm0,[rcx+0x00]
movsd   xmm1,[rcx+0x08]
movsd   xmm2,[rcx+0x10]
movsd   xmm3,[rcx+0x18]
movsd   xmm4,[rcx+0x20]
movsd   xmm5,[rcx+0x28]
movsd   xmm6,[rcx+0x30]
movsd   xmm7,[rcx+0x38]
no_fpargs:
mov     rdi,[rsi+0x00]
mov     rdx,[rsi+0x10]
mov     rcx,[rsi+0x18]
mov     r8, [rsi+0x20]
mov     r9, [rsi+0x28]
mov     rsi,[rsi+0x08]
call    rbx
pop     rsi
pop     rcx
pop     rbx
mov     [rsi],rax
movsd   [rcx],xmm0
ret
