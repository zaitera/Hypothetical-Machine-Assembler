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

std::vector<uint16_t> PreProcessor::findCharInStringIndexes(std::string sample, char character_to_find)
{
    std::vector<uint16_t> character_indexes;
    for(uint16_t i =0; i < sample.size(); i++)
    {
        if(sample[i] == character_to_find)
        {  
            character_indexes.push_back(i);
        }
    }
    return character_indexes;
}

std::vector<std::string> PreProcessor::splitString(std::string word)
{
    std::vector<std::string> splitted_words;
    std::vector<char> special_characters{SPECIAL_CHARACTERS};
    std::vector<uint16_t> splitting_indexes;
    splitting_indexes.push_back(0);
    for(uint16_t i = 0 ; i<=special_characters.size(); i++)
    {
        auto aux = findCharInStringIndexes(word,special_characters[i]);
        splitting_indexes.insert(splitting_indexes.end(),aux.begin(),aux.end());
    }
    std::sort(splitting_indexes.begin(), splitting_indexes.end());
    uint16_t last_index = 0;
    for (uint16_t i = 1; i < splitting_indexes.size(); i++)
    {
        auto aux = word.substr(last_index,splitting_indexes[i]-last_index);
        //adding the word with no special characters
        if(!(aux.empty()))
        {
            splitted_words.push_back(aux);
        }
        ///adding the special character found IF NOT EMPTY
        if(!(std::string(1,word[splitting_indexes[i]]).empty()))
        {
            splitted_words.push_back(std::string(1,word[splitting_indexes[i]]));
        }
        last_index = splitting_indexes[i]+1;
    }
    //this condition treats the cases where a word starts with a special character, pushes the rest of the string as a word to the splitted words
    if((splitting_indexes.back()) != (word.length()-1) && splitting_indexes.size() > 1)
    {
        auto aux = word.substr(splitting_indexes.back()+1,word.length()-1-splitting_indexes.back());
        splitted_words.push_back(aux);
    }
    //this condition treats the case where theres no any special characters in the string
    if(splitting_indexes.size() == 1 && splitting_indexes[0] == 0 )
    {
        splitted_words.push_back(word);
    }

    return splitted_words;
}

tuple_list  PreProcessor::removeEmptySpacesAndLines(void)
{ 
    std::string text_line, word;
    std::vector <std::string> sentence;
    std::tuple<uint16_t,std::vector <std::string>> current_tuple;
    tuple_list file_tuple;
    uint16_t line_cont = 0;
    while (std::getline(*(this->source_code_file), text_line))
    {
        std::istringstream text_stream(text_line);
        while (text_stream >> word)
        {
            std::transform(word.begin(), word.end(),word.begin(), ::toupper);
            auto aux = splitString(word);
            if(!(text_line.empty()))
            {
                sentence.insert(sentence.end(),aux.begin(),aux.end());
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
    for(size_t i = 0; i != tuple_file.size(); i++ )
    {
        std::cout << std::setfill('0') << std::setw(3) << std::get<0>(tuple_file[i])+1 << " ";
        for(size_t j = 0; j != std::get<1>(tuple_file[i]).size(); j++ )
            std::cout << std::get<1>(tuple_file[i])[j] << " ";
        std::cout << std::endl;
    } 
}

void PreProcessor::preProcess(void)
{
    tuple_list file = removeEmptySpacesAndLines(); 
    printTupleListFile(file);
}