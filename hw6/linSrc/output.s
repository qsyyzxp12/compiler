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
	.data
_CONSTANT_1:
	.word 2
	.align 3
	.text
	ldr w10, _CONSTANT_1
	add w9, w9, w10
	.data
_CONSTANT_2:
	.word 3
	.align 3
	.text
	ldr w10, _CONSTANT_2
	mul w9, w9, w10
	.data
_CONSTANT_3:
	.word 4
	.align 3
	.text
	ldr w10, _CONSTANT_3
	.data
_CONSTANT_4:
	.word 5
	.align 3
	.text
	ldr w11, _CONSTANT_4
	sdiv w10, w10, w11
	sub w9, w9, w10
	.data
_CONSTANT_5:
	.word 1
	.align 3
	.text
	ldr w10, _CONSTANT_5
	neg w10, w10
	add w9, w9, w10
	str w9, [x29, #-12]
	ldr w9, [x29, #-12]
mov w0, w9
bl _write_int
.data
_CONSTANT_7: .ascii "\n"
.align 2
.text
ldr x0, =_CONSTANT_7
bl _write_str
	.data
_CONSTANT_8:
	.word 1
	.align 3
	.text
	ldr w9, _CONSTANT_8
	str w9, [x29, #-4]
	.data
_CONSTANT_10:
	.word 2
	.align 3
	.text
	ldr w9, _CONSTANT_10
	str w9, [x29, #-8]
	.data
_CONSTANT_12:
	.word 3
	.align 3
	.text
	ldr w9, _CONSTANT_12
	str w9, [x29, #-12]
	ldr w9, [x29, #-4]
	ldr w10, [x29, #-8]
	mul w9, w9, w10
	ldr w10, [x29, #-12]
	.data
_CONSTANT_14:
	.word 4
	.align 3
	.text
	ldr w11, _CONSTANT_14
	mul w10, w10, w11
	sub w9, w9, w10
	.data
_CONSTANT_15:
	.word 5
	.align 3
	.text
	ldr w10, _CONSTANT_15
	sub w9, w9, w10
	str w9, [x29, #-12]
	ldr w9, [x29, #-12]
mov w0, w9
bl _write_int
.data
_CONSTANT_17: .ascii "\n"
.align 2
.text
ldr x0, =_CONSTANT_17
bl _write_str
	.data
_CONSTANT_18:
	.float 1.000000
	.align 3
	.text
	ldr s16, _CONSTANT_18
	.data
_CONSTANT_19:
	.float 2.000000
	.align 3
	.text
	ldr s17, _CONSTANT_19
	fadd s16, s16, s17
	.data
_CONSTANT_20:
	.float 3.000000
	.align 3
	.text
	ldr s17, _CONSTANT_20
	fmul s16, s16, s17
	.data
_CONSTANT_21:
	.float 4.000000
	.align 3
	.text
	ldr s17, _CONSTANT_21
	.data
_CONSTANT_22:
	.float 5.000000
	.align 3
	.text
	ldr s18, _CONSTANT_22
	fdiv s17, s17, s18
	fsub s16, s16, s17
	.data
_CONSTANT_23:
	.float 1.000000
	.align 3
	.text
	ldr s17, _CONSTANT_23
	fneg s17, s17
	fadd s16, s16, s17
	str s16, [x29, #-24]
	ldr s16, [x29, #-24]
fmov s0, s16
bl _write_float
.data
_CONSTANT_25: .ascii "\n"
.align 2
.text
ldr x0, =_CONSTANT_25
bl _write_str
	.data
_CONSTANT_26:
	.float 1.000000
	.align 3
	.text
	ldr s16, _CONSTANT_26
	str s16, [x29, #-16]
	.data
_CONSTANT_28:
	.float 2.000000
	.align 3
	.text
	ldr s16, _CONSTANT_28
	str s16, [x29, #-20]
	.data
_CONSTANT_30:
	.float 3.000000
	.align 3
	.text
	ldr s16, _CONSTANT_30
	str s16, [x29, #-24]
	ldr s16, [x29, #-16]
	ldr s17, [x29, #-20]
	fmul s16, s16, s17
	ldr s17, [x29, #-24]
	.data
_CONSTANT_32:
	.float 4.000000
	.align 3
	.text
	ldr s18, _CONSTANT_32
	fmul s17, s17, s18
	fsub s16, s16, s17
	.data
_CONSTANT_33:
	.float 5.000000
	.align 3
	.text
	ldr s17, _CONSTANT_33
	fsub s16, s16, s17
	str s16, [x29, #-24]
	ldr s16, [x29, #-24]
fmov s0, s16
bl _write_float
.data
_CONSTANT_35: .ascii "\n"
.align 2
.text
ldr x0, =_CONSTANT_35
bl _write_str
	ldr s16, [x29, #-24]
	.data
_CONSTANT_36:
	.float 2.000000
	.align 3
	.text
	ldr s17, _CONSTANT_36
	ldr s18, [x29, #-24]
	fmul s17, s17, s18
	fdiv s16, s16, s17
	str s16, [x29, #-24]
	ldr s16, [x29, #-24]
fmov s0, s16
bl _write_float
.data
_CONSTANT_38: .ascii "\n"
.align 2
.text
ldr x0, =_CONSTANT_38
bl _write_str
	.data
_CONSTANT_39:
	.word 0
	.align 3
	.text
	ldr w9, _CONSTANT_39
	mov w0, w9
	b _end_MAIN

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
	.word 116