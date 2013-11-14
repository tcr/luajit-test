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
#include <dasm_proto.h>
#include <dasm_arm.h>

// Most basic DynASM JIT; generates a trivial function that
// returns a given value, and executes it.

// DynASM directives.
//|.arch arm
//|.actionlist actions
static const uint16_t actions[3] = {
0x4008,
0x4770,
0x0000
};

#line 13 "main.dasc"

// This define affects "|" DynASM lines.  "Dst" must
// resolve to a dasm_State** that points to a dasm_State*.
#define Dst &state

int test (int a, int b)
{
  return a & b;
}
 
int main ()
{
  printf("Testing...\n");

  int num = 0xFF;

  printf(" --> test value %d\n", test(0xff, 1));

  dasm_State *state;

  dasm_init(&state, 1);
  dasm_setup(&state, actions);

  // Generate the code.  Each line appends to a buffer in
  // "state", but the code in this buffer is not fully linked
  // yet because labels can be referenced before they are
  // defined.
  //
  // The run-time value of C variable "num" is substituted
  // into the immediate value of the instruction.
  //|  ands r0, r1
  //|  bx  r14
  dasm_put(Dst, 0);
#line 45 "main.dasc"

  // Link the code and write it to executable memory.
  size_t size;
  int dasm_status = dasm_link(&state, &size);
  printf("1\n");
  assert(dasm_status == DASM_S_OK);

  printf("2\n");
  void *code = malloc(size);
  dasm_encode(&state, code);
  dasm_free(&state);
  printf("3 %p\n", code);

  // Call the JIT-ted function.
  int (*fptr)(int, int) = (code + 1);
  int ret = fptr(0xff, 1);
  // assert(ret == 0x1);
  printf("4 %d\n", ret);

  printf("COOL\n");

  // Free the machine code.
  // free_jitcode(fptr);

  return 0;
}