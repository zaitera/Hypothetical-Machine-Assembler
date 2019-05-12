#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include <preprocessor.h>

enum TokenType{
    spchar = 0,
    inst = 1,
    label = 2,
    memparameter = 3,
    constval = 4
};

enum Section
{
    UNDEFINED = 0,
    TEXT,
    DATA,
};
class Assembler
{
private:
    //! A private pointer to a file.
    /*! points to the file that contains the source code to be processed. */
    std::fstream* source_code_file;
    
    //! Private atribute,
    /*!the file being assembled in our representation.*/
    TupleList file_being_assembled;
    const std::map<std::string, uint8_t> instOpcodesMP = {
        {"ADD", 1},
        {"SUB", 2},
        {"MULT", 3},
        {"DIV", 4},
        {"JMP", 5},
        {"JMPN", 6},
        {"JMPP", 7},
        {"JMPZ", 8},
        {"COPY", 9},
        {"LOAD", 10},
        {"STORE", 11},
        {"INPUT", 12},
        {"OUTPUT", 13},
        {"STOP", 14}
    };
    const std::map<std::string, uint8_t> memSpacesMP = {
        {"ADD", 2},
        {"SUB", 2},
        {"MULT", 2},
        {"DIV", 2},
        {"JMP", 2},
        {"JMPN", 2},
        {"JMPP", 2},
        {"JMPZ", 2},
        {"COPY", 3},
        {"LOAD", 2},
        {"STORE", 2},
        {"INPUT", 2},
        {"OUTPUT", 2},
        {"STOP", 1},
        {"PUBLIC", 0}
    };   
    std::map<std::string, uint16_t> symbolsTableMP;
    
    void spcharLexicalAnalysis(std::string special_char);
    void memoryParamLexicalAnalysis(std::string memparam);
    void constValLexicalAnalysis(std::string instruction);
    void instLexicalAnalysis(std::string instruction);
    void labelLexicalAnalysis(std::string label);
    void instructionSintax(std::vector<std::string> aux);
    void lexicalAnalyzer(std::string, TokenType);
    uint8_t countWords(std::vector<std::string> sentence);
    void firstPass(void);
    void labelAnalysis(std::vector<std::string> line, uint16_t line_num_pre, uint16_t line_num_orig, uint16_t mem_pos );
    Section sectionAnalysis(std::string str,uint16_t line_num_pre, uint16_t line_num_orig);

public:
    //! Class constructor, receives a pointer to the source file.
    /*!
        constructs the object and indicates the file to be processed.
    */
    Assembler(std::fstream *);

    //! Class destructor,
    /*!
        destructs the object guarantees a clean exit for the program.
    */
    ~Assembler();

    //! Public method
    /*!
        This method does the preprocessing action from a to z for the defined source code.
    */
    void assemble(void);
};

#endif /* ASSEMBLER_H */