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
        std::string msg("Lexical error: »'");
        msg = msg + label + "' label starts with non-alphabetic character '";
        msg.insert(msg.end(),1,label[0]); 
        msg.insert(msg.end(),1,'\''); 
        throw msg;
    }else
    {
        for(char& c : label) 
        {
            if(!isalnum(c) && c != '_' )
            {
                std::string msg("Lexical error: »'");                
                msg = msg + label + "' label contains a non-alphanumeric character '";
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
    if(instOpcodesMP.count(instruction)==0)
    {
        std::string msg("Lexical error: »'");                
        msg = msg + instruction + "' instruction was not recognized ";
        throw msg;
    }
}
void Assembler::dataDirectiveLexicalAnalysis(std::string directive)
{
    if(directive!="SPACE" && directive != "CONST" )
    {
        std::string msg("Lexical error: »'");                
        msg = msg + directive + "' data directive was not recognized ";
        throw msg;
    }
}
void Assembler::memoryParamLexicalAnalysis(std::string memparam)
{
    if(!isalpha(memparam[0]))
    {
        std::string msg("Lexical error: »'");
        msg = msg + memparam + "' memory address parameter starts with non-alphabetic character '";
        msg.insert(msg.end(),1,memparam[0]); 
        msg.insert(msg.end(),1,'\''); 
        throw msg;
    }else
    {
        for(char& c : memparam) 
        {
            if(!isalnum(c) && c!= '+')
            {
                std::string msg("Lexical error: »'");                
                msg = msg + memparam + "' memory address parameter contains a non-alphanumeric character '";
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
        if(!isdigit(c) && c != '+' && c != '-'&& c != 'X')
        {
            std::string msg("Lexical error: »'");                
            msg = msg + instruction + "' constant value contains a non-numeric related character '";
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
        std::string msg("Lexical error: »'");                
        msg.insert(16,special_char); 
        msg.insert(17,"' is illegal character for this context ");
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
        case datdirective:
            try
            {
                dataDirectiveLexicalAnalysis(token);
            }catch (std::string errmsg) {
                throw errmsg;
            }
            break;
        default: break;    
    }
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

uint16_t Assembler::labelAnalysis(std::vector<std::string> line, uint16_t mem_pos )
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
                    throw errmsg;
                }
                this->symbolsTableMP.insert( std::pair<std::string,uint16_t>(line[0],mem_pos) );
                printMAP(symbolsTableMP);
                return 2;
            }else
            {
                errmsg = "Syntactic error: »'"+line[0]+"' has been defined befores ";
                throw errmsg; 
            }
        }else
        {
            errmsg = "Syntactic error: »'"+line[0]+"' label declaration symbol ':' at wrong place ";
            throw errmsg;
        }            
        
    }else if (symbol_count > 1)
    {
        errmsg = "Syntactic error: »'"+line[0]+"' has more than one label declaration symbol ':' ";
        throw errmsg;
    }
    return 0;
}

Section Assembler::sectionAnalysis(std::string str)
{
    std::string errmsg;
    if(str == "TEXT") 
        return TEXT;
    else if(str == "DATA")
        return DATA;
    else{
        errmsg = "Lexical error: »'"+str+"' is invalid section name ";
        throw errmsg;
    }
}
void Assembler::firstPass(void)
{
    Section section = UNDEFINED;
    std::string errmsg;
    uint16_t mem_pos = 0;
    uint16_t current_token;
    for(size_t i = 0; i != this->file_being_assembled.size(); i++ )
    {
        auto line = std::get<1>(this->file_being_assembled[i]);
        current_token = 0;
        if (line[0] == "SECTION")
        {
            if (line.size()>2)
            {
                errmsg = "Syntactic error: »'"+line[1]+" "+line[2]+"' unrecognized section declaration -> in line "+ std::to_string(i+1) +" of preprocessed AND line "+std::to_string(std::get<0>(this->file_being_assembled[i])+1)+" of original source code.";
                throw errmsg;
            }
            try
            {
                section = sectionAnalysis(line[1]);
            }
            catch(std::string errmsg)
            {
                errmsg = errmsg +  "-> in line "+ std::to_string(i+1) +" of preprocessed AND line "+std::to_string(std::get<0>(this->file_being_assembled[i])+1)+" of original source code.";
                throw errmsg;
            }
            continue;
        }
        if (section == UNDEFINED)
        {
            errmsg = "Semantic error: program running on undefined section -> in line "+ std::to_string(i+1) +" of preprocessed AND line "+std::to_string(std::get<0>(this->file_being_assembled[i])+1)+" of original source code.";
            throw errmsg;
        }        
        try
        {
            current_token = labelAnalysis(line, mem_pos);
        }
        catch(std::string errmsg)
        {
            errmsg = errmsg + "-> in line "+ std::to_string(i+1) +" of preprocessed AND line "+std::to_string(std::get<0>(this->file_being_assembled[i])+1)+" of original source code.";
            throw errmsg;
        }

        if (current_token >= line.size())   continue;
        
        switch (section)
        {
            case TEXT:{
                try
                {
                    lexicalAnalyzer(line[current_token],inst);
                }
                catch(std::string errmsg)
                {
                    errmsg = errmsg + "-> in line "+ std::to_string(i+1) +" of preprocessed AND line "+std::to_string(std::get<0>(this->file_being_assembled[i])+1)+" of original source code.";
                    throw errmsg;
                }
                auto mem_spaces =  this->memSpacesMP.at(line[current_token]);
                auto aux = (line[current_token] == "COPY")? mem_spaces+1:mem_spaces;
                if (line.size()-current_token < aux || line.size()-current_token >aux )
                {                
                    errmsg = "Syntactic error: »'"+line[current_token]+"' instruction format or amount of parameter is invalid (requires "+std::to_string(mem_spaces-1)+" parameters) -> in line "+ std::to_string(i+1) +" of preprocessed AND line "+std::to_string(std::get<0>(this->file_being_assembled[i])+1)+" of original source code.";
                    throw errmsg;
                }
                try
                {
                    for (size_t i = 1; i < mem_spaces; i++)
                    {
                        lexicalAnalyzer(line[current_token+(i*2-1)], label); //i*2 -1 to consider the ',' between parameters
                    }                
                }
                catch(std::string errmsg)
                {
                    errmsg += " as instruction '" +line[current_token]+"' parameter -> in line "+ std::to_string(i+1) +" of preprocessed AND line "+std::to_string(std::get<0>(this->file_being_assembled[i])+1)+" of original source code.";
                    throw errmsg;
                }
                mem_pos += mem_spaces;
                break;
            }case DATA:
                try
                {
                    lexicalAnalyzer(line[current_token],datdirective);
                }
                catch(std::string errmsg)
                {
                    errmsg = errmsg + "-> in line "+ std::to_string(i+1) +" of preprocessed AND line "+std::to_string(std::get<0>(this->file_being_assembled[i])+1)+" of original source code.";
                    throw errmsg;
                }

                if (line[current_token] == "CONST")
                {
                    if (line.size()-current_token <= 1)
                    {
                        errmsg = "Syntactic error: »'CONST' directive is not followed by any value -> in line "+ std::to_string(i+1) +" of preprocessed AND line "+std::to_string(std::get<0>(this->file_being_assembled[i])+1)+" of original source code.";
                        throw errmsg;
                    }
                    
                    try
                    {
                        lexicalAnalyzer(line[current_token+1], constval);
                    }
                    catch(std::string errmsg)
                    {
                        errmsg = errmsg + "-> in line "+ std::to_string(i+1) +" of preprocessed AND line "+std::to_string(std::get<0>(this->file_being_assembled[i])+1)+" of original source code.";
                        throw errmsg;
                    }
                    mem_pos += 1;
                }
                if (line[current_token] == "SPACE")
                {
                    auto aux = line.size()-current_token;
                    if ( aux >= 2 )
                    {
                        if ((line[current_token+1].find_first_not_of( "0123456789" ) != std::string::npos) || aux > 2)
                        {
                            errmsg = "Lexical error: »'SPACE' directive is followed by invalid token (not an integer number or valid line) -> in line "+ std::to_string(i+1) +" of preprocessed AND line "+std::to_string(std::get<0>(this->file_being_assembled[i])+1)+" of original source code.";
                            throw errmsg;
                        }
                        std::stringstream str(line[current_token+1]);
                        uint16_t aux;
                        str >> aux;
                        mem_pos += (aux-1);
                    }
                    mem_pos += 1;
                }
                break;
            default:
                break;
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