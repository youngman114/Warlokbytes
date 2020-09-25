# Instructions

| Instruction | Hexadecimal Opcode | Stack State        | Brief                                                                                                 | Implemented? |
|-------------|--------------------|--------------------|-------------------------------------------------------------------------------------------------------|--------------|
| PASS        | 0x00               |                    | Do nothing                                                                                            |       T      |
| PRINT       | 0x01               | byte...0x00 ->     | Print null terminated byte set from stack                                                             |       T      |
| BR          | 0x0A               | byte ->            | Branch to arg1:LEB128(u32) if TOS != 0                                                                |       F      |
| GOTO        | 0x0B               |                    | Move program pointer to arg1:LEB128(u32)                                                              |       F      |
| PUSHB       | 0x10               | -> byte            | Push one byte                                                                                         |       T      |
| PUSHN       | 0x11               | -> byte...0x00     | Push null terminated byte set                                                                         |       T      |
| ADD         | 0x20               | byte, byte -> byte | Add two bytes and push result                                                                         |       T      |
| SUB         | 0x21               | byte, byte -> byte | Subtract two bytes and push result                                                                    |       T      |
| MUL         | 0x22               | byte, byte -> byte | Multiply two bytes and push result                                                                    |       T      |
| DIV         | 0x23               | byte, byte -> byte | Divide two bytes and push result                                                                      |       T      |
| FRAME       | 0x6A               |                    | Push new frame onto the frame stack with locals size arg1:LEB128(u32) and stack size arg2:LEB128(u32) |       F      |
| DEFRAME     | 0x6B               |                    | Pop current frame from frame stack                                                                    |       F      |
| ADDR        | 0x6C               |                    | Remember call pointer to the current position                                                         |       F      |
| RET         | 0x6D               |                    | Pop call pointer and areturn to it                                                                    |       F      | 
| EQB         | 0x70               | byte, byte -> byte | Compare two bytes, push 1 if equal and 0 if not                                                       |       F      |
| NEQB        | 0x71               | byte, byte -> byte | Compare two bytes, push 0 if equal and 1 if not                                                       |       F      |
| NOTB        | 0x71               | byte -> byte       | Inverse TOS byte                                                                                      |       F      | 
| LLOADB      | 0xA0               | -> byte            | Push local byte from addr arg1:LEB128(u32)                                                            |       F      |
| LSTOREB     | 0xA1               | byte ->            | Store popped TOS at local arg1:LEB128(u32)                                                            |       F      |
| HALT        | 0xFF               | byte ->            | Exit program with TOS as exit code                                                                    |       T      |

*TOS - Top Of Stack
*argN:u32 - binary op argument with size of 32 bits
*argN:LEB128(u32) - binary op argument encoded with LEB128