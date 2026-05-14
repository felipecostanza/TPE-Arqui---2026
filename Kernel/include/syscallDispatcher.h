#ifndef _SYSCALLS_H_
#define _SYSCALLS_H_

#include <stdint.h> 
#include <stdlib.h>

typedef enum{
    STDOUT = 1,
    STDERR
} FDS;


void syscallDispatcher(uint64_t rax, ...);
void write(FDS fd, const char *buf, size_t count);

#endif