#include <assembler.h>

Assembler::Assembler(std::fstream *source)
{
    this->source_code_file = source;
}

Assembler::~Assembler(){}

void Assembler::printCurrentTupleList(void)
{
    
    std::cout << "__________Current Tuple List___________"<<std::endl;
    
    for(size_t i = 0; i != this->file_being_assembled.size(); i++ )
    {
        std::cout << std::setfill('0') << std::setw(3) << std::get<0>(this->file_being_assembled[i])+1 << " ";
        for(size_t j = 0; j != std::get<1>(this->file_being_assembled[i]).size(); j++ )
            std::cout << std::get<1>(this->file_being_assembled[i])[j] << " ";
        std::cout << std::endl;
    } 
    std::cout << "__________End Tuple List___________"<<std::endl;
}

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
    if(inst_opcodes_MP.count(instruction)==0)
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
        bool found_plus = false;
        for(char& c : memparam) 
        {
            if (c == '+')
            {
                found_plus = true;
                continue;
            }
            if (!found_plus)
            {
                if(!isalnum(c) && c!='_')
                {
                    std::string msg("Lexical error: »'");                
                    msg = msg + memparam + "' memory address parameter contains a non-alphanumeric character '";
                    msg.insert(msg.end(),1,c); 
                    msg.insert(msg.end(),1,'\''); 
                    throw msg;
                    break;
                }
            }else
            {
                if(!isdigit(c))
                {
                    std::string msg("Lexical error: »'");                
                    msg = msg + memparam + "' in this memory address parameter the number summed to label is not valid '";
                    msg.insert(msg.end(),1,c); 
                    msg.insert(msg.end(),1,'\''); 
                    throw msg;
                    break;
                }
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
    std::vector<char> special_characters{SPECIAL_CHARACTERS, '+'};    
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

void printMAP(std::map<std::string, std::pair<uint16_t,uint16_t>> myMap)
{
    std::cout << "_________MAPi__________"<<std::endl;
    for(auto elem : myMap)
    {
        std::cout << elem.first << " -- " << elem.second.first<<" line= " <<elem.second.second<< "\n";
    }
    std::cout << "_________MAPf__________"<<std::endl;

}

uint16_t Assembler::labelAnalysis(std::vector<std::string> line, uint16_t mem_pos, uint16_t line_num)
{
    std::string errmsg;
    auto symbol_count = count(line.begin(), line.end(), ":");
    if ( symbol_count == 1 )
    {
        if (line[1] == ":")
        {
            if ( this->symbols_table_MP.count(line[0]) ==  0 )
            {
                try
                {
                    lexicalAnalyzer(line[0],label);
                }
                catch(std::string errmsg)
                {
                    throw errmsg;
                }
                auto aux = std::pair<uint16_t,uint16_t>(mem_pos,line_num);
                this->symbols_table_MP.insert( std::pair<std::string,std::pair<uint16_t,uint16_t>>(line[0],aux) );
                printMAP(symbols_table_MP);
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
        errmsg = "Syntatic error: »'"+str+"' is invalid section name ";
        throw errmsg;
    }
}

bool Assembler::isParametersNumberValid(uint16_t inst_size, uint16_t present_in_line)
{
    bool condition;
    switch (inst_size)
    {
        case 4:
            if (present_in_line == 4 || present_in_line == 6 || present_in_line == 8 )
            {
                condition = false;
            }else
            {
                condition = true;
            }
            break;
        case 1:
            condition = (present_in_line == inst_size)? false : true;
            break;                
        default:
            if (present_in_line == 2 || present_in_line == 4)
            {
                condition = false;
            }else
            {
                condition = true;
            }
            break;
    }
    return condition;
}
void Assembler::firstPass(void)
{
    Section section = UNDEFINED;
    std::string errmsg;
    uint16_t mem_pos_data = 0;
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
            auto temp = current_token;
            current_token = labelAnalysis(line, mem_pos, i);
           
            if (section == TEXT)
                if ( (current_token-temp) > 0)
                    std::get<1>(this->file_being_assembled[i]).erase(std::get<1>(this->file_being_assembled[i]).begin(), std::get<1>(this->file_being_assembled[i]).begin()+(current_token-temp));   
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

                auto mem_spaces =  this->mem_spaces_MP.at(line[current_token]);
                auto aux = (line[current_token] == "COPY")? mem_spaces+1:mem_spaces;

                if (isParametersNumberValid(aux, line.size()-current_token))
                {                
                    errmsg = "Syntactic error: »'"+line[current_token]+"' instruction format or amount of parameter is invalid (requires "+std::to_string(mem_spaces-1)+" parameters) -> in line "+ std::to_string(i+1) +" of preprocessed AND line "+std::to_string(std::get<0>(this->file_being_assembled[i])+1)+" of original source code.";
                    throw errmsg;
                }
                bool pendent_first = false;
                bool pendent_last = false;
                std::vector<std::string> copy_last;

                if (line.end()[-2] == "+")
                {
                    pendent_last = true;
                    auto joined_parameter = line.end()[-3] + line.end()[-2] + line.end()[-1];
                    copy_last = {line.end()[-3], line.end()[-2], line.end()[-1]};
                    line.end()[-3] = joined_parameter;
                    line.pop_back();
                    line.pop_back();
                }

                std::vector<std::string> copy_first;
                if (line[current_token] == "COPY" && line[current_token+2]=="+")
                {
                    pendent_first = true;
                    auto joined_parameter = line[current_token+1] + line[current_token+2] + line[current_token+3];
                    copy_first = {line[current_token+1], line[current_token+2], line[current_token+3]};
                    line[current_token+1] = joined_parameter;
                    auto it = line.begin()+current_token+2;
                    line.erase(it);
                    line.erase(it);
                }

                try
                {
                    for (size_t i = current_token+1; i < line.size(); i++)
                    {
                        if (i == current_token+2)
                        {
                            lexicalAnalyzer(line[i], spchar); //the ',' between parameters
                        }else
                        {
                            lexicalAnalyzer(line[i], memparameter);
                        }
                    }                
                }
                catch(std::string errmsg)
                {
                    errmsg += ", as instruction '" +line[current_token]+"' parameter -> in line "+ std::to_string(i+1) +" of preprocessed AND line "+std::to_string(std::get<0>(this->file_being_assembled[i])+1)+" of original source code.";
                    throw errmsg;
                }

                if (pendent_last)
                {
                    line.pop_back();
                    line.insert(line.end(), copy_last.begin(), copy_last.end());
                }

                if (pendent_first)
                {
                    auto it = line.begin()+current_token+1;
                    line.erase(it);
                    line.insert(it, copy_first.begin(), copy_first.end());
                }
                
                mem_pos += mem_spaces;
                break;
            }case DATA:
                if (mem_pos_data == 0)
                    mem_pos_data = i;
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
                    if ( line.size()>current_token+2 && line[current_token+1] == "+")
                    {
                        auto joined_parameter = line[current_token+1] + line[current_token+2];
                        line[current_token+1] = joined_parameter;
                        auto it = line.begin()+current_token+2;
                        line.erase(it);
                    }
                    if (line.size()-current_token <= 1 || line.size()-current_token>2 )
                    {
                        errmsg = "Syntactic error: »'CONST' directive is not followed by any value or followed by more than one value -> in line "+ std::to_string(i+1) +" of preprocessed AND line "+std::to_string(std::get<0>(this->file_being_assembled[i])+1)+" of original source code.";
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
    this->index_data_section = mem_pos_data;
                
}

void Assembler::semanticAnalyzerVectors(std::vector<std::string> line, size_t i)
{
    std::string errmsg;

    auto mem_spaces = this->mem_spaces_MP.at(line[0]);
    auto pos_mem1 = this->symbols_table_MP.at(line[1]);

    if ( THIS_IS_NOT_STOP_OR_COPY(mem_spaces) )
    {
        if (THIS_IS_A_VECTOR(line.size()))
        {
            if (std::stoi(line[3]) < 0)
            {
                errmsg = "Semantic error: Attempt to access a position not reserved by SPACE using negative parameter -> line" + std::to_string(i+1) +" of preprocessed AND line "+std::to_string(std::get<0>(this->file_being_assembled[i])+1)+" of original source code.";
                throw errmsg;
            }
            auto size_vector = std::get<1>(this->file_being_assembled[i])[4];
            if (std::stoi(line[3]) >= std::stoi(size_vector))
            {
                errmsg = "Semantic error: Attempt to access a position not reserved by SPACE using negative parameter -> line" + std::to_string(i+1) +" of preprocessed AND line "+std::to_string(std::get<0>(this->file_being_assembled[i])+1)+" of original source code.";
                throw errmsg;
            }
        }
    }
}

void Assembler::semanticAnalyzerGeneric(std::vector<std::string> line, size_t i)
{
    std::string errmsg;
        
    if( this->symbols_table_MP.count(line[1]) == 0)
    {
        errmsg = "Semantic error:  missing labels -> line" + std::to_string(i+1) +" of preprocessed AND line "+std::to_string(std::get<0>(this->file_being_assembled[i])+1)+" of original source code.";
        throw errmsg;   
    }

    auto opcode = this->inst_opcodes_MP.at(line[0]);
    auto pos_mem1 = this->symbols_table_MP.at(line[1]);

    if (THIS_IS_A_JUMP(opcode))
    {
        if(pos_mem1.second >= this->index_data_section)
        {
            errmsg = "Semantic error: Jump to invalid section -> line" + std::to_string(i+1) +" of preprocessed AND line "+std::to_string(std::get<0>(this->file_being_assembled[i])+1)+" of original source code.";
            throw errmsg;   
        }
    }
    else 
    {
        if(pos_mem1.second < this->index_data_section)
        {
            errmsg = "Semantic error: Jump to invalid section -> line" + std::to_string(i+1) +" of preprocessed AND line "+std::to_string(std::get<0>(this->file_being_assembled[i])+1)+" of original source code.";
            throw errmsg;   
        }
        
        auto line_label = std::get<1>(this->file_being_assembled[pos_mem1.second]);
            
        if (opcode == inst_opcodes_MP.at("DIV"))
        {
            if(line_label[2] == "CONST" && line_label[3] == "0")
            {
                errmsg = "Semantic error: Attempt to divide by zero -> line" + std::to_string(i+1) +" of preprocessed AND line "+std::to_string(std::get<0>(this->file_being_assembled[i])+1)+" of original source code.";
                throw errmsg;   
            }
        }
        else if (opcode == inst_opcodes_MP.at("INPUT"))
        {
            if(line_label[2] == "CONST")
            {
                errmsg = "Semantic error: Attempt to change a constant value -> line" + std::to_string(i+1) +" of preprocessed AND line "+std::to_string(std::get<0>(this->file_being_assembled[i])+1)+" of original source code.";
                throw errmsg;   
            }
        }
        else if (opcode == inst_opcodes_MP.at("COPY"))
        {
            if( this->symbols_table_MP.count(line[3]) == 0)
            {
                errmsg = "Semantic error: missing labels -> line" + std::to_string(i+1) +" of preprocessed AND line "+std::to_string(std::get<0>(this->file_being_assembled[i])+1)+" of original source code.";
                throw errmsg;   
            }
            if(line_label[2] == "CONST")
            {
                errmsg = "Semantic error: Attempt to change a constant value -> line" + std::to_string(i+1) +" of preprocessed AND line "+std::to_string(std::get<0>(this->file_being_assembled[i])+1)+" of original source code.";
                throw errmsg;   
            }
        }
    }
}

void Assembler::secondPass(void)
{
    std::string errmsg;
    for(size_t i = 1; i != this->file_being_assembled.size(); i++ )
    {
        auto line = std::get<1>(this->file_being_assembled[i]);
        
        if (line.size()==1) continue;
        if (line[1] == "DATA") break;

        auto mem_spaces =  this->mem_spaces_MP.at(line[0]);
        
        try
        {
            semanticAnalyzerGeneric(line, i);
            semanticAnalyzerVectors(line, i);
        }
        catch(std::string errmsg)
        {
            throw errmsg;
        }
        
        auto pos_mem1 = this->symbols_table_MP.at(line[1]);

        if (mem_spaces == 2)
        {
            if (line.size() == mem_spaces)
            {    
                std::get<1>(this->file_being_assembled[i])[1] = std::to_string( pos_mem1.first );
            }
            else
            {
                auto temp = pos_mem1.first;
                temp += std::stoi(line[3]);
                std::get<1>(this->file_being_assembled[i])[1] = std::to_string( + std::stoi(line[3]));
            }
        }
        else if (mem_spaces == 3)
        {
            std::get<1>(this->file_being_assembled[i])[1] = std::to_string( (this->symbols_table_MP.at(line[1])).first );
            std::get<1>(this->file_being_assembled[i])[3] = std::to_string( (this->symbols_table_MP.at(line[3])).first );
        }

        printCurrentTupleList();
    }
}

void Assembler::assemble(void)
{
    PreProcessor pre_processor(this->source_code_file);
    this->file_being_assembled = pre_processor.preProcess();
    try{
        firstPass();
        secondPass();
    } catch(std::string errmsg)
    {
        std::cout<<errmsg<<std::endl;
    }
}