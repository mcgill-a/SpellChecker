#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Alex McGill - 40276245
// Date of last modification: 25/02/2017

// The purpose of this program is to spell check words
// from an input file or the command prompt and output
// incorrectly spelt words to a file or the command prompt.

// This function loads in the dictionary file and adds each word into an array called dict
//- dict			an array of strings that stores each word from the dictionary file
//- sizeOfDict 		stores the number of array elements
//- longestWord 	stores the longest word in the dictionary
void loadDictionary(char** dict, int *sizeOfDict, int *longestWord)
{
	FILE *input;
	char buffer[1000];
	int counter = 0;
	int length = 0;
	*sizeOfDict = 0;
	int i = 0;
	input = fopen("dictionary.txt", "r");
	if(input != NULL)
	{
		while(fgets(buffer,1000, input)!=NULL)
		{
			counter++;
			length = strlen(buffer);
			if(length > *longestWord)
			{
				*longestWord = length;
			}
		}
		*sizeOfDict = counter;
		rewind(input);
		while(fgets(buffer,1000, input)!=NULL)
		{
			char temp[1000];
			strcpy(temp, buffer);
			dict[i] = malloc((strlen(temp) + 1) * sizeof(char));
			// If there is a new line character at the end, remove it
			if(temp[(strlen(temp) - 1)] == '\n')
			{
				temp[(strlen(temp) -1)] = '\0';
			}
			strcpy(dict[i], temp);
			i++;
		}
		fclose(input);			
	}
	else
	{
		printf("Failed to load dictionary\n");
		exit(0);
		
	}
}

// This function takes the arguments input from the command prompt
// and sets the file input, file output, ignore case and adds words to an array
//- argc			the number of strings (arguments) entered
//- argv			an array of strings entered in the command prompt
//- fileIn 			stores the name of the input file
//- fileOut 		stores the name of the output file
//- argStrings		stores the actual words from the arguments in the array
//- numOfArgStrings	stores the number of words in argStrings
//- inputExists		0 = there is no input file,		1 = there is an input file
//- outputExists	0 = there is no output file,	1 = there is an output file
//- ignoreCase		0 = should not ignore case, 	1 = should ignore case
void getArgs (int argc, char **argv, char **fileIn, char **fileOut, char **argStrings, int *numOfArgStrings, int *inputExists, int *outputExists, int *ignoreCase)
{
	*fileIn[100];
	int x = 0;
	for(int i = 1; i < argc; i++)
	{
		// if the current argument is -i
		if (strcmp(argv[i], "-i") == 0)
		{
			// and the next argument exists
			if(argv[i+1] != NULL)
			{
				// set the file input name to the next argument
				*fileIn = argv[i+1];
				*inputExists = 1;
			}
			i++;
		}
		// if the current argument is -o
		else if (strcmp(argv[i], "-o") == 0)
		{
			// and the next argument exists
			if(argv[i+1] != NULL)
			{
				// set the file output name to the next argument
				*fileOut = argv[i+1];
				*outputExists = 1;
			}
			i++;
			
		}
		// if the current argument is -c
		else if (strcmp(argv[i], "-c") == 0)
		{
			*ignoreCase = 1;
		}
		// if the current argument is /help
		else if (strcmp(argv[i], "/help") == 0)
		{
			printf("Usage:\n");
			printf("\tspell [options]\n");
			printf("\t-i -- Input file name\n");
			printf("\t-o -- Output file name\n");
			printf("\t-c -- Ignore character case\n\n");
		}
		// otherwise, add the argument to the list of strings
		else
		{
			// Allocate enough memory to store the string in the array
			argStrings[x] = malloc((strlen(argv[i]) + 1) * sizeof(char*));
			strcpy(argStrings[x], argv[i]);
			x++;
		}
	}
	*numOfArgStrings = x;	
}

// This function gets the user file, reads in the data line per line
// then adds the words from each line into an array
//- lines			an array of strings that stores entire lines individually
//- numOfLines		stores the number of lines in the array
//- words			an array of strings that stores individual words from each line
//- longestWord 	stores the longest word in the dictionary
//- numOfWords		stores the number of words in the array words
//- wordLines		stores the each words line number
void getUserFile(char **lines, int *numOfLines, char **fileIn, char **words, int *longestWord, int *numOfWords, int *wordLines)
{
	char buffer[1000];
	int counter = 0;
	int length = 0;
	*numOfLines = 0;
	int i = 0;

	FILE *userFile;
	int check = 0;
	// Check to see if there is a file name and if that file exists
	if((*fileIn != NULL) && (userFile = fopen(*fileIn, "r")))
	{
		check = 1;
	}

	if((check == 1) && (userFile != NULL))
	{
		int index = 0;
		// While the buffer from the input is not empty
		while(fgets(buffer,1000, userFile) !=NULL)
		{
			char temp[1000];
			strcpy(temp, buffer);
			{
				// Allocate enough memory to store the string in the array
				lines[index] = malloc((strlen(temp) + 1) * sizeof(char));
				// If there is a new line character at the end, remove it
				if(temp[(strlen(temp) - 1)] == '\n')
				{
					temp[(strlen(temp) -1)] = '\0';
				}
				strcpy(lines[index], temp);
				index++;
			}
		}
		fclose(userFile);
		*numOfLines = index;

		int x = 0;
		for(int j = 0; j < index; j++)
		{
			char temp[1000];
			strcpy(temp, lines[j]);
			char *word;
			if(temp[0] != '\n' || temp[0] != '\0')
			{
				// Set word to the token between the delimiters
				word = strtok (temp," ,.-?!;");
				// while word isn't empty or a newline character
				while ((word != NULL) && (word[0] != '\n'))
				{
					// Allocate enough memory to store the string in the array
					words[x] = malloc((*longestWord + 1) * sizeof(char));
					// If there is a new line character at the end, remove it
					if(word[(strlen(word) - 1)] == '\n')
					{
						word[(strlen(word) -1)] = '\0';
					}
					strcpy(words[x], word);
					// Line number is j+1 because actual lines start with a 1 not 0
					wordLines[x] = j+1;
					// Set word to the token between the delimiters
					word = strtok (NULL, " ,.-?!;");
					x++;
				}
			}
			
		}
		*numOfWords = x;		
	}
	else
	{
		printf("The file does not exist, please try again..\n");
	}
}

// This function takes argStrings and checks that they are actual words,
// if the string is then it puts the word into an array called words
//- words			an array of strings that stores individual words from each line
//- numOfArgStrings	stores the number of words in argStrings
//- longestWord 	stores the longest word in the dictionary
//- numOfWords		stores the number of words in the array words
void getArgWords(char ** argStrings, char **words, int *numOfArgStrings, int *longestWord, int *numOfWords)
{
	int x = 0;
	for(int i = 0; i < *numOfArgStrings; i++)
	{
		char temp[100];
		strcpy(temp, argStrings[i]);
		char *word;
		if(temp[0] != '\n' || temp[0] != '\0')
		{
			// Set word to the token between the delimiters
			word = strtok (temp," ,.-?!;");
			// while word isn't empty or a newline character
			while ((word != NULL) && (word[0] != '\n'))
			{
				// Allocate enough memory to store the string in the array
				words[x] = malloc((*longestWord + 1) * sizeof(char));
				// If there is a new line character at the end, remove it
				if(word[(strlen(word) - 1)] == '\n')
				{
					word[(strlen(word) -1)] = '\0';
				}
				strcpy(words[x], word);
				// Set word to the token between the delimiters				
				word = strtok (NULL, " ,.-?!;");
				x++;
			}
			
		}
	}
	*numOfWords = x;
	
}

// This function takes a string and converts all the characters to lower case
//- target			the word to be converted to lower case
void lowerCaseString(char* target)
{
	int i = 0;
	while(target[i] != '\0')
	{
		target[i] = tolower(target[i]);
		i++;
	}
	
}

//- This function take a string and converts all the characters to upper case
//- target			the word to be converted to upper case
void upperCaseString(char* target)
{
	int i = 0;
	while(target[i] != '\0')
	{
		target[i] = toupper(target[i]);
		i++;
	}
	
}

// This function takes in a word, the dictionary array and the size of the array and
// then using a binary search looks for the word in the dictionary array.
// if the word is not found it returns 0
//- word			the target word to be searched for in the dictionary
//- right			the size of the dictionary array
//- dict			an array of strings that stores each word from the dictionary file
int bSearch(char *word, int right, char **dict)
{
	int mid;
	int first = 0;
	int last = right - 1;
	int match = 0;
	while (first <= last)
	{
		mid = (first + last) / 2;
		// check if the word is the same as the word selected in the dictionary
		match = strcmp(dict[mid], word);
		// if the word matches, it will return the position in the dictionary
		if(match == 0)
		{
			return mid;
		}
		// if the word in the dictionary is less than the word
		else if (match < 0)
		{
			first = mid + 1;
		}
		else
		{
			last = mid - 1;
		}
	}
	// if the word is not found in the dictionary then it will return 0
   return 0;
}

// This function takes the wrong words and outputs them to a file
//- wrongWords		an array of strings that stores the wrong words from the original input
//- numOfWrongWords	stores the number of wrong words in the array wrongWords
//- fileOut 		stores the name of the output file
//- wrongWordLines	stores the line number of each wrong word
void outputToFile(char** wrongWords, int *numOfWrongWords, char *fileOut, int *wrongWordLines)
{
	FILE *outputFile;
	outputFile = fopen(fileOut, "w+");

	for(int i = 0; i < *numOfWrongWords; i++)
	{
		fprintf(outputFile, "LINE %d - %s\n", wrongWordLines[i], wrongWords[i]);
	}
	printf("Wrong words have been sent to: %s\n", fileOut);
   fclose(outputFile);	
}

// This function takes the wrong words and outputs them to the command prompt (console)
//- wrongWords		an array of strings that stores the wrong words from the original input
//- numOfWrongWords	stores the number of wrong words in the array wrongWords
//- wrongWordLines	stores the line number of each wrong word
void outputToConsole(char** wrongWords, int *numOfWrongWords, int *wrongWordLines)
{
	printf("Wrong words:\n");
	
	for(int i = 0; i < *numOfWrongWords; i++)
	{
		printf("LINE %d - %s\n",wrongWordLines[i], wrongWords[i]);
	}
}

// This function frees up the memory used throughout the program once it has finished running
//- lines			an array of strings that stores entire lines individually
//- dict			an array of strings that stores each word from the dictionary file
//- words			an array of strings that stores individual words from each line
//- wrongWords		an array of strings that stores the wrong words from the original input
//- argStrings		stores the actual words from the arguments in the array
//- numOfLines		stores the number of lines in the array
//- sizeOfDict 		stores the number of array elements
//- numOfWords		stores the number of words in the array words
//- numOfWrongWords	stores the number of wrong words in the array wrongWords
//- numOfArgStrings	stores the number of words in argStrings
void freeMemory(char** lines, char** dict, char** words, char** wrongWords, char** argStrings, int *numOfLines, int *sizeOfDict, int *numOfWords, int *numOfWrongWords, int *numOfArgStrings)
{
	// Free dictionary
	for (int i= 0; i < *sizeOfDict; i++)
	{
		free(dict[i]);
	}
	
	// Free user file input
	for (int i=0; i < *numOfLines; i++)
	{
		free(lines[i]);
	}
	
	// Free word list
	for(int i = 0; i < *numOfWords; i++)
	{
		free(words[i]);
	}
	
	// Free wrong words list
	for(int i = 0; i < *numOfWrongWords; i++)
	{
		free(wrongWords[i]);
	}
	
	// Free argument strings list
	for(int i = 0; i < *numOfArgStrings; i++)
	{
		free(argStrings[i]);
	}
}

int main(int argc, char **argv)
{
	printf("Starting...\n");
	printf("--- --- -- SPELL CHECKER -- --- ---\n");
	
	// Arrays
	char *dict[100000];
	char *lines[100000];
	char *words[10000];
	char *wrongWords[10000];
	char *argStrings[10000];
	int wordLines[10000];
	int wrongWordLines[10000];
	
	// Array sizes
	int sizeOfDict = 0;
	int numOfArgStrings = 0;
	int numOfLines = 0;
	int numOfWrongWords = 0;
	int numOfWords = 0;
	
	// Longest word in dictionary
	int longestWord = 0;
	
	// If the value is set to 1, the file name has been input
	int inputExists = 0;
	int outputExists = 0;
	int ignoreCase = 0;
	
	// Input and output file names
	char *fileIn = 0;
	char *fileOut = 0;
	
	loadDictionary(dict, &sizeOfDict, &longestWord);
	
	getArgs(argc, argv, &fileIn, &fileOut, argStrings, &numOfArgStrings, &inputExists, &outputExists, &ignoreCase);
	
	if(inputExists == 1)
	{
		getUserFile(lines, &numOfLines, &fileIn, words, &longestWord, &numOfWords, wordLines);
	}
	else
	{
		getArgWords(argStrings, words, &numOfArgStrings, &longestWord, &numOfWords);
	}
	int j = 0;
	// If the program should not ignore case:
	if(ignoreCase == 0)
	{	
		// Binary Search - Case sensitive
		for(int i = 0; i < numOfWords; i++)
		{
			int result = 0;
			char* word = words[i];
			// If the words begins with a capital letter
			// Check the original word and the word with a lower case letter instead
			// If one of them matches then the word is spelt correctly
			if((word[0] >= 'A') && (word[0] <= 'Z'))
			{
				// check the word as it is originally with the first character capital letter
				int temp1 = bSearch(word, sizeOfDict, dict);
				// checker is a temporary string used to check the 
				// word without affecting the actual word
				char checker[30];
				strcpy(checker, word);
				// convert the first letter of checker to lower case
				checker[0] = tolower(checker[0]);
				// check the word with a the first letter now lowercase
				int temp2 = bSearch(checker, sizeOfDict, dict);
				// If the result is anything other than 0 then it has found the word
				result = temp1 + temp2;
			}
			else
			{
				result = bSearch(word, sizeOfDict, dict);
			}
			
			if(result == 0)
			{
				// Allocate enough memory to store the string in the array
				wrongWords[j] = malloc((strlen(word) + 1) * sizeof(char));
				strcpy(wrongWords[j], word);
				// Get the line number of the word
				wrongWordLines[j] = wordLines[i];
				j++;
			}
		}
	}
	else
	{
		// If the program should ignore case:
		for(int i = 0; i < numOfWords; i++)
		{
			int result = 0;
			char* word = words[i];
			// checker is a temporary string used to check the 
			// word without effecting the actual word
			char checker[30];
			strcpy(checker, word);
			// All letters lower case check
			lowerCaseString(checker);
			int temp1 = bSearch(checker, sizeOfDict, dict);
			// First letter upper case check
			checker[0] = toupper(checker[0]);
			int temp2 = bSearch(checker, sizeOfDict, dict);
			// All letters upper case check
			upperCaseString(checker);
			int temp3 = bSearch(checker, sizeOfDict, dict);
			
			result = temp1 + temp2 + temp3;
			
			if(result == 0)
			{
				// Allocate enough memory to store the string in the array
				wrongWords[j] = malloc((strlen(word) + 1) * sizeof(char));
				strcpy(wrongWords[j], word);
				// Get the line number of the word
				wrongWordLines[j] = wordLines[i];
				j++;
			}
		}
	}
	numOfWrongWords = j;
	
	if(outputExists == 1)
	{
		outputToFile(wrongWords, &numOfWrongWords, fileOut, wrongWordLines);
	}
	else
	{
		outputToConsole(wrongWords, &numOfWrongWords, wrongWordLines);
	}
	
	freeMemory(lines, dict, words, wrongWords, argStrings, &numOfLines, &sizeOfDict, &numOfWords, &numOfWrongWords, &numOfArgStrings);
	
	printf("--- --- --- --- --- --- --- --- ---\n");
	printf("...Complete!\n");
		
	
	return 0;
}