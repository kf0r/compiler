USAGE: ./kompilator \<source file\> \<target file\>   
Message "Mozliwe uzycie niezainicjalizowanej zmiennej [...] w [...]" is not an error. Like in any other compiler, its an warning message.   
Message "Kompilacja zakonczona niepowodzeniem" means that compilation was not succesful.   
My paradigm of this language is that, variables are initialised when they are given as an argument in procedure call, if they are not initialised in call, a warning will be printed.   
    
parser.ypp - main program, parsing and compiling.   
lexer.l - tokenizer    
Architecture.cpp - contains memory and register management functions   
Assembly.cpp - functions creating low level instructions.   
AssemblyAlgebra.cpp - two functions creating division and multiplication blocks.   
Block.cpp - translating AST to basic block representation   
LowLevelProgram.cpp - translation manager, higher level instruction manager.   
ProgramStructure.cpp - semantic analyzer, memory allocator.   
Types.cpp - methods of types classes, so identifiers, expressions etc.   
Vertex.cpp - methods of AST vertex classes, so Instructions and inheriting classes, Instruction linked lists, declarations and procedures.   
Headers contain class and methods definitions.
    
Krzysztof Fornal, 268433