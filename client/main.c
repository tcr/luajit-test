/*
 * test.c
 * Example of a C program that interfaces with Lua.
 * Based on Lua 5.0 code by Pedro Martelletto in November, 2003.
 * Updated to Lua 5.1. David Manura, January 2007.
 */

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdlib.h>
#include <stdio.h>


int lj_err_unwind_arm(int state, void *ucb, void *ctx)
{
    return -1;
}

#include <assert.h>
#include <stdint.h>


int test (const char *code, double returnvalue)
{
    printf("# start\n");

    int status, result, i;
    double sum;
    lua_State *L;

    printf("# create state\n");

    /*
     * All Lua contexts are held in this structure. We work with it almost
     * all the time.
     */
    L = luaL_newstate();

    printf("# open libs\n");

    luaL_openlibs(L); /* Load Lua libraries */

    printf("# run script\n");

    luaL_loadstring(L, code);
    /* Ask Lua to run our little script */
    result = lua_pcall(L, 0, 1, 0);
    if (result) {
        printf("Failed to run script: %s\n", lua_tostring(L, -1));
        return 1;
    }

    printf("# parse result\n");

    /* Get the returned value at the top of the stack (index -1) */
    sum = lua_tonumber(L, -1);

    printf("# returned: %.0f\n", sum);

    lua_pop(L, 1);  /* Take the returned value out of the stack */
    lua_close(L);   /* Cya, Lua */

    if (sum == returnvalue) {
        printf("ok\n");
        return 0;
    } else {
        printf("not ok\n");
        return 1;
    }
}


int main (void)
{
    // printf("1..4\n");
    // test("return 2 + 2", 4);
    // test("return (56 * 24)/2", 1344/2);
    // test("local a = 5; return a", 5);
    // test("local a = 5 * 5; return a", 5*5);
    // test("local function a () return 5; end; return a()", 5);
    // test("local function a (b) return b; end; return a(10)", 10);
    // test("local function a (b, c) return b * c; end; return a(10, 5)", 10 * 5);
    // test("local function a (b, c)\n\treturn b * c\nend\n\nreturn a(10, 5)", 10 * 5);
    // test("local a = {5}; return a[1]", 5);
    // test("local a = {5, 10, 15}; return a[1] * a[2] * a[3]", 5*10*15);

    test("local sqrt = math.sqrt; return sqrt(4)", 2);
    
    printf("\n# done\n");
}