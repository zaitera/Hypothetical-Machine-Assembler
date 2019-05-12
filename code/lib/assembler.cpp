#include <assembler.h>

Assembler::Assembler(std::fstream *source)
{
    this->source_code_file = source;
}

Assembler::~Assembler(){}

void Assembler::labelLexicalAnalysis(std::string label)
{
    if(!isalpha(label[0]))
    {
        std::string msg("Lexical error: '");
        msg.insert(16,label); 
        msg.insert(16+label.size(),"' label starts with non-alphabetic character '");
        msg.insert(msg.end(),1,label[0]); 
        msg.insert(msg.end(),1,'\''); 
        throw msg;
    }else
    {
        for(char& c : label) 
        {
            if(!isalnum(c) && c != '_' )
            {
                std::string msg("Lexical error: '");                
                msg.insert(16,label); 
                msg.insert(16+label.size(),"' label contains a non-alphanumeric character '");
                msg.insert(msg.end(),1,c); 
                msg.insert(msg.end(),1,'\''); 
                throw msg;
                break;
            }
        }
    }
}

void Assembler::instLexicalAnalysis(std::string instruction)
{
    for(char& c : instruction) 
    {
        if(!isalpha(c))
        {
            std::string msg("Lexical error: '");                
            msg.insert(16,instruction); 
            msg.insert(16+instruction.size(),"' instruction contains a non-alphanumeric character '");
            msg.insert(msg.end(),1,c); 
            msg.insert(msg.end(),1,'\''); 
            throw msg;
            break;
        }
    }
}

void Assembler::memoryParamLexicalAnalysis(std::string memparam)
{
    if(!isalpha(memparam[0]))
    {
        std::string msg("Lexical error: '");
        msg.insert(16,memparam); 
        msg.insert(16+memparam.size(),"' memory address parameter starts with non-alphabetic character '");
        msg.insert(msg.end(),1,memparam[0]); 
        msg.insert(msg.end(),1,'\''); 
        throw msg;
    }else
    {
        for(char& c : memparam) 
        {
            if(!isalnum(c) && c!= '+')
            {
                std::string msg("Lexical error: '");                
                msg.insert(16,memparam); 
                msg.insert(16+memparam.size(),"' memory address parameter contains a non-alphanumeric character '");
                msg.insert(msg.end(),1,c); 
                msg.insert(msg.end(),1,'\''); 
                throw msg;
                break;
            }
        }
    }
}

void Assembler::constValLexicalAnalysis(std::string instruction)
{
    for(char& c : instruction) 
    {
        if(!isdigit(c) && c != '+' && c != '-'&& c != 'x')
        {
            std::string msg("Lexical error: '");                
            msg.insert(16,instruction); 
            msg.insert(16+instruction.size(),"' constant value contains a non-numeric related character '");
            msg.insert(msg.end(),1,c); 
            msg.insert(msg.end(),1,'\''); 
            throw msg;
            break;
        }
    }
}
void Assembler::spcharLexicalAnalysis(std::string special_char)
{
    std::vector<char> special_characters{SPECIAL_CHARACTERS, '-', '+'};    
    bool found = false;
    for(char& c : special_characters) 
    {
        if(c == special_char[0])
        {
            found = true;
            break;
        }
    }
    if (!found)
    {
        std::string msg("Lexical error: '");                
        msg.insert(16,special_char); 
        msg.insert(17,"' is illegal character for this context.");
        throw msg;
    }
    
}

void Assembler::lexicalAnalyzer(std::string token, TokenType type)
{
    switch(type)
    {
        case spchar:
            try
            {
                spcharLexicalAnalysis(token);
            }catch (std::string errmsg) {
                throw errmsg;
            }
            break;
        case inst:
            try
            {
                instLexicalAnalysis(token);
            }catch (std::string errmsg) {
                throw errmsg;
            }
            break;
        case label:
            try
            {
                labelLexicalAnalysis(token);
            }catch (std::string errmsg) {
                throw errmsg;
            }
            break;
        case memparameter:
            try
            {
                memoryParamLexicalAnalysis(token);
            }catch (std::string errmsg) {
                throw errmsg;
            }
            break;
        case constval:
            try
            {
                constValLexicalAnalysis(token);
            }catch (std::string errmsg) {
                throw errmsg;
            }
            break;
        default: break;    
    }
}

void Assembler::instructionSintax(std::vector<std::string> sentence)
{
    try
    {
        lexicalAnalyzer(sentence[0],inst);
    }catch (std::string errmsg) {
        std::cout <<errmsg << " -> in line " << i+1 <<" of preprocessed AND line "<<std::get<0>(this->file_being_assembled[i])+1 <<" of original source code."<<std::endl;
    }
    for (size_t i = 1; i < sentence.size() ; i+=2)
    {
        try
        {
            lexicalAnalyzer(sentence[i],memparameter);
        }catch (std::string errmsg) {
            std::cout <<errmsg << " -> in line " << i+1 <<" of preprocessed AND line "<<std::get<0>(this->file_being_assembled[i])+1 <<" of original source code."<<std::endl;
        }
    }
}

uint8_t Assembler::countWords(std::vector<std::string> sentence)
{
    uint8_t cont;
    std::vector<char> special_characters{SPECIAL_CHARACTERS, '-','+'};
    bool found = false;
    for (size_t i = 0,cont = 0; i < sentence.size(); i++)
    {
        if(sentence[i].size()>1)
        {
            cont++;
        }else
        {
            for (size_t i = 0; i < special_characters.size(); i++)
            {
                std::string as_str(1, special_characters[i]);
                if (as_str == sentence[i])
                {
                    found = true;
                    break;
                }
                
            }
            if (!found)
            {
                cont++;
            }  
        }
    }
    
}

void Assembler::sintaticAnalyzer(void)
{
    for(size_t i = 0; i != this->file_being_assembled.size(); i++ )
    {
        auto aux = std::get<1>(this->file_being_assembled[i]);
        
        if (aux[1] == ":")
        {
            try
            {
                lexicalAnalyzer(aux[0],label);
            }catch (std::string errmsg) {
                std::cout <<errmsg << " -> in line " << i+1 <<" of preprocessed AND line "<<std::get<0>(this->file_being_assembled[i])+1 <<" of original source code."<<std::endl;
            }
        }

    }
}

void Assembler::assemble(void)
{
    PreProcessor pre_processor(this->source_code_file);
    this->file_being_assembled = pre_processor.preProcess();
    sintaticAnalyzer();
}