#include <stdio.h>
#include <inttypes.h>

int inc(int a) {
    asm volatile ("incl %0" : "+r" (a));
    return a;
}

int add(int a, int b) {
    asm volatile ("addl %1, %0" : "+r" (a) : "r" (b));
    return a;
}

ssize_t mywrite(int fd, const void* buf, size_t sz) {
    register uintptr_t arg0 asm("rdi") = fd;
    register uintptr_t arg1 asm("rsi") = (uintptr_t) buf;
    register uintptr_t arg2 asm("rdx") = sz;
    uintptr_t result;
    __asm__ volatile("syscall"
                     : "=a" (result)
                     : "0" (1), "r" (arg0), "r" (arg1), "r" (arg2)
                     : "memory", "cc", "rcx", "r11");
    return result;
}
