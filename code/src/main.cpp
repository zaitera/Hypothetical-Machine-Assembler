#include <assembler.h>
#include <preprocessor.h>

int main()
{
    std::fstream src_code;
    src_code.open("test.txt",std::ios::in );
    PreProcessor pre_processor = PreProcessor(&src_code);
    pre_processor.preProcess();
    return 0;
}