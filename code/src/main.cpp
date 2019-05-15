#include <assembler.h>

int main()
{
    std::fstream src_code;
    src_code.open("test.asm",std::ios::in );
    Assembler assembler(&src_code);
    assembler.assemble();
    return 0;
}