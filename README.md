# SimpleShellDemo
#COSC 4302 Group Project Shell

Written by Johnny Do and Carlos Del Valle

#Description

The purpose of this project is to write a simple shell program in C language and execute the shell program to run the commands in a Linux OS.

To compile the shell program, type gcc -o compiler2.c compiler2 in your terminal.

If you want to compile3.c, then type gcc -pthread -o compile3_2 compiler3.c and this here is for part 2.

This shell program shows the use of fork() and execv() of how it execute from our simple shell program compile2.c We know that fork() will create the child command from the parent and the execv() will execute the child process. The parent will have to wait until the child process is terminated. While the shell program is compiled, it should print 'myShell$'. Once it's show it, you can now put a command. To exit the shell, type exit. You also can use ctrl+z to exit the shell. We setup the PATH to parse the arguments and check to see if the command exists. If the setPATH() == -1, it will print an error. Then it will go an infinite loop to clear all buffers. The program skip spaces and check if there are arguments or new line character. If it is, we continue. If the command exists, it will execute. Now it will create a child process and parent process using fork().
