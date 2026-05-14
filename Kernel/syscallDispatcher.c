#include <stdint.h>
#include <stdarg.h>
#include <syscallDispatcher.h>
#include <naiveConsole.h>

void write(FDS fd, const char * buf, size_t len);


void syscallDispatcher(uint64_t rax, ...){
    
    va_list args;
    va_start(args, rax);

    switch(rax){
        case 1: 
        FDS fd = va_arg(args, FDS);
        const char* buf = va_arg(args, const char*);
        size_t count = va_arg(args, size_t);
        write(fd, buf, count);
        break;
    }

}

void write(FDS fd, const char * buf, size_t len){

    if(fd == STDOUT){
        ncUpdateColor(0x0F);
    }
    else if(fd == STDERR){
        ncUpdateColor(0x04);
    }

    ncPrint(buf);

}