#include <assembler.h>

Assembler::Assembler(std::fstream *source)
{
    this->source_code_file = source;
}

Assembler::~Assembler(){}

void Assembler::lexicalAnalyzer(std::string word)
{
    if(!isalpha(word[0]) && (word.size() > 1))
    {
        throw "Word starts with non-alphabetic character";
    }else
    {
        bool found = false; 
        std::vector<char> special_characters{SPECIAL_CHARACTERS,'_'};
        for(char& c : word) 
        {
            for(char& s : special_characters) 
            {
                if (c==s)
                {
                    found = true;
                    break;
                }
            }
            if(!isalnum(c) && !found)
            {
                
                throw "Word contains illegal character, not an alphanumeric character";
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
            } catch (const char* msg) {
                std::cerr << msg << " -> in line " << i+1 <<" of preprocessed AND line "<<std::get<0>(this->file_being_assembled[i])+1 <<" of original source code."<<std::endl;
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