#include <assembler.h>

Assembler::Assembler(std::fstream *source)
{
    this->source_code_file = source;
}

Assembler::~Assembler(){}

void Assembler::lexicalAnalyzer(std::string token)
{
    if(!isalpha(token[0]) && (token.size() > 1))
    {
        std::string msg("Lexical error: '");
        msg.insert(16,token); 
        msg.insert(16+token.size(),"' starts with non-alphabetic character '");
        msg.insert(msg.end(),1,token[0]); 
        msg.insert(msg.end(),1,'\''); 
        throw msg;
    }else if(token.size() > 1)
    {
        for(char& c : token) 
        {
            if(!isalnum(c) && c != '_' )
            {
                std::string msg("Lexical error: '");                
                msg.insert(16,token); 
                msg.insert(16+token.size(),"' contains a non-alphanumeric character '");
                msg.insert(msg.end(),1,c); 
                msg.insert(msg.end(),1,'\''); 
                throw msg;
                break;
            }
        }
    }
}

void Assembler::testLexicalAnalyzer(void)
{
    for(size_t i = 0; i != this->file_being_assembled.size(); i++ )
    {
        for(size_t j = 0; j != std::get<1>(this->file_being_assembled[i]).size(); j++ )
        {
            try
            {
                lexicalAnalyzer(std::get<1>(this->file_being_assembled[i])[j]);
            } catch (std::string errmsg) {
                std::cout <<errmsg << " -> in line " << i+1 <<" of preprocessed AND line "<<std::get<0>(this->file_being_assembled[i])+1 <<" of original source code."<<std::endl;
            }
        }
    }
}

void Assembler::assemble(void)
{
    PreProcessor pre_processor(this->source_code_file);
    this->file_being_assembled = pre_processor.preProcess();
    testLexicalAnalyzer();
}