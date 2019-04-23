#include <preprocessor.h>


PreProcessor::PreProcessor(std::fstream *source)
{
    this->source_code_file = source;
}

void PreProcessor::printSourceFile(void)
{
    PreProcessor::printFile(this->source_code_file);
}

void PreProcessor::printFile(std::fstream *source)
{
    std::string line;
    while (*(source) >> line) {
        std::cout << line << std::endl;
    }
    source->clear();
    source->seekg( 0, source->beg);
    source->seekp( 0, source->beg);
}



tuple_list  PreProcessor::removeEmptySpacesAndLines(void)
{ 
    std::string text_line, word;
    std::vector <std::string> sentence;
    std::tuple<uint16_t,std::vector <std::string>> current_tuple;
    std::string aux;
    tuple_list file_tuple;
    uint16_t line_cont = 0;
    while (std::getline(*(this->source_code_file), text_line))
    {
        std::istringstream text_stream(text_line);
        while (text_stream >> word)
        {
            std::transform(word.begin(), word.end(),word.begin(), ::toupper);
            if (word.back() == ',' || word.back() == ':')
            {
                aux = word.back();
                word.erase(word.end()-1);
                if(!(word.empty()))
                {
                    sentence.push_back(word);
                }
                sentence.push_back(aux);
            }
            else if (word[0] == ',' || word[0] == ':')
            {
                aux = word[0];
                sentence.push_back(aux);
                word.erase(word.begin());
                sentence.push_back(word);
            }
            else
            {
                sentence.push_back(word);
            }
        }
        if(!(text_line.empty()))
        {
            current_tuple = make_tuple(line_cont,sentence); 
            file_tuple.push_back(current_tuple);
            sentence.clear();
        }
        line_cont++;
    }
    return file_tuple;
}

void PreProcessor::printTupleListFile(tuple_list tuple_file)
{
    for(uint16_t i = 0; i != tuple_file.size(); i++ )
    {
        std::cout << std::setfill('0') << std::setw(3) << std::get<0>(tuple_file[i])+1 << " ";
        for(uint16_t j = 0; j != std::get<1>(tuple_file[i]).size(); j++ )
            std::cout << std::get<1>(tuple_file[i])[j] << " ";
        std::cout << std::endl;
    } 
}

void PreProcessor::preProcess(void)
{
    printTupleListFile(removeEmptySpacesAndLines());
}