/*
** This file has been pre-processed with DynASM.
** http://luajit.org/dynasm.html
** DynASM version 1.3.0, DynASM arm version 1.3.0
** DO NOT EDIT! The original file is in "main.dasc".
*/

#if DASM_VERSION != 10300
#error "Version mismatch between DynASM and included encoding engine"
#endif

#line 1 "main.dasc"
// Includes
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <dasm_proto.h>
#include <dasm_arm.h>

// Most basic DynASM JIT; generates a trivial function that
// returns a given value, and executes it.

// DynASM directives.
//|.arch arm
//|.actionlist actions
static const uint16_t actions[40] = {
0x2805,
0xbfd4,
0x2000,
0x2001,
0x4770,
0xbf00,
0xffff,
0x0000,
0xb410,
0x2802,
0xbfd8,
0x2100,
0xdd00,
0xffff,
0x5002,
0xf04f,
0x0201,
0xf04f,
0x0400,
0xf04f,
0x0302,
0xffff,
0x600b,
0x18a1,
0xf103,
0x0301,
0x4614,
0x460a,
0x4283,
0xd100,
0xffff,
0x500b,
0xffff,
0x600c,
0x4608,
0xbc10,
0x4770,
0xbf00,
0xffff,
0x0000
};

#line 14 "main.dasc"

// This define affects "|" DynASM lines.  "Dst" must
// resolve to a dasm_State** that points to a dasm_State*.
#define Dst &state


static void jit_init (dasm_State** state)
{
	printf(":: JIT_INIT.\n");
	dasm_init(state, 1);
	dasm_setupglobal(state, (void **)malloc(32*sizeof(void *)), 32);
	dasm_setup(state, actions);
	assert(state != 0);
}

static void* jit_build (dasm_State** state, size_t* size)
{
	printf(":: JIT_LINK.\n");
	// Link the code and write it to executable memory.
	int dasm_status = dasm_link(state, size);
	assert(*size != 0);
	assert(dasm_status == DASM_S_OK);
	void *code = malloc(*size);

	printf(":: JIT_ENCODE.\n");
	dasm_encode(state, code);
	dasm_free(state);
	return code;
}

static void jit_dump (void* code, size_t size)
{
	printf(":: JIT_DUMP\n");
	// Dump generated code.
	int max = size - 1;
	while (max >= 0 && ((uint16_t *) code)[max] == 0) {
		max--;
	}
	for (int i = 0; i <= max; i++) {
		printf(";;; %04x\n", ((uint16_t *) code)[i]);
	}
}

static void jit_free (void *code)
{
	printf(":: JIT_DONE.\n\n\n\n");
	free(code);
}







int cmp (int n)
{
	if (n > 5) {
		return 1;
	}
	return 0;
}

void cmp_test (char* tag, void* call)
{
	int (*fn)(int) = call;
	printf(":: CMP TEST: %s.\n", tag);
	assert(fn(1) == 0);
	assert(fn(5) == 0);
	assert(fn(10) == 1);
}

void cmp_jit (void)
{
	dasm_State *state;
	size_t size = 0;
	void* code;

	cmp_test("CONTROL", cmp);
	jit_init(&state);
	
	//| cmp  r0, #5
	//| ite le
	//| mov r0, #0
	//| mov r0, #1
	//| bx  lr
	//| nop
	dasm_put(Dst, 0);
#line 101 "main.dasc"

	code = jit_build(&state, &size);
	jit_dump(code, size);
	cmp_test("JITTED", code+1);
	jit_free(code);
}



int fib (int n)
{
	int i = 2;
	int f1 = 0;
	int f2 = 1;
	int fn = 0;
	for (i = 2; i < n; i++) {
		fn = f1 + f2;
		f1 = f2;
		f2 = fn;
	}
	return fn;
}

void fib_test (char* tag, void* call)
{
	int (*fn)(int) = call;
	printf(":: FIB TEST: %s.\n", tag);
	assert(fn(10) == 34);
	assert(fn(4) == 2);
	assert(fn(0) == 0);
	assert(fn(3) == 1);
}

void fib_jit (void)
{
	dasm_State *state;
	size_t size = 0;
	void* code;

	fib_test("CONTROL", fib);
	jit_init(&state);

	//| push {r4}
	//| cmp r0, #2
	//| it  le
	//| mov r1, #0
	//| ble >2
	//| mov.w r2, #1
	//| mov.w r4, #0
	//| mov.w r3, #2
	//|1:
	//| adds   r1, r4, r2
	//| add.w  r3, r3, #1
	//| mov r4, r2
	//| mov r2, r1
	//| cmp r3, r0
	//| bne <1
	//|2:
	//| mov r0, r1
	//| pop {r4}
	//| bx  lr
	//| nop
	dasm_put(Dst, 8);
#line 163 "main.dasc"

	code = jit_build(&state, &size);
	jit_dump(code, size);
	fib_test("JITTED", code+1);
	jit_free(code);
}







int main ()
{
	printf(":: START.\n");

  // The run-time value of C variable "num" is substituted
  // into the immediate value of the instruction.
// | cmp  r0, #5
// | ite le
// | mov r0, #0
// | mov r0, #1
// | bx  lr

	fib_jit();
	cmp_jit();

	printf(":: FINISHED.\n");

	return 0;
}
