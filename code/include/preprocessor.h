#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <tuple>
#include <iomanip>
#include <algorithm>
#include <bits/stdc++.h> 
#define SPECIAL_CHARACTERS ',',':',';','+'

#define MIN_MACRO 3
#define MAXIMUM_AMOUNT_OF_MACRO_ARGUMENTS 3
#define MAX_NUMBER_COMMAS 2
#define MAX_MACRO (MIN_MACRO + MAXIMUM_AMOUNT_OF_MACRO_ARGUMENTS + MAX_NUMBER_COMMAS)
#define MACRO_HAS_PARAMETERS(a) (a>MIN_MACRO)
#define THERE_ARE_MORE_COMMAS(n_tokens) ( ((n_tokens - MIN_MACRO)%2 == 0) && (n_tokens != MIN_MACRO) )

#define ELEMENT_FBP(i, j) std::get<i>(this->file_being_processed[j])


//! Data type, made of a tuple <int, and a vector of strings>
/*!
    This data type helps representing our relevant informations of the source code (words and characters) in the vector of strings
    And also the number of the respective line in the source code as a uint16_t
*/
typedef std::vector< std::tuple<uint16_t, std::vector< std::string>> > TupleList;


typedef std::vector< std::tuple<std::string, std::string> > Table;
typedef std::vector< std::tuple<std::string, uint8_t, uint8_t> > MacroNameTable;

//!  PreProcessor Class. 
/*!
  functions and data structures needed to implement a full working preprocessor for our project
*/
class PreProcessor
{
private:
    //! A private pointer to a file.
    /*! points to the file that contains the source code to be processed. */
    std::fstream* source_code_file;
    
    //! Private atribute,
    /*!the file being processed in our representation.*/
    TupleList file_being_processed;
    
    //! Private atribute,
    /*!Table of equivalences in the source code, labels and values.*/
    Table table_EQU;

    MacroNameTable mnt;
    TupleList mdt;
    //! Private method , receives a pointer to a file.
    /*!
        This method is used to print any file on the console, given its pointer as a parameter
        and returns nothing
    */
    void printFile(std::fstream *);
    
    //! Private method
    /*!
        This method is used to print the source file meant to be processed, on the console, given its pointer as a parameter
        and returns nothing
    */
    void printSourceFile(void);

    //! Private method, receivs a string and a character
    /*!
        This method finds the occurrences of a given char in a string
        returns all the indexes in which this char exists in the original string as a vector of uint16_6
    */
    std::vector<uint16_t> findCharInStringIndexes(std::string, char);
    
    //! Private method, receives a string
    /*!
        This method splits the received strings into many sub-strings between the special characters defined (SPECIAL_CHARACTERS).
        returns all the sub strings as a vector of strings.
    */
    std::vector<std::string> splitString(std::string);

    //! Private method,
    /*!
        This method eliminates all extra spaces and white line from the source code 
        and identifies the special characters, split the words between them.
        This method return a TupleList, our optimized way of representing the source code .
    */
    TupleList removeUselessInfos(void);

    //! Private method, receives TupleList (the file being processed)
    /*!
        This method is used to print the file being processed to the console screen, helps for debugging
    */
    void writePreProcessedFile(void);
    void printTupleListFile(void);
    void printMDT(void);
    void printMNT(void);
    void printTupleTable(Table);
    void removeComments(void);
    bool insertInMacroNameTable(size_t i, size_t position_macro);
    void insertInMacroDefinitionTable(size_t pos, std::vector<std::string>);
    bool swapLinesMacro(size_t line, size_t position_macro);

    Table parseDirectiveEQU(void);
    std::string findInTable(Table, std::string);
    void processEQUs(void);
    void processIFs(void);
    void processMacros(void);

public:
    std::string file_name;
    //! Class constructor, receives a pointer to the source file.
    /*!
        constructs the object and indicates the file to be processed.
    */
    PreProcessor(std::fstream *);
    
    //! Class destructor,
    /*!
        destructs the object guarantees a clean exit for the program.
    */
    ~PreProcessor();
    //! Public method
    /*!
        This method does the preprocessing action from a to z for the defined source code.
    */
    TupleList preProcess(void);
};

#endif /* PREPROCESSOR_H */
