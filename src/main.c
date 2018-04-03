#include "compiled_blocks.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define MAX_STACK_SIZE 1024
char *my_stack[MAX_STACK_SIZE]; //depth of brackets nesting
int my_stack_index = 0;

#define MAX_INPUT_PROG_SIZE 65536

#define JIT_CODE_MAX_SIZE (MAX_INPUT_PROG_SIZE * 16)

ssize_t read_program(char *start, int fd) {
    ssize_t sz;
    size_t all = 0;
    while ((sz = read(fd, start, MAX_INPUT_PROG_SIZE - all)) != 0) {
        start += sz;
        all += sz;
    }
    if(sz == -1) return -1;
    if(sz != 0) return -2;
    return all;
}


void fill_jmp_addr(char *a, char *b) {
    int sizeof_jne = 30;

    //a - pointer to instruction: jmp

    //b - pointer to instruction: get access to array before jne

    unsigned int from_a_to_b = (unsigned int) ((b - a - 5) & 0xffffffff);

    *(a + 1) = (unsigned char) (from_a_to_b & 0xff);
    *(a + 2) = (unsigned char) ((from_a_to_b >> 8) & 0xff);
    *(a + 3) = (unsigned char) ((from_a_to_b >> 16) & 0xff);
    *(a + 4) = (unsigned char) ((from_a_to_b >> 24) & 0xff);

    from_a_to_b += sizeof_jne;
    from_a_to_b *= -1;

    *(b + sizeof_jne - 4) = (unsigned char) (from_a_to_b & 0xff);
    *(b + sizeof_jne - 3) = (unsigned char) ((from_a_to_b >> 8) & 0xff);
    *(b + sizeof_jne - 2) = (unsigned char) ((from_a_to_b >> 16) & 0xff);
    *(b + sizeof_jne - 1) = (unsigned char) ((from_a_to_b >> 24) & 0xff);
}


int main(int argc, const char *argv[]) {
    char text[MAX_INPUT_PROG_SIZE];

    if (argc < 2) {
        printf("Usage: jit_runner <program.bf>\n");
        exit(EXIT_FAILURE);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    ssize_t sz = read_program(text, fd);

    if(sz == -1){
        perror("read");
        exit(EXIT_FAILURE);
    }else if(sz == -2){
        printf("Input program too large\n");
        exit(EXIT_FAILURE);
    }

    close(fd);

    char *addr;
    addr = mmap(NULL, JIT_CODE_MAX_SIZE, PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (addr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }


    int prog_ind = 0;
    for (int k = 0; k < sizeof(preparing); ++k) {
        addr[prog_ind + k] = preparing[k];
    }
    prog_ind += sizeof(preparing);

    char *cur_to = 0;
    char *tmp_ptr = 0;

    for (int i = 0; i < sz - 1; ++i) {
        switch (text[i]) {
            case '>':
                for (int k = 0; k < sizeof(indexincr); ++k) {
                    addr[prog_ind + k] = indexincr[k];
                }
                prog_ind += sizeof(indexincr);
                break;
            case '<':
                for (int k = 0; k < sizeof(indexdec); ++k) {
                    addr[prog_ind + k] = indexdec[k];
                }
                prog_ind += sizeof(indexdec);
                break;
            case '+':
                for (int k = 0; k < sizeof(arincr); ++k) {
                    addr[prog_ind + k] = arincr[k];
                }
                prog_ind += sizeof(arincr);
                break;
            case '-':
                for (int k = 0; k < sizeof(ardec); ++k) {
                    addr[prog_ind + k] = ardec[k];
                }
                prog_ind += sizeof(ardec);
                break;
            case '.':
                for (int k = 0; k < sizeof(ptchr); ++k) {
                    addr[prog_ind + k] = ptchr[k];
                }
                prog_ind += sizeof(ptchr);
                break;
            case ',':
                for (int k = 0; k < sizeof(gtchr); ++k) {
                    addr[prog_ind + k] = gtchr[k];
                }
                prog_ind += sizeof(gtchr);
                break;
            case '[':
                my_stack[my_stack_index++] = &addr[prog_ind];
                for (int k = 0; k < sizeof(jmp_code); ++k) {
                    addr[prog_ind + k] = jmp_code[k];
                }
                prog_ind += sizeof(jmp_code);
                break;
            case ']':
                cur_to = &addr[prog_ind];
                tmp_ptr = my_stack[--my_stack_index];
                for (int k = 0; k < sizeof(jne_code); ++k) {
                    addr[prog_ind + k] = jne_code[k];
                }
                prog_ind += sizeof(jne_code);
                fill_jmp_addr(tmp_ptr, cur_to);
                break;
        }
    }

    for (int k = 0; k < sizeof(ending); ++k) {
        addr[prog_ind + k] = ending[k];
    }
    prog_ind += sizeof(ending);

    int rez = mprotect(addr, JIT_CODE_MAX_SIZE, PROT_EXEC);
    if (rez != 0) {
        perror("mprotect");
        exit(EXIT_FAILURE);
    }

    void (*prog)();
    prog = addr;

    int (*m1p)(int) = putchar;
    int (*m1g)() = getchar;
    void *(*mlc)(size_t) = malloc;

    prog(m1p, m1g, mlc);

    rez = munmap(addr, JIT_CODE_MAX_SIZE);
    if (rez != 0) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }

}
