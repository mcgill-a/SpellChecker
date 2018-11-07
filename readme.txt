The spell tool takes in words from either the console or an input file.

It then spell checks the words by using a binary search of each word against
a dictionary file and then outputs the words not in the dictionary (spelt incorrectly)
to either the console or an output file.

If ignore case is typed (-c) then the program will ignore the case that the words are typed
in when spell checking.

---------

The tool chain used for building the program is the "Developer Command Prompt for VS2015"

To use the spell tool, first compile it by typing "cl spell.c" into the command prompt
The tool is now ready to use.

---------

The usage of the tool is as follows:

spell [options]
	-i -- Input file name
	-o -- Output file name
	-c -- Ignore character case

Some example commands:

spell -i sentences_test.txt -o output.txt -c
	This will set:
		the input as sentences_test.txt
		the output as output.txt
		the program to ignore the case of the words

spell -i single_words_test.txt -c
	This will set:
		the input as single_words_test.txt
		the output as the console
		the program to ignore the case of the words

spell -o output.txt This is aa test of theee program.. Yes!
	This will set:
		the input as the words typed into the console
		the output as output.txt
		the program will not ignore the case of the words
