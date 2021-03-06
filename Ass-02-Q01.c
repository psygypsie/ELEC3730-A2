/**
 * File: Ass-02-Q01.c
 * 
 * @author Thomas Courtney - c3175353
 * @author Jeremiah Smith - c3238179
 * @since 03-05-2019
 */
#include "Ass-02.h"
#include <ctype.h>
#include <stdlib.h>
#ifdef STM32F407xx
#include <usart.h>
#endif

#define MAX_STR_LEN 100		// Maximum characters in the input string
#define CR 13			// Carriage return character
#define NL 0x0a         	//New Line Feed

void serial_string_parser(char**,int*);
int string_parser(char *inp, char **array_of_words_p[]);
static int inputLen = 0;	//The number of characters that have been read in from terminal.

void CommandLineParserInit (void)
{

	printf ("\n");
	printf ("%s\n", ASS_STRING);
	printf ("%s\n", VER_STRING);
	printf ("Command Line Parser Example EDITED\n");
	printf("> ");
}
//
//int main()
//{
//	while(1)
//	CommandLineParserProcess();
//}

/*
 * Check for input and echo back
 * This function operates the command line calculator process on the Windows
 * command line as well as the Putty interface
 *
 * @Params
 * void
 *
 * @Returns
 * void
 */
void CommandLineParserProcess ()
{
	int error = 0;		// indicates whether or not an error has been detected
	char c;			// holds current char read in from the command line
	int i;
	static char command_line[MAX_STR_LEN + 1];
	char **array_of_words;	// holds the array of words entered in from the command line from beginning to carriage return
	int count;		// a count of the number of words
	int debug = 0;		// signals whether debug is on or off


#ifdef STM32F407xx

	int flag = 0; 			//This flag is for saying if a character has been read in.
	int endInputFlag = 0;		//Indicates if the input has completed being read in.

	if (HAL_UART_Receive (&huart2, &c, 1, 0x0) == HAL_OK){
		// Get one line of input


		//If this is true then a character has been read in.
		flag = 1;
		if((c!= CR) && inputLen < MAX_STR_LEN){
			command_line[inputLen] = c;			//Add char to input string.
			inputLen++;					//Increment for position of next character.
		}else{
			printf("\n");
			endInputFlag = 1;				//CR read in so input complete.
		}
		printf("%c", c);					//Print what happened to the terminal.

	}

	if(endInputFlag)
	{		//If the whole string is read in.

			command_line[inputLen] = '\0'; //Set's last char as null.

			// Parse the input and print result
			count = string_parser(command_line, &array_of_words);

			// ~~~ operations: result calculated below
			float result = 0;

			// loop over input words
			for (int i = 0; i < count; i++)
			{

				// result starts as first number entered
				if (i == 1){
					result = strtof(array_of_words[1], NULL);
				}

				/*  add <num 1> .. <num N> Sum one or more numbers. */
				else if (strcmp(array_of_words[0], "add") == 0)
					result += strtof(array_of_words[i], NULL);
				/* sub <num 1> <num 2> Subtract two numbers. */
				else if (strcmp(array_of_words[0], "sub") == 0)
					result -= strtof(array_of_words[i], NULL);
				/* mul <num 1> .. <num N> Multiply one or more numbers. */
				else if (strcmp(array_of_words[0], "mul") == 0)
					result *= strtof(array_of_words[i], NULL);
				/* div <num 1> <num 2> Divide two numbers.*/
				else if (strcmp(array_of_words[0], "div") == 0)
					result /= strtof(array_of_words[i], NULL);

				/* debug <on|off> Turn debug messages on or off. */
				else if (strcmp(array_of_words[0], "debug") == 0)
				{
					if (count == 1)
					{
							printf("Debug messages are off\n");
						if (debug == 1)
							printf("Debug messages are on\n");
						return;
					}
					else if (strcmp(array_of_words[1], "on") == 0)
					{
						debug = 1;
						printf("Debug messages will now be displayed\n");
					}
					else if (strcmp(array_of_words[1], "off") == 0)
					{
						debug = 0;
						printf("Debug messages will not be displayed\n");
					}
					else if (debug == 1)
						printf("Error: Debug commands include 'debug on', 'debug off' and 'debug' (to see the debug status)\n");
					return;
				}
				/* help [<command>] Display help messages.*   d) */
				else if (strcmp(array_of_words[0], "help") == 0)
				{
					// prints help messages for all commands
					if (count == 1)
					{

						printf("add - Performs an addition operation on the succeeding numbers\n");
						printf("sub - Performs a subtraction operation on the succeeding numbers\n");
						printf("mul - Performs a multiplication operation on the succeeding numbers\n");
						printf("div - Performs a division operation on the succeeding numbers\n");
						printf("debug - Enter 'debug on' for debugging messages and 'debug off' for no debugging messages\n");
						return;
					}
					else if (strcmp(array_of_words[1], "add") == 0)
						printf("Performs an addition operation on the succeeding numbers\n");
					else if (strcmp(array_of_words[1], "sub") == 0)
						printf("Performs a subtraction operation on the succeeding numbers\n");
					else if (strcmp(array_of_words[1], "mul") == 0)
						printf("Performs a multiplication operation on the succeeding numbers\n");
					else if (strcmp(array_of_words[1], "div") == 0)
						printf("Performs a division operation on the succeeding numbers\n");
					else if (strcmp(array_of_words[1], "debug") == 0)
						printf("Enter 'debug on' for debugging messages and 'debug off' for no debugging messages\n");
					else if (debug == 1)
						printf("No help for '%s'", array_of_words[1]);
					return;
				}
				// invalid command
				else if (debug == 1)
				{
					printf("'%s' is an invalid command, type command 'help' to see a list of available commands\n", array_of_words[0]);
					return;
				}

			if (debug == 1 && i >= 1)
				for (int a = 0; a < strlen(array_of_words[i]); a++)
				{
					if (!isdigit(array_of_words[i][a]))
					{
						printf("Please enter numbers after a calculator operation to see valid results\n");
						error = 1;
						return;
					}
				}
		}

			if (error == 0)

				printf("Result : %g\n\n", result);
				printf("> ");
				inputLen = 0;
			if (count != 0) {
				free(array_of_words[0]);
				free(array_of_words);
			}

	}
#else
	c = getchar();	//Moved to here so that getChar() only happens in windows.
	while (c != '\n' && i < MAX_STR_LEN) {
		command_line[i] = c;
		i++;
		c = getchar();
	}

	command_line[i] = 0;

	// Parse the input and print result
	count = string_parser(command_line, &array_of_words);

	// ~~~ operations
	float result = 0;

	// loop over input words
	for (int i = 0; i < count; i++)
	{

		// result starts as first number entered
		if (i == 1)
			result = strtof(array_of_words[1], NULL);


		/*  add <num 1> .. <num N> Sum one or more numbers. */
		else if (strcmp(array_of_words[0], "add") == 0)
			result += strtof(array_of_words[i], NULL);
		/* sub <num 1> <num 2> Subtract two numbers. */
		else if (strcmp(array_of_words[0], "sub") == 0)
			result -= strtof(array_of_words[i], NULL);
		/* mul <num 1> .. <num N> Multiply one or more numbers. */
		else if (strcmp(array_of_words[0], "mul") == 0)
			result *= strtof(array_of_words[i], NULL);
		/* div <num 1> <num 2> Divide two numbers.*/
		else if (strcmp(array_of_words[0], "div") == 0)
			result /= strtof(array_of_words[i], NULL);

		/* debug <on|off> Turn debug messages on or off. */
		else if (strcmp(array_of_words[0], "debug") == 0)
		{
			if (count == 1)
			{
				if (debug == 0)
					printf("Debug messages are off\n");
				if (debug == 1)
					printf("Debug messages are on\n");
				return;
			}
			else if (strcmp(array_of_words[1], "on") == 0)
			{
				debug = 1;
				printf("Debug messages will now be displayed\n");
			}
			else if (strcmp(array_of_words[1], "off") == 0)
			{
				debug = 0;
				printf("Debug messages will not be displayed\n");
			}
			else if (debug == 1)
				printf("Error: Debug commands include 'debug on', 'debug off' and 'debug' (to see the debug status)\n");
			return;
		}
		/* help [<command>] Display help messages.*   d) */
		else if (strcmp(array_of_words[0], "help") == 0)
		{
			// prints help messages for all commands
			if (count == 1)
			{

				printf("add - Performs an addition operation on the succeeding numbers\n");
				printf("sub - Performs a subtraction operation on the succeeding numbers\n");
				printf("mul - Performs a multiplication operation on the succeeding numbers\n");
				printf("div - Performs a division operation on the succeeding numbers\n");
				printf("debug - Enter 'debug on' for debugging messages and 'debug off' for no debugging messages\n");
				return;
			}
			else if (strcmp(array_of_words[1], "add") == 0)
				printf("Performs an addition operation on the succeeding numbers\n");
			else if (strcmp(array_of_words[1], "sub") == 0)
				printf("Performs a subtraction operation on the succeeding numbers\n");
			else if (strcmp(array_of_words[1], "mul") == 0)
				printf("Performs a multiplication operation on the succeeding numbers\n");
			else if (strcmp(array_of_words[1], "div") == 0)
				printf("Performs a division operation on the succeeding numbers\n");
			else if (strcmp(array_of_words[1], "debug") == 0)
				printf("Enter 'debug on' for debugging messages and 'debug off' for no debugging messages\n");
			else if (debug == 1)
				printf("No help for '%s'", array_of_words[1]);
			return;
		}
		// invalid command
		else if (debug == 1)
		{
			printf("'%s' is an invalid command, type command 'help' to see a list of available commands\n", array_of_words[0]);
			return;
		}

	if (debug == 1 && i >= 1)
		for (int a = 0; a < strlen(array_of_words[i]); a++)
		{
			if (!isdigit(array_of_words[i][a]))
			{
				printf("Please enter numbers after a calculator operation to see valid results\n");
				error = 1;
				return;
			}
		}
}

	if (error == 0)
		printf("Result : %g\n\n", result);

	if (count != 0) {
		free(array_of_words[0]);
		free(array_of_words);
	}

#endif
}

/* This function is Q5 of A1 */
void serial_string_parser(char** array_of_words, int* count) {
	char c;
	int i, j;
	char command_line[MAX_STR_LEN + 1];

	// Get one line of input
	printf("\n\nEnter text:\n");
	i = 0;
	c = getchar();
	while (c != CR && i < MAX_STR_LEN) {
		printf("%c", c);
		if (c < ' ')
			printf("[0x%02x]", c);
		command_line[i] = c;
		i++;
		c = getchar();
	}
	command_line[i] = 0;

	// Parse the input and print result
	*count = string_parser(command_line, &array_of_words);						//This will handle all of the actual parsing.
	printf("\n\nCount    : %d\n", *count);	/* COUNT IS NOT COMING BACK CORRECTLY */
	for (j = 0; j < *count; j++) {
		printf("Word(%d)  : %s\n", j + 1, (array_of_words)[j]);
	}
	if (*count != 0) {
		free(array_of_words[0]);
		free(array_of_words);
	}
}


/* These functiond are from Q4 of A1 */

/*
 * Gets the size of the contents of a char pointer.
 * The function will only be used in this file and so is static.
 *
 * @Params:
 *
 *  char* s - input pointer whose contents are the subject of the function.
 *
 *
 * @Returns:
 *
 *  int - this is the size of the pointer's subject in bytes.
 *
 *
 */
static int getSize(char *s){

	char* t;                        //This pointer will move through the input input pointer's contents.
	for(t = s; *t !='\0'; t++){}    //Moves the t through contents of s until it NULL terminator
	return t - s;                   //The difference in address between two pointers is the size of s. s points to beggining and t points to the end.
}
/*
 * Find the number of "words" in an series of characters based on a delimiter.
 *
 * @Params:
 *
 *  char* s - input pointer whose contents are the subject of the function.
 *  char delim - a delimiter that determines what is a word and what isn't.
 *               This parameter can be passed by value as it is not modified
 *               by the function.
 *
 * @Returns:
 *
 *  int - the number of words in the series of characters.
 *
 *
 */
static int getNumWords(char *s, char delim){

	char* t;                                  //This pointer will move through the input input pointer's contents.
	char tPrev;
	int wordCount = 0;
	int flag1 = 0;
	int flag2 = 0;                      //Flags for determining if word is present.



	for(t = s+1; *t !='\0'; t++){             //Loop begins at second character.

		tPrev = *(t-1);                         //Hold previous character.

		if((*t != delim && tPrev == delim) || (t == (s+1) && tPrev != delim)){     //Check if the beginning of word has been found.
			flag1 = 1;
		}
		if((tPrev != delim && *t == delim) || ((t-s) == (getSize(s)-1) && *t != delim)){//Check if the end of word has been found.
			flag2 = 1;
		}


		if(flag1 && flag2){                     //If both flags set a whole word has been found!
			wordCount++;
			flag1 = 0;                            //Reset the flags.
			flag2 = 0;
		}

	}
	return wordCount;


}
/*
 * Given a delimiter terminated word determines the number of characters in the word.
 *
 * @Params
 *  char* word - target of the character count.
 *  char delim - the character indicating the end of the word.
 *
 * @Returns
 *  int - the number of characters in the word.
 */
static int getWordCharCount(char* word, char delim){
	int numChar = 0;
	int i = 0;

	while(*(word+i) != delim){
		numChar++;
		i++;
	}


	return numChar;
}
/*
 * Break ups a string by a delimiter (currently a space " "). Will be modified later to include a delimiter parameter (dynamic for later assignments).
 *
 * @Params:
 *
 *  char* inp - the input data to be parsed.
 *  char** array_of_words_p[] - pointer to a pointer to an array of char. (Which is also an array of pointers?) Will be updated to hold the words in
 *                              in the char* input as determined by the delimiter.
 *
 * @Returns:
 *
 *  int - the number of words in the input char* as determined by the delimiter.
 */
int string_parser(char *inp, char **array_of_words_p[]) {

	int sizeOfInput = getSize(inp);
	int wordsInInput = getNumWords(inp, ' ');
	int count = wordsInInput;

	if(wordsInInput == 0 || sizeOfInput == 0) return 0;

	*array_of_words_p = (char**)malloc(sizeof(char*) * wordsInInput);
	wordsInInput = 0;
	char* carrier;      //Points to characters in the input.
	int numChar = 0;


	for(int i = 0; i < sizeOfInput; i++){
		carrier = inp + i;
		if(*(carrier) != ' '){
			numChar = getWordCharCount((carrier), ' ');
			(*array_of_words_p)[wordsInInput] = (char*)malloc(sizeof(char)*(numChar+1));
			i+= numChar;
			wordsInInput++;
			numChar = 0;
		}
	}

	wordsInInput = 0;
	numChar = 0;


	for(int i = 0; i < sizeOfInput; i++){
		carrier = inp + i;
		if(*(carrier) != ' '){                                          //If delimiter reached stop writing word to array.
			(*array_of_words_p)[wordsInInput][numChar] = *(carrier);
			numChar++;
		}

		if(*(carrier) == ' ' && i!=0){                                  //If end of word reached and it's no beginning of input.
			if(*(carrier - 1) != ' '){                                    //If previous character was not delim, then a new word has been logged.
				(*array_of_words_p)[wordsInInput][numChar] = '\0';          //Append NULL to end of string to terminate word.
				wordsInInput++;                                             //Count the word.
			}

			numChar = 0;                                                  //Reset numbe rof characters.
		}

		if(i == (sizeOfInput - 1) && *(carrier) != ' '){                //If end of input reached and last character is not delim then append the NULL.
			(*array_of_words_p)[wordsInInput][numChar] = '\0';            //Append NULL to end of string to terminate word.
		}
	}


	/* return getNumWords(inp,' '); */
	return count;
}
