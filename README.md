# Hypothetical-Machine-Assembler
>├── README.md (This file)  
├── /docs  
│ └── Trabalho1.pdf (Specifications of the assembler to be done - in portuguese)   
│ └── test-codes (a directory with some .asm codes for validation)  
├── /code  
| └── /src/  
|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;└── main.cpp (principal code of the project)  
| └── /includes/ (libraries headers directory)  
|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;     └── preprocessor.h (Preprocessor's library header)  
|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;     └── assembler.h (Assembler's library header)  
| └── /lib/ (libraries source code directory)    
|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;     └── preprocessor.cpp (preprocessor's library source code)  
|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;     └── assembler.cpp (Assembler's library source code)  
| └── CMakeLists.txt (Cmake build configurations)    
| └── build.sh (building script)  
| └── build (directory made by the script and is deleted when it's done compiling)      

### __Introduction__:  
#### An assembler of an invented simple assembly language, this language was invented to facilitate the understanding of compilers, interpreters and basic software components.  

### ISA of our hypothetical machine:  
<p align="center">
  <img  src="https://github.com/abdullah-zaiter/Hypothetical-Machine-Assembler/tree/master/docs/SB-repo-instructions.png">
</p>

### Other directives of our hypothetical machine:  
<p align="center">
  <img  src="https://github.com/abdullah-zaiter/Hypothetical-Machine-Assembler/tree/master/docs/Directives-Rep_SB.png">
</p>

### __Requirements__:  
* Any operating system (Linux, Windows, macOS)
* Cmake  - at least version 3

### __Instructions__:
Just run the script _build.sh_
```
>sh build.sh
```
And then run the program with the assembly program you would like to assemble:
```
>./bin/main 'Input-filename'.asm
```
Expected output (if no errors we're found on the original input file):

* 'Input-filename'.pre (the preprocessed file)
* 'Input-filename'.obj (the object binary code of the input file) 

#### Conventions adopted writing the code:  https://gist.github.com/lefticus/10191322