#include <sys/stat.h>

enum {
  UART_FR_RXFE = 0x10,
  UART_FR_TXFF = 0x20,
  UART0_ADDR = 0x4000C000,

};

#define UART_DR(baseaddr) (*(unsigned int *)(baseaddr))
#define UART_FR(baseaddr) (*(((unsigned int *)(baseaddr))+6))

int _close(int file) {
  return 0;
}

void _exit(int code) {
  while (1) { }
}

void _kill(int code) {
  while (1) { }
}

int _getpid() {
  return 0;
}

int _fstat(int file, struct stat *st) {
  st->st_mode = S_IFCHR;
  return 0;

}

int _isatty(int file) {
  return 1;

}

int _lseek(int file, int ptr, int dir) {
  return 0;

}

int _open(const char *name, int flags, int mode) {
return -1;

}

int _read(int file, char *ptr, int len) {
  int todo;
  if(len == 0)
    return 0;
  while(UART_FR(UART0_ADDR) & UART_FR_RXFE);
  *ptr++ = UART_DR(UART0_ADDR);
  for(todo = 1; todo < len; todo++) {
    if(UART_FR(UART0_ADDR) & UART_FR_RXFE) { break;  }
    *ptr++ = UART_DR(UART0_ADDR);

}
  return todo;

}


int _write(int file, char *ptr, int len) {
  int todo;
  for (todo = 0; todo < len; todo++) {
    UART_DR(UART0_ADDR) = *ptr++;

}
  return len;

}

// Copyright 2014 Technical Machine, Inc. See the COPYRIGHT
// file at the top-level directory of this distribution.
//
// Licensed under the Apache License, Version 2.0 <LICENSE-APACHE or
// http://www.apache.org/licenses/LICENSE-2.0> or the MIT license
// <LICENSE-MIT or http://opensource.org/licenses/MIT>, at your
// option. This file may not be copied, modified, or distributed
// except according to those terms.


extern unsigned char  _heap;  // Start of heap defined in linker
extern unsigned char  _eheap; // End of heap

static unsigned char* heap = 0;

unsigned char* _sbrk ( int size ) {
    if (heap == 0) {
        heap = (unsigned char*)&_heap;
    }

    unsigned char* r = heap;

    // Align to 8-byte boundary
    unsigned char* next = (unsigned char*)(((unsigned int)(heap + size) + 7) & ~7);

    if (next > &_eheap) {
        return 0; // Out of memory
    } else {
        heap = next;
        return r;
    }
}
