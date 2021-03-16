/*
 * Author: Pablo Sanchez Narro
 * Matriculation number: 40486559
 *
 * Reads a Java file, outputs its data and a file with its comments and methods
*/

#include <stdio.h>
#include <string.h>
 

int error_checker (int status);
int commandLA (char *arg1, char *arg2, char *arg3);
int get_info (char *file);
int line_counter (char* file, int* nofLines, int* nonBlankL);
int comments_counter (char *file, int *nofComments);
int output_file (char *file, char *outFile);


/*Main function*/
int main (int argc, char** argv)
{
	int nofLines, nonBlankL, nofComments;
	int status = 0;
	
	// Command Line Arguments checker
	commandLA(argv[1], argv[3], argv[4]);

	// File to open
	char* file = argv[2];
	
	// File to output
	char *outFile = argv[4];

	// Gets the info of the code
	get_info(file);
	
	// Number of lines
	line_counter(file, &nofLines, &nonBlankL);
	printf("Total number of lines: %d\n", nofLines);
	printf("Number of non-blank lines: %d\n", nonBlankL);
	
	// Number of comments
	comments_counter(file, &nofComments);
	printf("Number of Javadoc comments: %d\n", nofComments);
	
	// Outputs the file
	output_file(file, outFile);
	
	// No errors
	error_checker(status);
	return 0;
}


/*Outputs errors*/
int error_checker (int status)
{
	switch (status)
	{
		case 0:
			return 0;
			break;
			
		case 1:
			printf("\nError: Please, use command line arguments\n");
			exit(1);
			return 1;
			break;
			
		case 2:
			printf("\nError: Please, use '-i' to specify the file you wish to open and '-o' to name the output document. Make sure you use '-i' first!\n");
			exit(1);
			return 1;
			break;
			
		case 3:
			printf("\nError: Cannot find specified file!\n");
			exit(1);
			return 1;
			break;

		case 4:
			printf("\nHow are you going to call the output file?\n");
			exit(1);
			return 1;
			break;			
	}
	
	return 0;
}


/*Checks if command line arguments are correct*/
int commandLA (char *arg1, char *arg2, char *arg3)
{
	int status = 0;
	
	if (arg1 == NULL || arg2 == NULL)	// Forces the user to use command line arguments
	{
		status = 1;
		error_checker(status);
		return 1;		
	}
	else if ((strcmp(arg1,"-i") != 0)  || (strcmp(arg2,"-o") != 0))	// Forces the user to use -i and -o
	{
		status = 2;
		error_checker(status);
		return 1;
	}	
	else if (arg3 == NULL)	// Forces the user to name the output file
	{
		status = 4;
		error_checker(status);
		return 1;		
	}	
	
	return 0;
}


/*Reads the Java code and outouts its info*/
int get_info (char *file)
{
	int status = 0;
	
	// Read the file
	FILE* input;
	input = fopen(file, "r");
	
	// Make sure the input is correct
	if (input == NULL) 
	{
        status = 3;
		error_checker (status);
		return 1;
    }	
	
	
	char code[1000];
	const char tag = '@';
	char *class;
	char *author_line;
	char *author_tag;
	char author[100];
	
	while (fgets (code , 1000 , input) != NULL)
	{		
		// Gets the author name
		author_line = memchr(code, tag, strlen(code));	// Gets the line from the tag onwards
		if(author_line != NULL && strstr(author_line, "author") != NULL)
		{
			author_tag = memchr(author_line, ' ', strlen(author_line));	// Removes the tag character
			strcpy(author, author_tag);	// Stores the author to print it after the class
		}
		
		// Gets the class name
		if(strstr(code, "class") != NULL)
		{
			char *token = strtok(code, "s");			
			token = strtok(NULL, "s");
			class = strtok(token, " ");	// Gets the class
			
			// Outputs class and author
			printf("\nClass: %s\n", class);
			printf("Author:%s", author);
			
		}
		
		
		char *ret_line;
		char ret_tag[100];
		char *par_line;
		char par_tag[100];
		char par_tag2[100];
		
		// Point to the tag character
		ret_line = memchr(code, tag, strlen(code));	
		par_line = memchr(code, tag, strlen(code));

		if(ret_line != NULL && strstr(ret_line, "return") != NULL) // If the line contains 'return'
		{		
			strcpy(ret_tag, ret_line); // Stores the 'return' tag

		} 
		else if(par_line != NULL && strstr(par_line, "param") != NULL) // If the line contains 'param'
		{
			strcpy(par_tag, par_line); // Stores the 'param' tag
			
			if(par_line != NULL && strstr(par_line, "x") != NULL) //Second Paramenter
			{
				strcpy(par_tag2, par_line);
			}
		}
	
	
		char *ret;
		char *par;
		char *par2;	
	
		if(strstr(code, "get") != NULL)
		{
			char *token_g = strtok(code, "e");	// Find 'e' from doubl*e* or g*e*t		
			token_g = strtok(NULL, "");
			char *method_g = strtok(token_g, " ");
			
			if(strstr(method_g, "ge") != NULL)
			{
				printf("\nMethod: %s\n", method_g);		
			}
			else	// If strtok has destroyed the 'ge', add it
			{
				printf("\nMethod: ge%s\n", method_g);				
			}
			
			// Removes the tag character
			ret = memchr(ret_tag, ' ', strlen(ret_tag));
			printf("Returns:%s", ret);
			
		} 
		else if(strstr(code, "set") != NULL)
		{
			char *token_s = strtok(code, "s");	// Find 's' from *s*et		
			token_s = strtok(NULL, "");
			char *method_s = strtok(token_s, " ");
			printf("\nMethod: s%s\n", method_s);	// Strtok destroys the 's' so we have to add it
			
			// Removes the tag character
			par = memchr(par_tag, ' ', strlen(par_tag));
			printf("Paramenter:%s", par);
		}
		else if(strstr(code, "move") != NULL)
		{
			char *token_m = strtok(code, "m");	// Find 'm' from *m*ove
			token_m = strtok(NULL, "");
			char *method_m = strtok(token_m, " ");
			printf("\nMethod: m%s\n", method_m);	// Strtok destroys the 'm' so we have to add it
			
			// Removes the tag character of both parameters
			par2 = memchr(par_tag2, ' ', strlen(par_tag2));
			par = memchr(par_tag, ' ', strlen(par_tag));
			printf("Paramenter:%s", par2);		
			printf("Paramenter:%s", par);		
			
		}
		else if(strstr(code, "toString") != NULL)
		{
			char *token_t = strtok(code, "S");	// Find 'S' from to*S*tring
			token_t = strtok(NULL, "");
			char *method_t = strtok(token_t, " ");
			printf("\nMethod: toS%s\n", method_t);	// Strtok destroys the 'toS' so we have to add it
			
			// Removes the tag character
			ret = memchr(ret_tag, ' ', strlen(ret_tag));
			printf("Returns:%s\n", ret);		
			
		}		
	}

	// Avoid memory leaks	
	fclose(input);

	return 0;	
}


/*Counts total and non blank lines*/
int line_counter (char* file, int* nofLines, int* nonBlankL)
{
	int status = 0;
	
	// Read the file
	FILE* input;
	input = fopen(file, "r");
	
	// Make sure the input is correct
	if (input == NULL) 
	{
        status = 3;
		error_checker(status);
		return 1;
    }	
	
	// To store each line
	char line [1000];
	
	// To store number of lines
	int nl = 0;
	int nonBL = 0;

	while(fgets(line, 1000, input) != NULL) 
	{
		int len = strlen(line);
		nl++;
        for (int i = 0; i < len; i++) 
		{
			// If the line is not blank
			if (line[i] != '\n' && line[i] != '\t' && line[i] != ' ') 
			{
				nonBL++;
				break;
			}
		}
	}

	// To return two values
	*nofLines = nl;
	*nonBlankL = nonBL;
		
	// Avoid memory leaks
	fclose(input);
	error_checker(status);
	return 0;
}

/*Counts total of Java comments*/
int comments_counter(char *file, int *nofComments)
{
	int status = 0;
	
	// Read the file
	FILE* input;
	input = fopen(file, "r");
	
	// Make sure the input is correct
	if (input == NULL) 
	{
        status = 3;
		error_checker(status);
		return 1;
    }	
	
	
	char ch [2000]; // Go through each character of the input file
	int comments = 0;
	int i = 0;
	
	for(int j = i+1; (ch[j]=fgetc(input)) != EOF ; j++)
	{
		if(ch[i] == '/')
		{				
			if(ch[j] == '*') // Comments start with /*
			{
				comments++;					
			}
		}		
		i++;
	}
	

	*nofComments=comments;
	
	// Avoid memory leaks
	fclose(input);
	return 0;
}


/*Outputs a file continging comments and methods*/
int output_file(char *file, char *outFile)
{
	int status = 0;

	// Read the file
	FILE* input;
	input = fopen(file, "r");
	
	// Make sure the input is correct
	if (input == NULL) 
	{
        status = 3;
		error_checker(status);
		return 1;
    }	

	// Write file
	FILE* output;
	output = fopen(outFile, "w");

	char line[2000];


	while(fgets(line, 2000, input) != NULL) 
	{
		int len = strlen(line);
        for (int i = 0; i < len; i++) 
		{
			if (line[i] == ';' || line[i] == '}' || line[i] == '+') // If it's not a comment nor method
			{
				break;
			}
			else if (line[i] == '\n')	// Prints the code into the file
			{
				fprintf(output, line);					
				continue;
			}
		}
	}	
	
	// Avoid memory leaks
	fclose(input);
	fclose(output);
	return 0;
}