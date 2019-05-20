#include <assembler.h>

int main(int argc, char ** argv)
{
    std::fstream src_code;
    if (argc!=2)
    {
        std::cerr<<"Arguments number is not valid, this program recieves the name of file to be assembled as an argument."<<std::endl;
        return 0;
    }else
    {
        std::string name(argv[1]);

        if (name.substr(name.find_last_of(".") + 1) != "asm")
        {
            std::cerr<<"File extension is not valid, only accepts .asm files."<<std::endl;
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
    }
 
    Assembler assembler(&src_code);
    assembler.file_name = argv[1];
    assembler.assemble();
    return 0;
}
