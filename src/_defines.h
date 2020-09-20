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

/* ARITHMETIC INSTRUCTIONS */
// But next byte onto the stack
#define PUSH 0x10

/* MISC INSTRUCTIONS */
// End the program execution with TOS exit code
#define HALT 0xFF
