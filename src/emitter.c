#include "emitter.h"
#include "parser.h"

EmitPos* emit_pos;
FILE *f_emit;
FILE *f_header;

uint8_t init_emitter() {
    printf("\nInitialize emiiter...");
    emit_pos = (EmitPos*)malloc(sizeof(EmitPos));
    emit_pos->code_pos =    (uint32_t*)malloc(sizeof(uint32_t));
    *(emit_pos->code_pos) = 0;
    emit_pos->header_pos =  (uint32_t*)malloc(sizeof(uint32_t));
    *(emit_pos->header_pos) = 0;
    fclose(fopen("../f_emit.txt", "w"));
    fclose(fopen("../f_header.txt", "w"));
    // f_emit = fopen("../f_emit.txt", "w");
    printf("\n>>Initialize DONE...");
}

uint8_t f_write( char* code, FILE *fp, uint32_t* pos) {
    printf("\n>>Writing code to file");
    int32_t code_size = size(code);
    uint8_t element_size = sizeof(char);
    fseek(fp, *pos, SEEK_SET);
    fwrite(code, element_size, code_size, fp);
    *pos = *pos + code_size;
    printf("\n>>Writing DONE");
}

uint8_t emit(char* code) {
    f_emit = fopen("../f_emit.txt", "a");
    printf("\n>>Pointer emit_pos->code_pos = %d", *(emit_pos->code_pos));
    f_write(code, f_emit, emit_pos->code_pos);
    fclose(f_emit);
    printf("\n>>Emit DONE");
}

uint8_t emit_newline(char* code) {
    f_emit = fopen("../f_emit.txt", "a");
    printf("\n>>Pointer emit_pos->code_pos = %d", *(emit_pos->code_pos));
    f_write("\n", f_emit, emit_pos->code_pos);
    f_write(code, f_emit, emit_pos->code_pos);
    fclose(f_emit);
    printf("\n>>Emit DONE");
}

uint8_t emit_header(char* code) {
    f_header = fopen("../f_header.txt", "a");
    printf("\n>>Pointer emit_pos->header_pos = %d", *(emit_pos->header_pos));
    f_write(code, f_header, emit_pos->header_pos);
    fclose(f_header);
    printf("\n>>Write Header DONE");
}

uint8_t emit_header_nl(char* code) {
    f_header = fopen("../f_header.txt", "a");
    printf("\n>>Pointer emit_pos->header_pos = %d", *(emit_pos->header_pos));
    f_write("\n", f_header, emit_pos->header_pos);
    f_write(code, f_header, emit_pos->header_pos);
    fclose(f_header);
    printf("\n>>Write Header DONE");
}

uint8_t file_write(FILE *f_submit) {
    // FILE* file;
    // size_t* reader;
    const uint8_t size = 8;
    uint8_t buffer[size];
    size_t read_bytes = 0;
    size_t total_bytes = 0;
    f_submit =  fopen("../f_final.txt",     "w");
    f_emit =    fopen("../f_emit.txt",      "r");
    f_header =  fopen("../f_header.txt",    "r");
    while ((read_bytes = fread(buffer, 1, size, f_header)) > 0) {
        printf("\n>> read_byte = %d", read_bytes);
        fwrite(buffer, 1, read_bytes, f_submit);
        // total_bytes = total_bytes + read_bytes;
    }
    // fseek(f_submit, total_bytes, SEEK_SET);
    while ((read_bytes = fread(buffer, 1, size, f_emit)) > 0) {
        printf("\n>> read_byte = %d", read_bytes);
        fwrite(buffer, 1, read_bytes, f_submit);
    }
    fclose(f_emit);
    fclose(f_header);
    fclose(f_submit);
    // return file;
}


