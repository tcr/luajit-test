# running

cd jit

`make run` will launch the JIT example

## test rig

Need an automated test rig to determine if assembled code is being properly generated from JIT.
1) test generation
2) test result

to start this, need a compiler and script that will generate assembly for a function for output by inspection.
(so do this)

./dump.js dumps the test() function in main
./run.js runs the code in main in qemu (then kills it, dumps output)

## notes

it compiles into an actions list, which is then parsed to generate branches i think

compile stage 
and
DASM_PUT stage (when code's being run)

/* Pass 1: Store actions and args, link branches/labels, estimate offsets. */
/* Feed encoder with actions. Calls are generated by pre-processor. */
DASM_FDEF void dasm_put(Dst_DECL, int start, ...);

/* Pass 2: Link sections, shrink branches/aligns, fix label offsets. */
/* Link sections and return the resulting size. */
DASM_FDEF int dasm_link(Dst_DECL, size_t *szp);

/* Pass 3: Encode sections. */
/* Encode sections into buffer. */
int dasm_encode(Dst_DECL, void *buffer)



so for example we got
0xdd00 - Branch LE
0xffff indicates an action.
0x5002 indicates:
	5 - DASM_REL_LG
	0x5002 & 2047 = // 0000 0111 1111 1111
	we then subtract 10 (starts chain for fwd rel)
	so 2 is -8


forward jump isn't working
first fix: not calling setupglobals

next, we look at the linker stage to see what's being output when we get the 0x5002 entry.

??? what is "bias"

we add it to our buffer (set it to 0) and our label pointer is set to the current position (entry 7).

i think this becomes a block chain, in case other values also point forward to the same label, they cascade. (clever!)

fixed the issue by changing around some off the offset code in the encoding stage.

next: have more testable code situations, dumping situations, to compare code.


create a function,
dump its assembly,
match it in code,
test its resulting output with a dumping function
and testing that it runs.