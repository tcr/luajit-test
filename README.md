# luajit thumb2 porting work

`make thumb` will compile libluajit.a for thumb
`make test` will run dynasm tests

## test

Tests dynasm code generation.

./dump.js dumps the test() function programmed in main.c for copying

`make test` runs the code

## tools

`./disas.js XXXX XXXX` disassembles a one or two-word command.

## notes

### Dynasm

Dynasm compiles input into an "actions" list. This is a list of assembly instructions interspliced with commands for dynamic instructions and branches that get inserted during Pass 1-3.

```
/* Pass 0: Compile into actions list. */
$ dynasm instr.dasc

/* Pass 1: Store actions and args, link branches/labels, estimate offsets. */
/* Feed encoder with actions. Calls are generated by pre-processor. */
DASM_FDEF void dasm_put(Dst_DECL, int start, ...);

/* Pass 2: Link sections, shrink branches/aligns, fix label offsets. */
/* Link sections and return the resulting size. */
DASM_FDEF int dasm_link(Dst_DECL, size_t *szp);

/* Pass 3: Encode sections. */
/* Encode sections into buffer. */
int dasm_encode(Dst_DECL, void *buffer)
```

So for example,

```
0xdd00 - Branch LE
0xffff indicates an action.
0x5002 indicates:
	5 - DASM_REL_LG
	0x5002 & 2047 = // 0000 0111 1111 1111
	we then subtract 10 (starts chain for fwd rel)
	so 2 is -8
```

### other

* Label pointers are a linked list. In case other values also point forward to the same label, they cascade. (clever!)