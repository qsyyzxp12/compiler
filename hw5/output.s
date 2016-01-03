	.data
_g_n:
	.word 0
	.align 3
	.text
	.text
_start_fact:
	str x30, [sp, #0]
	str x29, [sp, #-8]
	add x29, sp, #-8
	add sp, sp, #-16
	ldr x30, =_frameSize_fact
	ldr x30, [x30, #0]
	sub sp, sp, w30
	str x9, [sp, #8]
	str x10, [sp, #16]
	str x11, [sp, #24]
	str x12, [sp, #32]
	str x13, [sp, #40]
	str x14, [sp, #48]
	str x15, [sp, #56]
	str x16, [sp, #64]
	str x17, [sp, #68]
	str x18, [sp, #72]
	str x19, [sp, #76]
	str x20, [sp, #80]
	str x21, [sp, #84]
	str x22, [sp, #88]
	str x23, [sp, #92]

	ldr x9, =_g_n
	ldr w10, [x9, #0]
	.data
_CONSTANT_0:
	.word 1
	.align 3
	.text
	ldr w9, _CONSTANT_0
cmp w10, 0
beq IfElse1
	ldr x9, =_g_n
	ldr w11, [x9, #0]
	mov w0, w11
	b _end_fact
b IfExit1
IfElse1:
	ldr x9, =_g_n
	ldr w11, [x9, #0]
	.data
_CONSTANT_1:
	.word 1
	.align 3
	.text
	ldr w9, _CONSTANT_1
	sub w11, w11, w9
	ldr x9, =_g_n
	str w11, [x9, #0]
	ldr x9, =_g_n
	ldr w11, [x9, #0]
	bl _start_fact
	mov w9, w0
	mul w11, w11, w9
	mov w0, w11
	b _end_fact
IfExit1:

_end_fact:
	ldr x9, [sp, #8]
	ldr x10, [sp, #16]
	ldr x11, [sp, #24]
	ldr x12, [sp, #32]
	ldr x13, [sp, #40]
	ldr x14, [sp, #48]
	ldr x15, [sp, #56]
	ldr x16, [sp, #64]
	ldr x17, [sp, #68]
	ldr x18, [sp, #72]
	ldr x19, [sp, #76]
	ldr x20, [sp, #80]
	ldr x21, [sp, #84]
	ldr x22, [sp, #88]
	ldr x23, [sp, #92]
	ldr x30, [x29, #8]
	mov sp, x29
	add sp, sp, #8
	ldr x29, [x29, #0]
	RET x30
	.data
_frameSize_fact:
	.word 92
	.text
_start_MAIN:
	str x30, [sp, #0]
	str x29, [sp, #-8]
	add x29, sp, #-8
	add sp, sp, #-16
	ldr x30, =_frameSize_MAIN
	ldr x30, [x30, #0]
	sub sp, sp, w30
	str x9, [sp, #8]
	str x10, [sp, #16]
	str x11, [sp, #24]
	str x12, [sp, #32]
	str x13, [sp, #40]
	str x14, [sp, #48]
	str x15, [sp, #56]
	str x16, [sp, #64]
	str x17, [sp, #68]
	str x18, [sp, #72]
	str x19, [sp, #76]
	str x20, [sp, #80]
	str x21, [sp, #84]
	str x22, [sp, #88]
	str x23, [sp, #92]

.data
_CONSTANT_2: .ascii "Enter a number:"
.align 3
.text
ldr x0, =_CONSTANT_2
bl _write_str
bl _read_int
mov w9, w0
	mov w11, w0
	ldr x12, =_g_n
	str w11, [x12, #0]
	ldr x11, =_g_n
	ldr w12, [x11, #0]
	.data
_CONSTANT_3:
	.word 1
	.align 3
	.text
	ldr w11, _CONSTANT_3
	add w12, w12, w11
	ldr x11, =_g_n
	str w12, [x11, #0]
	ldr x11, =_g_n
	ldr w12, [x11, #0]
	.data
_CONSTANT_4:
	.word 1
	.align 3
	.text
	ldr w11, _CONSTANT_4
cmp w12, 0
beq IfElse2
	bl _start_fact
	mov w11, w0
	str w11, [x29, #-4]
b IfExit2
IfElse2:
	.data
_CONSTANT_6:
	.word 1
	.align 3
	.text
	ldr w11, _CONSTANT_6
	str w11, [x29, #-4]
IfExit2:
.data
_CONSTANT_8: .ascii "The factorial is "
.align 1
.text
ldr x0, =_CONSTANT_8
bl _write_str
	ldr w11, [x29, #-4]
mov w0, w11
bl _write_int
.data
_CONSTANT_9: .ascii "\\n"
.align 3
.text
ldr x0, =_CONSTANT_9
bl _write_str

_end_MAIN:
	ldr x9, [sp, #8]
	ldr x10, [sp, #16]
	ldr x11, [sp, #24]
	ldr x12, [sp, #32]
	ldr x13, [sp, #40]
	ldr x14, [sp, #48]
	ldr x15, [sp, #56]
	ldr x16, [sp, #64]
	ldr x17, [sp, #68]
	ldr x18, [sp, #72]
	ldr x19, [sp, #76]
	ldr x20, [sp, #80]
	ldr x21, [sp, #84]
	ldr x22, [sp, #88]
	ldr x23, [sp, #92]
	ldr x30, [x29, #8]
	mov sp, x29
	add sp, sp, #8
	ldr x29, [x29, #0]
	RET x30
	.data
_frameSize_MAIN:
	.word 96
