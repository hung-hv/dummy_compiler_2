#ifndef EMITTER_H
#define EMITTER_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



typedef struct EmitterPositon_t {
    uint32_t* code_pos;
    uint32_t* header_pos;
} EmitPos;

extern EmitPos* emit_pos;
extern FILE *f_emit;
extern FILE *f_header;

uint8_t init_emitter();
uint8_t f_write( char* code, FILE *fp, uint32_t* pos);
uint8_t emit(char* code);
uint8_t emit_newline(char* code);
uint8_t emit_header(char* code);
uint8_t file_write(FILE *f_submit); 
//haha
#endif 