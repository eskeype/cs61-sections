#ifndef WEENSYOS_PROCESS_H
#define WEENSYOS_PROCESS_H
#include "lib.h"
#include "x86-64.h"
#if WEENSYOS_KERNEL
#error "process.h should not be used by kernel code."
#endif

// process.h
//
//    Support code for WeensyOS processes.


// SYSTEM CALLS

// sys_yield
//    Yield control of the CPU to the kernel. The kernel will pick another
//    process to run, if possible.
static inline void sys_yield(void) {
    asm volatile ("int %0" : /* no result */
                  : "i" (INT_SYS_YIELD)
                  : "cc", "memory");
}

// sys_panic
//    Report an error and stop the current process.
static inline void __attribute__((noreturn)) sys_panic(const char* message) {
    asm volatile ("int %0" : /* no result */
                  : "i" (INT_SYS_PANIC), "D" (message)
                  : "cc", "memory");
 loop: goto loop;
}

// sys_write
//    Write a string to the console.
static inline void sys_write(const char* message, size_t sz) {
    asm volatile ("int %0" : /* no result */
                  : "i" (INT_SYS_WRITE), "D" (message), "S" (sz)
                  : "cc", "memory");
}


// OTHER HELPER FUNCTIONS

// app_printf(format, ...)
//    Calls console_printf() (see lib.h). The cursor position is read from
//    `cursorpos`, a shared variable defined by the kernel, and written back
//    into that variable. The initial color is based on the current process ID.
void app_printf(int colorid, const char* format, ...);

#endif
