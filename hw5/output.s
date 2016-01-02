	.data
_g_n:
	.word 0
	.align 3
	.text
	.text
_start_foo:
	str x30, [sp, #0]
	str x29, [sp, #-8]
	add x29, sp, #-8
	add sp, sp, #-16
	ldr x30, =_frameSize_foo
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

	ldr x9, =_g_n:
	ldr w10, [x9, #0]
_CONSTANT_0:
	.word 1
	.align 3
	.text
	ldr w9, _CONSTANT_0
	add w10, w10, w9
	ldr x9, =_g_n:
	str w10, [x9, #0]
	ldr x9, =_g_n:
	ldr w10, [x9, #0]
	mov w0, w10
	b _end_foo

_end_foo:
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
_frameSize_foo:
	.word 92
	.text
_start_main:
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

	bl _start_foo
	mov w9, w0
	str w9, [x29, #-4]

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
	.word 96
