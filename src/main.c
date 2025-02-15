#include <fileioc.h>

#ifdef DEBUG
#include <debug.h>
#endif

#include "interpreter.h"
#include "static.h"

int main(void) {
    const char* filename = "SNOW";
    uint8_t programHandle = ti_OpenVar(filename, "r", OS_TYPE_PRGM);
    if (programHandle == 0) {
        dbg_printf("Unable to read prgm%s.", filename);
        return 1;
    }

    clear_key_buffer();
    
    #ifdef DEBUG
    dbg_ClearConsole();
    dbg_printf("Reading prgm%s\n", filename);
    #endif

    size_t programSize = ti_GetSize(programHandle);

    if (programSize == 0) {
        dbg_printf("Program size 0!\n");
        ti_Close(programHandle);
        return 2;    
    }

    ProgramToken* program = malloc(programSize);
    if (program == NULL) {
        dbg_printf("Could not allocate program buffer!\n");
        ti_Close(programHandle);
        return 3;
    }
    size_t readCount = ti_Read(program, 1, programSize, programHandle);

    #ifdef DEBUG
    dbg_printf("Size: %d read %d\n", programSize, readCount);
    #endif
    
    if (readCount != programSize) {
        dbg_printf("Size mismatch!\n");
        free(program);
        ti_Close(programHandle);
        return 4;
    }

    Interpreter_Interpret(program, programSize);

    free(program);
    ti_Close(programHandle);

    return 0;
}