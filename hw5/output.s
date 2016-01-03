	.text
_start_print_space:
	str x30, [sp, #0]
	str x29, [sp, #-8]
	add x29, sp, #-8
	add sp, sp, #-16
	ldr x30, =_frameSize_print_space
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
_CONSTANT_0: .ascii " "
.align 3
.text
ldr x0, =_CONSTANT_0
bl _write_str

_end_print_space:
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
_frameSize_print_space:
	.word 92
	.text
_start_print_star:
	str x30, [sp, #0]
	str x29, [sp, #-8]
	add x29, sp, #-8
	add sp, sp, #-16
	ldr x30, =_frameSize_print_star
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
_CONSTANT_1: .ascii "*"
.align 3
.text
ldr x0, =_CONSTANT_1
bl _write_str

_end_print_star:
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
_frameSize_print_star:
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
_CONSTANT_2:
	.word 11
	.align 3
	.text
	ldr w9, _CONSTANT_2
	str w9, [x29, #-16]
	ldr w10, [x29, #-16]
	.data
_CONSTANT_4:
	.word 1
	.align 3
	.text
	ldr w11, _CONSTANT_4
	sub w10, w10, w11
	.data
_CONSTANT_5:
	.word 2
	.align 3
	.text
	ldr w11, _CONSTANT_5
	sdiv w10, w10, w11
	str w10, [x29, #-12]
WhileTest1:
	ldr w11, [x29, #-12]
	.data
_CONSTANT_7:
	.word 0
	.align 3
	.text
	ldr w12, _CONSTANT_7
cmp w11, 0
beq WhileExit1
	ldr w11, [x29, #-12]
	str w11, [x29, #-4]
WhileTest2:
	ldr w12, [x29, #-4]
	.data
_CONSTANT_9:
	.word 0
	.align 3
	.text
	ldr w13, _CONSTANT_9
cmp w12, 0
beq WhileExit2
	bl _start_print_space
	ldr w12, [x29, #-4]
	.data
_CONSTANT_10:
	.word 1
	.align 3
	.text
	ldr w13, _CONSTANT_10
	sub w12, w12, w13
	str w12, [x29, #-4]
b WhileTest2
WhileExit2:
	ldr w13, [x29, #-16]
	ldr w14, [x29, #-12]
	.data
_CONSTANT_12:
	.word 2
	.align 3
	.text
	ldr w15, _CONSTANT_12
	mul w14, w14, w15
	sub w13, w13, w14
	str w13, [x29, #-4]
WhileTest3:
	ldr w14, [x29, #-4]
	.data
_CONSTANT_14:
	.word 0
	.align 3
	.text
	ldr w15, _CONSTANT_14
cmp w14, 0
beq WhileExit3
	bl _start_print_star
	ldr w14, [x29, #-4]
	.data
_CONSTANT_15:
	.word 1
	.align 3
	.text
	ldr w15, _CONSTANT_15
	sub w14, w14, w15
	str w14, [x29, #-4]
b WhileTest3
WhileExit3:
	ldr w15, [x29, #-12]
	str w15, [x29, #-4]
WhileTest4:
	ldr w-1, [x29, #-4]
	.data
_CONSTANT_18:
	.word 0
	.align 3
	.text
	ldr w-1, _CONSTANT_18
cmp w-1, 0
beq WhileExit4
	bl _start_print_space
	ldr w-1, [x29, #-4]
	.data
_CONSTANT_19:
	.word 1
	.align 3
	.text
	ldr w-1, _CONSTANT_19
	sub w-1, w-1, w-1
	str w-1, [x29, #-4]
b WhileTest4
WhileExit4:
	ldr w-1, [x29, #-12]
	.data
_CONSTANT_21:
	.word 1
	.align 3
	.text
	ldr w-1, _CONSTANT_21
	sub w-1, w-1, w-1
	str w-1, [x29, #-12]
.data
_CONSTANT_23: .ascii "\n"
.align 2
.text
ldr x0, =_CONSTANT_23
bl _write_str
b WhileTest1
WhileExit1:
	.data
_CONSTANT_24:
	.word 5
	.align 3
	.text
	ldr w-1, _CONSTANT_24
	str w-1, [x29, #-12]
	.data
_CONSTANT_26:
	.word 3
	.align 3
	.text
	ldr w-1, _CONSTANT_26
	str w-1, [x29, #-8]
WhileTest5:
	ldr w-1, [x29, #-8]
	.data
_CONSTANT_28:
	.word 0
	.align 3
	.text
	ldr w-1, _CONSTANT_28
cmp w-1, 0
beq WhileExit5
	ldr w-1, [x29, #-12]
	str w-1, [x29, #-4]
WhileTest6:
	ldr w-1, [x29, #-4]
	.data
_CONSTANT_30:
	.word 0
	.align 3
	.text
	ldr w-1, _CONSTANT_30
cmp w-1, 0
beq WhileExit6
	bl _start_print_space
	ldr w-1, [x29, #-4]
	.data
_CONSTANT_31:
	.word 1
	.align 3
	.text
	ldr w-1, _CONSTANT_31
	sub w-1, w-1, w-1
	str w-1, [x29, #-4]
b WhileTest6
WhileExit6:
	ldr w-1, [x29, #-16]
	ldr w-1, [x29, #-12]
	.data
_CONSTANT_33:
	.word 2
	.align 3
	.text
	ldr w-1, _CONSTANT_33
	mul w-1, w-1, w-1
	sub w-1, w-1, w-1
	str w-1, [x29, #-4]
WhileTest7:
	ldr w-1, [x29, #-4]
	.data
_CONSTANT_35:
	.word 0
	.align 3
	.text
	ldr w-1, _CONSTANT_35
cmp w-1, 0
beq WhileExit7
	bl _start_print_star
	ldr w-1, [x29, #-4]
	.data
_CONSTANT_36:
	.word 1
	.align 3
	.text
	ldr w-1, _CONSTANT_36
	sub w-1, w-1, w-1
	str w-1, [x29, #-4]
b WhileTest7
WhileExit7:
	ldr w-1, [x29, #-12]
	str w-1, [x29, #-4]
WhileTest8:
	ldr w-1, [x29, #-4]
	.data
_CONSTANT_39:
	.word 0
	.align 3
	.text
	ldr w-1, _CONSTANT_39
cmp w-1, 0
beq WhileExit8
	bl _start_print_space
	ldr w-1, [x29, #-4]
	.data
_CONSTANT_40:
	.word 1
	.align 3
	.text
	ldr w-1, _CONSTANT_40
	sub w-1, w-1, w-1
	str w-1, [x29, #-4]
b WhileTest8
WhileExit8:
.data
_CONSTANT_42: .ascii "\n"
.align 2
.text
ldr x0, =_CONSTANT_42
bl _write_str
	ldr w-1, [x29, #-8]
	.data
_CONSTANT_43:
	.word 1
	.align 3
	.text
	ldr w-1, _CONSTANT_43
	sub w-1, w-1, w-1
	str w-1, [x29, #-8]
b WhileTest5
WhileExit5:

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
	.word 108
