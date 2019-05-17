#include <assembler.h>

int main(int argc, char ** argv)
{
    std::fstream src_code;
    
    if (argc!=2)
    {
        std::cerr<<"Arguments number is not valid, this programs recieve the file to be assembler as a parameter."<<std::endl;
        return 0;
    }else
    {
        src_code.open(argv[1],std::ios::in);
        if (src_code.good())
        {
            std::cout<<"File '"<< argv[1]<<"' opened successfully."<<std::endl;
        }else
        {
            std::cerr<<"File not found."<<std::endl;
            return 0;
        }   
    }
 
    Assembler assembler(&src_code);
    assembler.assemble();
    return 0;
}