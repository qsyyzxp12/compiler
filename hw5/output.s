	.data
_g_n:
	.place 2
	.text
	.text
_start_main
	str x30, [sp, #0]
	str x29, [sp, #-8]
	add x29, sp, #-8
	add sp, sp, #-16
	ldr x30, =_frameSize_main
	ldr x30, [x30, #0]
	sub sp, sp, w30
	x9, [sp, #8]
	x10, [sp, #16]
	x11, [sp, #24]
	x12, [sp, #32]
	x13, [sp, #40]
	x14, [sp, #48]
	x15, [sp, #56]
	x16, [sp, #64]
	x17, [sp, #68]
	x18, [sp, #72]
	x19, [sp, #76]
	x20, [sp, #80]
	x21, [sp, #84]
	x22, [sp, #88]
	x23, [sp, #92]

_CONSTANT_0:
	.word 1
	.align 3
	.text
	ldr w9, _CONSTANT_0
	ldr x10, =_g_n:
	str w9, [x10, #-4]

_end_main:
	x9, [sp, #8]
	x10, [sp, #16]
	x11, [sp, #24]
	x12, [sp, #32]
	x13, [sp, #40]
	x14, [sp, #48]
	x15, [sp, #56]
	x16, [sp, #64]
	x17, [sp, #68]
	x18, [sp, #72]
	x19, [sp, #76]
	x20, [sp, #80]
	x21, [sp, #84]
	x22, [sp, #88]
	x23, [sp, #92]
	x30, [x29, #8]
	mov sp, x29
	add sp, sp, #8
	ldr x29, [x29, #0]
	RET x30
	.data
_frameSize_main:
	.word 92
