	.text
_start_main:
	str x30, [sp, #0]
	str x29, [sp, #-8]
	add x29, sp, #-8
	add sp, sp, #-16
	ldr x30, =_frameSize_main
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

_CONSTANT_0:
	.word 1
	.align 3
	.text
	ldr w9, _CONSTANT_0
_CONSTANT_1:
	.word 2
	.align 3
	.text
	ldr w10, _CONSTANT_1
	add w9, w9, w10
_CONSTANT_2:
	.word 3
	.align 3
	.text
	ldr w10, _CONSTANT_2
	mul w9, w9, w10
_CONSTANT_3:
	.word 4
	.align 3
	.text
	ldr w10, _CONSTANT_3
_CONSTANT_4:
	.word 5
	.align 3
	.text
	ldr w11, _CONSTANT_4
	sdiv w10, w10, w11
	sub w9, w9, w10
_CONSTANT_5:
	.word 1
	.align 3
	.text
	ldr w10, _CONSTANT_5
_CONSTANT_6:
	.word -1
	.align 3
	.text
	ldr w11, _CONSTANT_6
	mul w10, w10, w11
	add w9, w9, w10
	str w9, [x29, #-12]
	ldr w9, [x29, #-12]
mov w0, w9
bl _write_int
.data
_CONSTANT_8: .ascii "\\n"
.align 3
.text
ldr x0, =_CONSTANT_8
bl _write_str
_CONSTANT_9:
	.word 1
	.align 3
	.text
	ldr w10, _CONSTANT_9
	str w10, [x29, #-4]
_CONSTANT_11:
	.word 2
	.align 3
	.text
	ldr w10, _CONSTANT_11
	str w10, [x29, #-8]
_CONSTANT_13:
	.word 3
	.align 3
	.text
	ldr w10, _CONSTANT_13
	str w10, [x29, #-12]
	ldr w10, [x29, #-4]
	ldr w11, [x29, #-8]
	mul w10, w10, w11
	ldr w11, [x29, #-12]
_CONSTANT_15:
	.word 4
	.align 3
	.text
	ldr w12, _CONSTANT_15
	mul w11, w11, w12
	sub w10, w10, w11
_CONSTANT_16:
	.word 5
	.align 3
	.text
	ldr w11, _CONSTANT_16
	sub w10, w10, w11
	str w10, [x29, #-12]
	ldr w10, [x29, #-12]
mov w0, w10
bl _write_int
.data
_CONSTANT_18: .ascii "\\n"
.align 3
.text
ldr x0, =_CONSTANT_18
bl _write_str
_CONSTANT_19:
	.float 1.000000
	.align 3
	.text
	ldr s16, _CONSTANT_19
_CONSTANT_20:
	.float 2.000000
	.align 3
	.text
	ldr s17, _CONSTANT_20
	fadd s16, s16, s17
_CONSTANT_21:
	.float 3.000000
	.align 3
	.text
	ldr s17, _CONSTANT_21
	fmul s16, s16, s17
_CONSTANT_22:
	.float 4.000000
	.align 3
	.text
	ldr s17, _CONSTANT_22
_CONSTANT_23:
	.float 5.000000
	.align 3
	.text
	ldr s18, _CONSTANT_23
	fdiv s17, s17, s18
	fsub s16, s16, s17
_CONSTANT_24:
	.float 1.000000
	.align 3
	.text
	ldr s17, _CONSTANT_24
_CONSTANT_25:
	.float -1.000000
	.align 3
	.text
	ldr s18, _CONSTANT_25
	fmul s17, s17, s18
	fadd s16, s16, s17
	str s16, [x29, #-24]
	ldr s16, [x29, #-24]
fmov s0, s16
bl _write_float
.data
_CONSTANT_27: .ascii "\\n"
.align 3
.text
ldr x0, =_CONSTANT_27
bl _write_str
_CONSTANT_28:
	.float 1.000000
	.align 3
	.text
	ldr s17, _CONSTANT_28
	str s17, [x29, #-16]
_CONSTANT_30:
	.float 2.000000
	.align 3
	.text
	ldr s17, _CONSTANT_30
	str s17, [x29, #-20]
_CONSTANT_32:
	.float 3.000000
	.align 3
	.text
	ldr s17, _CONSTANT_32
	str s17, [x29, #-24]
	ldr s17, [x29, #-16]
	ldr s18, [x29, #-20]
	fmul s17, s17, s18
	ldr s18, [x29, #-24]
_CONSTANT_34:
	.float 4.000000
	.align 3
	.text
	ldr s19, _CONSTANT_34
	fmul s18, s18, s19
	fsub s17, s17, s18
_CONSTANT_35:
	.float 5.000000
	.align 3
	.text
	ldr s18, _CONSTANT_35
	fsub s17, s17, s18
	str s17, [x29, #-24]
	ldr s17, [x29, #-24]
fmov s0, s17
bl _write_float
.data
_CONSTANT_37: .ascii "\\n"
.align 3
.text
ldr x0, =_CONSTANT_37
bl _write_str
_CONSTANT_38:
	.word 1
	.align 3
	.text
	ldr w11, _CONSTANT_38
_CONSTANT_39:
	.word 2
	.align 3
	.text
	ldr w12, _CONSTANT_39
	str w11, [x29, #-12]
	ldr w11, [x29, #-12]
mov w0, w11
bl _write_int
.data
_CONSTANT_41: .ascii "\\n"
.align 3
.text
ldr x0, =_CONSTANT_41
bl _write_str
_CONSTANT_42:
	.word 2
	.align 3
	.text
	ldr w12, _CONSTANT_42
_CONSTANT_43:
	.word 2
	.align 3
	.text
	ldr w13, _CONSTANT_43
	str w12, [x29, #-12]
	ldr w12, [x29, #-12]
mov w0, w12
bl _write_int
.data
_CONSTANT_45: .ascii "\\n"
.align 3
.text
ldr x0, =_CONSTANT_45
bl _write_str
_CONSTANT_46:
	.word 1
	.align 3
	.text
	ldr w13, _CONSTANT_46
_CONSTANT_47:
	.word 2
	.align 3
	.text
	ldr w14, _CONSTANT_47
	str w13, [x29, #-12]
	ldr w13, [x29, #-12]
mov w0, w13
bl _write_int
.data
_CONSTANT_49: .ascii "\\n"
.align 3
.text
ldr x0, =_CONSTANT_49
bl _write_str
_CONSTANT_50:
	.word 2
	.align 3
	.text
	ldr w14, _CONSTANT_50
_CONSTANT_51:
	.word 2
	.align 3
	.text
	ldr w15, _CONSTANT_51
	str w14, [x29, #-12]
	ldr w14, [x29, #-12]
mov w0, w14
bl _write_int
.data
_CONSTANT_53: .ascii "\\n"
.align 3
.text
ldr x0, =_CONSTANT_53
bl _write_str
_CONSTANT_54:
	.word 1
	.align 3
	.text
	ldr w15, _CONSTANT_54
_CONSTANT_55:
	.word 2
	.align 3
	.text
	ldr w-1, _CONSTANT_55
	str w15, [x29, #-12]
	ldr w15, [x29, #-12]
mov w0, w15
bl _write_int
.data
_CONSTANT_57: .ascii "\\n"
.align 3
.text
ldr x0, =_CONSTANT_57
bl _write_str
_CONSTANT_58:
	.word 1
	.align 3
	.text
	ldr w-1, _CONSTANT_58
_CONSTANT_59:
	.word 2
	.align 3
	.text
	ldr w-1, _CONSTANT_59
	str w-1, [x29, #-12]
	ldr w-1, [x29, #-12]
mov w0, w-1
bl _write_int
.data
_CONSTANT_61: .ascii "\\n"
.align 3
.text
ldr x0, =_CONSTANT_61
bl _write_str
_CONSTANT_62:
	.float 1.000000
	.align 3
	.text
	ldr s18, _CONSTANT_62
_CONSTANT_63:
	.float 2.000000
	.align 3
	.text
	ldr s19, _CONSTANT_63
	str s18, [x29, #-12]
	ldr w-1, [x29, #-12]
mov w0, w-1
bl _write_int
.data
_CONSTANT_65: .ascii "\\n"
.align 3
.text
ldr x0, =_CONSTANT_65
bl _write_str
_CONSTANT_66:
	.float 1.000000
	.align 3
	.text
	ldr s18, _CONSTANT_66
_CONSTANT_67:
	.float 2.000000
	.align 3
	.text
	ldr s19, _CONSTANT_67
	str s18, [x29, #-12]
	ldr w-1, [x29, #-12]
mov w0, w-1
bl _write_int
.data
_CONSTANT_69: .ascii "\\n"
.align 3
.text
ldr x0, =_CONSTANT_69
bl _write_str
_CONSTANT_70:
	.float 1.000000
	.align 3
	.text
	ldr s18, _CONSTANT_70
_CONSTANT_71:
	.float 2.000000
	.align 3
	.text
	ldr s19, _CONSTANT_71
	str s18, [x29, #-12]
	ldr w-1, [x29, #-12]
mov w0, w-1
bl _write_int
.data
_CONSTANT_73: .ascii "\\n"
.align 3
.text
ldr x0, =_CONSTANT_73
bl _write_str
_CONSTANT_74:
	.word 0
	.align 3
	.text
	ldr w-1, _CONSTANT_74
	mov w0, w-1
	b _end_main

_end_main:
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
_frameSize_main:
	.word 116
