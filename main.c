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
static const uint16_t actions[6] = {
0x2805,
0xbfd4,
0x2000,
0x2001,
0x4770,
0xbf00
};

#line 13 "main.dasc"

// This define affects "|" DynASM lines.  "Dst" must
// resolve to a dasm_State** that points to a dasm_State*.
#define Dst &state

int test (int n)
{
  // int i = 2;
  //  int f1 = 0;
  //  int f2 = 1;
  //  int fn = 0;
  //  for ( i = 2; i < n; i++ )
  //  {
  //     fn = f1 + f2;
  //     f1 = f2;
  //     f2 = fn;
  //  }
  //  return fn;
  if (n > 5) {
    return 1;
  }
  return 0;
} 
 
int main ()
{
  printf("Testing...\n");

  int num = 0xFF;

  printf(" --> test value %d\n", test(10));

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
//| cmp  r0, #5
//| ite le
//| mov r0, #0
//| mov r0, #1
//| bx  lr
dasm_put(Dst, 0);
#line 62 "main.dasc"

/*
cmp r0, #5
     95e: bfd4        ite le
     960: 2000        movle r0, #0
     962: 2001        movgt r0, #1
     964: 4770        bx  lr
     966: bf00        nop
*/

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
  int (*fptr)(int) = (code + 1);
  int ret = fptr(10);
  // assert(ret == 0x1);
  printf("4 %d\n", ret);

  printf("COOL\n");

  // Free the machine code.
  // free_jitcode(fptr);

  return 0;
}
