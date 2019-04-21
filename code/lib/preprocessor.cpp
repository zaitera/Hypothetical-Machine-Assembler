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
    std::string text_line, word, line_to_tuple;
    std::tuple<uint16_t,std::string> current_tuple;
    tuple_list file_tuple;
    uint16_t line_cont = 0;
    while (std::getline(*(this->source_code_file), text_line))
    {
        std::istringstream text_stream(text_line);
        while (text_stream >> word)
        {
            line_to_tuple.append(word);
            line_to_tuple.append(" ");
            std::transform(line_to_tuple.begin(), line_to_tuple.end(),line_to_tuple.begin(), ::toupper);
        }
        if(!(text_line.empty()))
        {
            current_tuple = make_tuple(line_cont,line_to_tuple); 
            line_cont++;
            file_tuple.push_back(current_tuple);
            line_to_tuple.clear();
        }
    }
    return file_tuple;
}
void PreProcessor::printTupleListFile(tuple_list tuple_file)
{
    for(uint16_t i = 0; i != tuple_file.size(); i++ )
    {
        std::cout << std::setfill('0') << std::setw(3) << std::get<0>(tuple_file[i])+1 << " " <<std::get<1>(tuple_file[i]) << std::endl;
    } 
}

void PreProcessor::preProcess(void)
{
    printTupleListFile(removeEmptySpacesAndLines());
}