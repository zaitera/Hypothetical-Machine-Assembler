#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include <preprocessor.h>

class Assembler
{
private:
    //! A private pointer to a file.
    /*! points to the file that contains the source code to be processed. */
    std::fstream* source_code_file;
    
    //! Private atribute,
    /*!the file being assembled in our representation.*/
    TupleList file_being_assembled;

    void lexicalAnalyzer(std::string);
    void testLexicalAnalyzer(void);   
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