USAGE: ./kompilator \<source file\> \<target file\> \n
Message "Mozliwe uzycie niezainicjalizowanej zmiennej [...] w [...]" is not an error, like in any other compiler, its an warning message.
Message "Kompilacja zakonczona niepowodzeniem" means that compilation was not succesful.
My paradigm of this language is that, variables are initialised when they are given as an argument in procedure call, if they are not initialised in call, a warning will be printed.