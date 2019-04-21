#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <tuple>
#include <iomanip>
#include <algorithm>

typedef std::vector< std::tuple<uint16_t, std::vector< std::string> > > tuple_list;

class PreProcessor
{
private:
    std::fstream* source_code_file;
    void printFile(std::fstream *);
public:
    PreProcessor(std::fstream *);
    tuple_list removeEmptySpacesAndLines(void);
    void printSourceFile(void);
    void preProcess(void);
    void printTupleListFile(tuple_list);
};

#endif /* PREPROCESSOR_H */
