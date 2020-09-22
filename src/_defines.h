typedef unsigned char byte;

typedef unsigned int u32;
typedef unsigned long u64;
typedef signed int i32;
typedef signed long i64;
typedef float f32;
typedef float f64;
typedef u32 ptr;

/* BASIC INSTRUCTIONS*/
// Do nothing
#define PASS 0x00
// Print NULL terminated string from stack
#define PRINT 0x01

/* STACK INSTRUCTIONS */
// But next byte onto the stack
#define PUSHB 0x10
// Push NULL terminated string onto the stack
#define PUSHN 0x11

/* ARITHMETIC INSTRUCTIONS */
// Add two numbers at stack and push result back
#define ADD 0x20
// Subtract two numbers at stack and push result back
#define SUB 0x21

/* MISC INSTRUCTIONS */
// End the program execution with TOS exit code
#define HALT 0xFF
