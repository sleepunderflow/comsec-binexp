// void 


__attribute__((sysv_abi, noreturn, naked)) 
void exit (int result) {
  __asm__(
    "movq $60, %%rax; " // sys_exit
    "syscall; "
    :                   // no output parameters  
    : "r" (result)      // result used via register
    : "rax"             // rax is modified inside
  );
}


// Print the string to stdout; 
// input: rdi - string
// output: rax - length printed
__attribute__((sysv_abi, naked))
int puts(char* string) {
  __asm__(
    "push %%rbp; "             // function preamble
    "movq %%rsp, %%rbp ; "
    "pushq %%rdx; "            // preserve registers
    "pushq %%rsi; "
    "pushq $1; "               // save the syscall number for later
    "call strlen; "            // get the length of the string
    "movq %%rax, %%rdx; "      // store that length in rdx - count
    "movq %%rdi, %%rsi; "      // store string address to rsi - buf
    "movq $1, %%rdi; "         // store 1 in rdi - stdout
    "popq %%rax; "             // was 1 - sys_write
    "syscall; "                
    "popq %%rsi; "             // restore saved registers
    "popq %%rdx; "
    "leave; "                  // function postamble
    "ret; "
    ::
  );
}


// Find the length of the string; 
// input: rdi - string
// output: rax - length
__attribute__((sysv_abi, naked))
long unsigned int strlen(char* string) {
  __asm__(
    "push %%rsi; "            // store all the registers :-)
    "push %%rdx; "
    "push %%rcx; "
    "push %%rdi; "
    "movq $0x10000, %%rcx; "  // set maximum length
    "xor %%rax, %%rax; "      // set the character to find (null byte)
    "repne scasb; "           // scan the string in rdi until null byte gets hit
    "subq (%%rsp), %%rdi; "   // subtract stored start of string address from the new address (null byte) 
    "movq %%rdi, %%rax; "     // save it to rax
    "popq %%rdi; "            // restore registers
    "popq %%rcx; "
    "popq %%rdx; "
    "popq %%rsi; "
    "ret; "
    ::
  );
} 

// read the string from stdin to buffer; 
// input: rdi - buffer
// output: rax - length read
__attribute__((sysv_abi, naked))
int gets(char* buf) {
  __asm__(
    "pushq %%rdx; "            // preserve registers
    "pushq %%rsi; "
    "movq $0x10000, %%rdx; "  // set maximum length
    "movq %%rdi, %%rsi; "      // store buffer address to rsi - buf
    "movq $0, %%rdi; "         // store 0 in rdi - stdin
    "movq $0, %%rax; "         // store 0 in rax - sys_read
    "syscall; "                
    "popq %%rsi; "             // restore saved registers
    "popq %%rdx; "
    "ret; "
    ::
  );
}
   
