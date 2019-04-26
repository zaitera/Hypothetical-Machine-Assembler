#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <tuple>
#include <iomanip>
#include <algorithm>
#include <bits/stdc++.h> 
#define SPECIAL_CHARACTERS ',',':','&'

//! Data type, made of a tuple <int, and a vector of strings>
/*!
    This data type helps representing our relevant informations of the source code (words and characters) in the vector of strings
    And also the number of the respective line in the source code as a uint16_t
*/
typedef std::vector< std::tuple<uint16_t, std::vector< std::string> > > tuple_list;

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
        This method return a tuple_list, our optimized way of representing the source code .
    */
    tuple_list removeEmptySpacesAndLines(void);
    void printTupleListFile(tuple_list);
public:
    //! Class constructor, receives a pointer to the source file.
    /*!
        constructs the object and indicates the file to be processed.
    */
    PreProcessor(std::fstream *);
    //! Public method
    /*!
        This method does the preprocessing action from a to z for the defined source code.
    */
    void preProcess(void);
};

#endif /* PREPROCESSOR_H */
