/*
** This file has been pre-processed with DynASM.
** http://luajit.org/dynasm.html
** DynASM version 1.3.0, DynASM thumb version 1.3.0
** DO NOT EDIT! The original file is in "test/main.dasc".
*/

#line 1 "test/main.dasc"
#include <stdint.h>

// DynASM directives.
//|.arch thumb
#if DASM_VERSION != 10300
#error "Version mismatch between DynASM and included encoding engine"
#endif
#line 5 "test/main.dasc"
//|.actionlist actions
static const uint16_t actions[72] = {
0x2805,
0xbfd4,
0x2000,
0x2001,
0x4770,
0xffff,
0x0000,
0xfb01,
0xf000,
0x4770,
0xffff,
0x0000,
0xf103,
0x0201,
0xeb03,
0x0204,
0xf113,
0x0201,
0xeb13,
0x0204,
0xfb01,
0xf000,
0xfb03,
0xf202,
0x4614,
0x1e88,
0xf1a0,
0x0008,
0xeb02,
0x0103,
0xffff,
0xb000,
0xf5a2,
0x3000,
0xf5ab,
0x3600,
0xffff,
0x0000,
0x685b,
0xf8d3,
0x3005,
0xf854,
0x3c04,
0xeba0,
0x0001,
0xffff,
0xb000,
0xeba0,
0x0001,
0xffff,
0xb000,
0xeba0,
0x0001,
0xffff,
0xb000,
0xffff,
0x0000,
0x6800,
0xffff,
0x915a,
0xffff,
0x0000,
0xf100,
0x0000,
0xffff,
0xa000,
0xf100,
0x0000,
0xffff,
0xa000,
0xffff,
0x0000
};

#line 6 "test/main.dasc"

#include "test.h"




int cmp (int n)
{
	if (n > 5) {
		return 1;
	}
	return 0;
}

void cmp_test (int (*fn)(int))
{
	assert(fn(1) == 0);
	assert(fn(5) == 0);
	assert(fn(10) == 1);
}

TEST_JIT(cmp, int (*)(int),
{
	// The run-time value of C variable "num" is substituted
  	// into the immediate value of the instruction.
  	//|.type num, int, r0
#define Dt1(_V) (int)(ptrdiff_t)&(((int *)0)_V)
#line 32 "test/main.dasc"
	//| cmp num, #5
	//| ite le
	//| movle r0, #0
	//| movgt r0, #1
	//| bx  lr
	//| nop
	dasm_put(Dst, 0);
#line 38 "test/main.dasc"
})



int mul (int a, int b)
{
	__asm__ (
	"mul.w r0, r1, r0\n\t"
	);
	// return a * b;
}

void mul_test (int (*fn)(int, int))
{
	assert(fn(2, 3) == 6);
	assert(fn(4, 12) == 48);
}

TEST_JIT(mul, int (*)(int, int),
{
	//| mul.w r0, r1, r0
	//| bx    lr
	//| nop
	dasm_put(Dst, 7);
#line 61 "test/main.dasc"
})







COMPARE_JIT(arith,
__asm__ (
	"add.w r2, r3, #1\n\t"
	"add.w r2, r3, r4\n\t"
	"adds.w r2, r3, #1\n\t"
	"adds.w r2, r3, r4\n\t"
	"mul.w r0, r1, r0\n\t"
	"mul.w r2, r3, r2\n\t"
	"mov r4, r2\n\t"
	"subs r0, r1, #2\n\t"
	"sub r0, r0, #8\n\t"
	"add r1, r2, r3, lsl #2\n\t"
	"sub r0, r2, #0x20000\n\t"
	"sub r6, r11, #0x20000\n\t"
), {
	//| add.w r2, r3, #1
	//| add.w r2, r3, r4
	//| adds.w r2, r3, #1
	//| adds.w r2, r3, r4
	//| mul.w r0, r1, r0
	//| mul.w r2, r3, r2
	//| mov r4, r2
	//| subs r0, r1, #2
	//| sub r0, r0, #8
	//| add r1, r2, r3, lsl #2
	//| sub r0, r2, #0x20000
	//| sub r6, r11, #0x20000
	dasm_put(Dst, 12, 2);
#line 96 "test/main.dasc"
})

int REGS_LSL = 24;


COMPARE_JIT(regs,
__asm__ (
	"ldr r3, [r3, #4]\n\t"
	"ldr r3, [r3, #5]\n\t"
	"ldr r3, [r4, #-4]\n\t"
	"sub r0, r0, r1, lsl #5\n\t"
	"sub r0, r0, r1, lsl #24\n\t"
	"sub r0, r0, r1, lsl #24\n\t"
), {
	//| ldr r3, [r3, #4]
	//| ldr r3, [r3, #5]
	//| ldr r3, [r4, #-4]
	//| sub r0, r0, r1, lsl #5
	//| sub r0, r0, r1, lsl #24
	//| sub r0, r0, r1, lsl #REGS_LSL
	dasm_put(Dst, 38, 5, 24, REGS_LSL);
#line 116 "test/main.dasc"
})



typedef struct {
	uint8_t number;
} simple_t;

void struct_jit()
{
	dasm_State *state;
	simple_t a = { 0 };
	simple_t* ptr = &a;
	ptr->number = 5;

    //|.type a,		simple_t,	r0
#define Dt2(_V) (int)(ptrdiff_t)&(((simple_t *)0)_V)
#line 132 "test/main.dasc"
	//| ldr r0, a->number
	dasm_put(Dst, 57, Dt2(->number));
#line 133 "test/main.dasc"
}



int SOMETHING = 1;
int SOMETHING2 = 0x2C002C;

COMPARE_JIT(immtest,
__asm__ (
	"add.w r0, r0, #1\n\t"
	"add.w r0, r0, #0x2C002C\n\t"
), {
	//| add.w r0, r0, #SOMETHING
	//| add.w r0, r0, #SOMETHING2
	dasm_put(Dst, 62, SOMETHING, SOMETHING2);
#line 147 "test/main.dasc"
})



void sub_neg ()
{
__asm__ (
	"add r6, #-255"
);
}




int main ()
{
	printf("# START.\n\n");

	printf("1..5\n");
	cmp_jit();
	mul_jit();
	arith_jit();
	struct_jit();
	regs_jit();
	immtest_jit();

	printf("# FINISHED.\n");

	return 0;
}
