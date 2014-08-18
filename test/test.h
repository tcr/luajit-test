#include <lm3s_cmsis.h>

// Includes
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <dasm_proto.h>
#include <dasm_thumb.h>

// "Dst" must resolve to a dasm_State** that points to a dasm_State*.
#define Dst &state

static void jit_init (dasm_State** state)
{
    printf("# JIT_INIT.\n");
    dasm_init(state, 1);
    dasm_setupglobal(state, (void **)malloc(32*sizeof(void *)), 32);
    dasm_setup(state, actions);
    assert(state != 0);
}

static void* jit_build (dasm_State** state, size_t* size)
{
    printf("# JIT_LINK.\n");
    // Link the code and write it to executable memory.
    int dasm_status = dasm_link(state, size);
    assert(*size != 0);
    assert(dasm_status == DASM_S_OK);
    void *code = calloc(1, *size);

    printf("# JIT_ENCODE.\n");
    dasm_encode(state, code);
    dasm_free(state);
    return code;
}

static int jit_compare (void* fn, void* code, size_t size)
{
    printf("# JIT_COMPARE (%d words):", size/2);
    for (int i = 0; i < size/2; i++) {
        if (((uint16_t*) code)[i] != ((uint16_t*) fn)[i]) {
            printf(" failed! word %d/%d: %04x isn't %04x\n", i+1, (size/2), ((uint16_t*) code)[i], ((uint16_t*) fn)[i]);
            printf("not ok\n");
            return 1;
        }
    }
    printf(" succeeded.\n");
    printf("ok\n");
    return 0;
}

static void jit_dump_cmp (void* code, void* code2, size_t size)
{
    printf("# JIT_DUMP\n");
    // Dump generated code.
    for (int i = 0; i < size/2; i++) {
        uint16_t a = ((uint16_t *) code)[i];
        uint16_t b = ((uint16_t *) code2)[i];
        if (a == b) {
            printf("#  %04x - %04x\n", a, b);
        } else {
            printf("#  %04x ! %04x\n", a, b);
        }
    }
}

static void jit_dump (void* code, size_t size)
{
    printf("# JIT_DUMP\n");
    // Dump generated code.
    for (int i = 0; i < size/2; i++) {
        printf("# %04x\n", ((uint16_t *) code)[i]);
    }
}

static void jit_free (void *code)
{
    printf("# JIT_DONE.\n\n");
    free(code);
}

#define TEST_JIT(A, T, ASM) \
void A ## _jit (void) \
{ \
    dasm_State *state; \
    size_t size = 0; \
    void* code; \
\
    printf("# TEST [%s]\n", #A); \
    A ## _test(A); \
    jit_init(&state); \
\
     ASM; \
\
    code = jit_build(&state, &size); \
    volatile uint32_t ptr = (uint32_t) A; \
    if (jit_compare((void*) (ptr - 1), code, size) != 0) \
        jit_dump_cmp(code, (void *) (ptr - 1), size); \
    printf("# JIT TEST.\n"); \
    A ## _test(((T) (code+1))); \
    jit_free(code); \
}

#define COMPARE_JIT(A, REALASM, ASM) \
void A (void) \
{ \
    REALASM; \
} \
void A ## _jit (void) \
{ \
    dasm_State *state; \
    size_t size = 0; \
    void* code; \
\
    printf("# COMPARE [%s]\n", #A); \
    jit_init(&state); \
\
     ASM; \
\
    code = jit_build(&state, &size); \
    volatile uint32_t ptr = (uint32_t) A; \
    if (jit_compare((void*) (ptr - 1), code, size) != 0) \
        jit_dump_cmp(code, (void *) (ptr - 1), size); \
    jit_free(code); \
}

void run_test(void);

int main ()
{
    SystemInit();

    run_test();

    printf("# terminate.\n");
    return 0;
}
