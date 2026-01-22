*This project has been created as part of the 42 curriculum by ansimonn.*

# Content

### 1. [Description](#description)

### 2. [Instructions](#instructions)

### 3. [Ressources](#ressources)

# Description

## Project

This project is about reproducing bash's pipe. It must handle 4 arguments in the following order:

- file1 is the path to the file the program will get it's input from


- cmd1 is the first shell command we want to execute (the left member of the pipe)


- cmd2 is the second shell command we want to execute (the right member of the pipe)


- file2 is the path to the file the program will write it's output to. If it does not already exist, the 
program creates it.

It must work the same way as the shell command 

`$> < file1 cmd1 | cmd2 > file2`

The program must contain a Makefile which compiles all necessary files into a binary named
`pipex`, without any unnecessary relinking. It must not terminate unexpectedly or have memory
leaks too.

## Implementation

I used a C `pipe()` function to redirect the output from cmd1 to the input of cmd2. I also used the
`fork()` function to create a child that is in charge of executing the cmd1 over the content of file1 and put the result
in the entry of the pipe, so that the parent can execute cmd2 directly on the exit of it and write the result in file2.

# Instructions

To compile all the file needed you must use the `make` command. It will create object files directly into the
`obj` folder and compile them to get your `pipex` binary at the root of the project.

From there you only need to execute it by executing the following command:

`$> ./pipex file1 cmd1 cmd2 file2`

Don't forget to put double quotes around your cmd1 and cmd2 if you want to add specifiers, or else the program
will exit without any result.

You can use the `make clean` command to delete all .o files in the obj folder, or the `make fclean` to also
delete the `pipex` binary.

The `make re` command will execute the `make fclean` command, and then recreate every object files and
the `pipex` binary.

# Ressources

I chose not to use AI as i usually do, because i prefer training myself to look for all the informations i need
by by my own, so my references websites are here:

- https://csnotes.medium.com/pipex-tutorial-42-project-4469f5dd5901


- https://www.geeksforgeeks.org/cpp/exit-codes-in-c-c-with-examples/


- https://www.codequoi.com/pipe-une-methode-de-communication-inter-processus/


- https://www.codequoi.com/creer-et-tuer-des-processus-fils-en-c/
