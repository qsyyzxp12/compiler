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
	.word 0
	.align 3
	.text
	ldr w9, _CONSTANT_0
	str w9, [x29, #-8]
# forinit
	.data
_CONSTANT_1:
	.word 0
	.align 3
	.text
	ldr w9, _CONSTANT_1
	str w9, [x29, #-4]
# fortest
ForTest1:
	ldr w10, [x29, #-4]
	.data
_CONSTANT_2:
	.word 10
	.align 3
	.text
	ldr w11, _CONSTANT_2
	cmp w10, w11
	cset w10, lt
	cmp w10, 0
	cset w9, ne
	cmp w9, 0
	beq shortCut0
	ldr w10, [x29, #-8]
	.data
_CONSTANT_3:
	.word 5
	.align 3
	.text
	ldr w11, _CONSTANT_3
	cmp w10, w11
	cset w10, lt
	cmp w10, 0
	cset w9, ne
shortCut0:
	cmp w9, 0
	beq ForExit1
	b ForBody1
# forinc
ForInc1:
	ldr w9, [x29, #-4]
	.data
_CONSTANT_4:
	.word 1
	.align 3
	.text
	ldr w10, _CONSTANT_4
	add w9, w9, w10
	str w9, [x29, #-4]
b ForTest1
# forbody
ForBody1:
	ldr w9, [x29, #-4]
	mov w0, w9
	bl _write_int
	.data
_CONSTANT_5: .ascii "\n"
	.align 2
	.text
	ldr x0, =_CONSTANT_5
	bl _write_str
	ldr w9, [x29, #-8]
	.data
_CONSTANT_6:
	.word 1
	.align 3
	.text
	ldr w10, _CONSTANT_6
	add w9, w9, w10
	str w9, [x29, #-8]
b ForInc1
ForExit1:

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
	.word 100
