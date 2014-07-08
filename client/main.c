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
#include "lj_dispatch.h"

int
main(void)
{
    printf("# start\n");

    int status, result, i;
    double sum;
    lua_State *L;

    printf("1\n");

    /*
     * All Lua contexts are held in this structure. We work with it almost
     * all the time.
     */
    L = luaL_newstate();

    printf("2\n");

    luaL_openlibs(L); /* Load Lua libraries */

    printf("3\n");

    luaL_loadstring(L, "return 1 + 1");
    /* Ask Lua to run our little script */
    result = lua_pcall(L, 0, 1, 0);
    if (result) {
        fprintf(stderr, "Failed to run script: %s\n", lua_tostring(L, -1));
        exit(1);
    }

    printf("4\n");

    /* Get the returned value at the top of the stack (index -1) */
    sum = lua_tonumber(L, -1);

    printf("Script returned: %.0f\n", sum);

    lua_pop(L, 1);  /* Take the returned value out of the stack */
    lua_close(L);   /* Cya, Lua */

    return 0;
}
