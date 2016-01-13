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
_CONSTANT_0:
	.word 1
	.align 3
	.text
	ldr w9, _CONSTANT_0
	str w9, [x29, #-12]
	.data
_CONSTANT_2:
	.word 5
	.align 3
	.text
	ldr w9, _CONSTANT_2
	ldr w10, [x29, #-12]
	lsl w10, w10, #2
	add x11, x29, #-4
	sub x11, x11, x10
	str w9, [x11, #0]
	ldr w9, [x29, #-12]
	lsl w9, w9, #2
	add x10, x29, #-4
	sub x10, x10, x9
	ldr w11, [x10, #0]
	mov w0, w11
	bl _write_int
	.data
_CONSTANT_3: .ascii "\n"
	.align 2
	.text
	ldr x0, =_CONSTANT_3
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
	.word 104
