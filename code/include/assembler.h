#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include <preprocessor.h>

enum TokenType{
    spchar = 0,
    inst = 1,
    label = 2,
    memparameter = 3,
    constval = 4,
    datdirective =5
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
    const std::map<std::string, uint8_t> inst_opcodes_MP = {
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
    const std::map<std::string, uint8_t> mem_spaces_MP = {
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
    };   
    std::map<std::string, std::pair<uint16_t,uint16_t>> symbols_table_MP;
    
    void spcharLexicalAnalysis(std::string special_char);
    void memoryParamLexicalAnalysis(std::string memparam);
    void constValLexicalAnalysis(std::string instruction);
    void dataDirectiveLexicalAnalysis(std::string);
    void instLexicalAnalysis(std::string instruction);
    void labelLexicalAnalysis(std::string label);
    void instructionSintax(std::vector<std::string> aux);
    void lexicalAnalyzer(std::string, TokenType);
    bool isParametersNumberValid(uint16_t, uint16_t );
    void firstPass(void);
    uint16_t labelAnalysis(std::vector<std::string>,uint16_t, uint16_t);
    Section sectionAnalysis(std::string);

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