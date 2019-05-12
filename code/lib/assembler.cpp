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
    // for(char& c : instruction) 
    // {
    //     if(!isalpha(c))
    //     {
    //         std::string msg("Lexical error: '");                
    //         msg.insert(16,instruction); 
    //         msg.insert(16+instruction.size(),"' instruction contains a non-alphanumeric character '");
    //         msg.insert(msg.end(),1,c); 
    //         msg.insert(msg.end(),1,'\''); 
    //         throw msg;
    //         break;
    //     }
    // }
    if(instOpcodesMP.find(instruction)==instOpcodesMP.end())
    {
        std::string msg("Lexical error: '");                
        msg.insert(16,instruction); 
        msg.insert(16+instruction.size(),"' instruction was not recognized.");
        throw msg;
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

uint8_t Assembler::countWords(std::vector<std::string> sentence)
{
    uint8_t cont = 0;
    std::vector<char> special_characters{SPECIAL_CHARACTERS, '-','+'};
    bool found;
    for (size_t i = 0; i < sentence.size(); i++)
    {
        found = false;
        if(sentence[i].size()>1)
        {
            cont++;
        }else
        {
            for (size_t j = 0; j < special_characters.size(); j++)
            {
                if (special_characters[j] == sentence[i][0])
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
    return cont;
}


struct size_less
{
    template<class T> bool operator()(T const &a, T const &b) const
    { return a.size() < b.size(); }
};
std::string maxWord(std::vector<std::string> const &lines)
{
    return *std::max_element(lines.begin(), lines.end(), size_less());
}

void printMAP(std::map<std::string, uint16_t> myMap)
{
    std::cout << "_________MAPi__________"<<std::endl;
    for(auto elem : myMap)
    {
        std::cout << elem.first << " -- " << elem.second << "\n";
    }
    std::cout << "_________MAPf__________"<<std::endl;

}

void Assembler::labelAnalysis(std::vector<std::string> line, uint16_t line_num_pre, uint16_t line_num_orig, uint16_t mem_pos )
{
    std::string errmsg;
    auto symbol_count = count(line.begin(), line.end(), ":");

    if ( symbol_count == 1 )
    {
        if (line[1] == ":")
        {
            
            if ( this->symbolsTableMP.count(line[0]) ==  0 )
            {
                try
                {
                    lexicalAnalyzer(line[0],label);
                }
                catch(std::string errmsg)
                {
                    errmsg = errmsg + "-> in line "+ std::to_string(line_num_pre) +" of preprocessed AND line "+std::to_string(line_num_orig)+" of original source code.";
                    throw errmsg;
                }
                this->symbolsTableMP.insert( std::pair<std::string,uint16_t>(line[0],mem_pos) );
                printMAP(symbolsTableMP);
            }else
            {
                errmsg = "Syntactic error: »'"+line[0]+"' has been defined befores -> in line "+ std::to_string(line_num_pre) +" of preprocessed AND line "+std::to_string(line_num_orig)+" of original source code.";
                throw errmsg; 
            }
        }else
        {
            errmsg = "Syntactic error: »'"+line[0]+"' has more than one label declaration symbol ':' -> in line "+ std::to_string(line_num_pre) +" of preprocessed AND line "+std::to_string(line_num_orig)+" of original source code.";
            throw errmsg;
        }            
        
    }else if (symbol_count > 1)
    {
        errmsg = "Syntactic error: »'"+line[0]+"' has more than one label declaration symbol ':' -> in line "+ std::to_string(line_num_pre) +" of preprocessed AND line "+std::to_string(line_num_orig)+" of original source code.";
        throw errmsg;
    }
}

Section Assembler::sectionAnalysis(std::string str,uint16_t line_num_pre, uint16_t line_num_orig)
{
    std::string errmsg;
    if(str == "TEXT") 
        return TEXT;
    else if(str == "DATA")
        return DATA;
    else{
        errmsg = "Lexical error: »"+str+" is invalid section name -> in line "+ std::to_string(line_num_pre) +" of preprocessed AND line "+std::to_string(line_num_orig)+" of original source code.";
        throw errmsg;
    }
}
void Assembler::firstPass(void)
{
    Section section = UNDEFINED;
    std::string errmsg;
    uint16_t mem_pos = 0;
    for(size_t i = 0; i != this->file_being_assembled.size(); i++ )
    {
        auto line = std::get<1>(this->file_being_assembled[i]);
        //treating cases wheres theres less than two valid tokens in the line
        if (countWords(line)<2)
        {
            errmsg = "Syntactic error: »'"+maxWord(line)+"' line contains less than two words -> in line "+ std::to_string(i+1) +" of preprocessed AND line "+std::to_string(std::get<0>(this->file_being_assembled[i])+1)+" of original source code.";
            throw errmsg;
        }
        //checking 
        if (line[0] == "SECTION")
        {
            try
            {
                section = sectionAnalysis(line[1],i+1, std::get<0>(this->file_being_assembled[i])+1);
            }
            catch(std::string errmsg)
            {
                throw errmsg;
            }
        }
        if (section == UNDEFINED)
        {
            errmsg = "Semantic error: program running on undefined section -> in line "+ std::to_string(i+1) +" of preprocessed AND line "+std::to_string(std::get<0>(this->file_being_assembled[i])+1)+" of original source code.";
            throw errmsg;
        }        
        try
        {
            labelAnalysis(line,i+1, std::get<0>(this->file_being_assembled[i])+1, mem_pos);
        }
        catch(std::string errmsg)
        {
            throw errmsg;
        }
        
       
    }
}

void Assembler::assemble(void)
{
    PreProcessor pre_processor(this->source_code_file);
    this->file_being_assembled = pre_processor.preProcess();
    try{
        firstPass();
    } catch(std::string errmsg)
    {
        std::cout<<errmsg<<std::endl;
    }
}