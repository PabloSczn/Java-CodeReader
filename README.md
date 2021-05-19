# CodeReader
Compiled using Visual Studio Command Line (C must be installed in VS).

Toolchain: Visual Studio 2019 Developer Command Prompt v16.8.4

This program uses C to read a Java file, output its information (methods, author, returns) and a file with its comments and methods


To run the program, write nmake on the console.

Makefile targets:

	CodeReader -> Compile CodeReader.c 

	clean -> Remove all objects, executables and texts files


The arguments that can be used are:


-i <filename.java>	to specify the Java doc to open.

-o <filename>	to specify the name of the output file.
	

Two Java files are included for example purposes
