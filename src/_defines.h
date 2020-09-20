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

/* STACK INSTRUCTIONS */
// But next byte onto the stack
#define PUSH 0x10

/* ARITHMETIC INSTRUCTIONS */
// Add two numbers at stack and push result back
#define ADD 0x20
// Subtract two numbers at stack and push result back
#define SUB 0x21

/* MISC INSTRUCTIONS */
// End the program execution with TOS exit code
#define HALT 0xFF
