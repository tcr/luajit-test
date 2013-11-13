// Most basic DynASM JIT; generates a trivial function that
// returns a given value, and executes it.

// DynASM directives.
|.arch arm
|.actionlist actions

// Includes
#include <stdio.h>
#include <dasm_proto.h>
#include <dasm_arm.h>

// This define affects "|" DynASM lines.  "Dst" must
// resolve to a dasm_State** that points to a dasm_State*.
#define Dst &state
 
int main ()
{
  printf("Testing...\n");

  int num = 0xFF;

  dasm_State *state;

  dasm_init(state, 1);
  dasm_setup(state, actions);

  // Generate the code.  Each line appends to a buffer in
  // "state", but the code in this buffer is not fully linked
  // yet because labels can be referenced before they are
  // defined.
  //
  // The run-time value of C variable "num" is substituted
  // into the immediate value of the instruction.
  |  and r0, r1
  |  bx  lr

  // Link the code and write it to executable memory.
  size_t size;
  int dasm_status = dasm_link(state, &size);
  assert(dasm_status == DASM_S_OK);

  void *code = malloc(size);
  dasm_encode(state, code);
  dasm_free(state);

  // Call the JIT-ted function.
  int (*fptr)() = code;
  int ret = fptr();
  assert(ret == );

  // Free the machine code.
  free_jitcode(fptr);

  return ret;
}
