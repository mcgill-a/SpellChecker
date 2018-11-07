all: spell-1 spell-2 spell-3 spell-4 clean

spell-1:
	cl spell.c
	spell -i sentences_test.txt

spell-2:
	cl spell.c
	spell -i sentences_test.txt -c
	
spell-3:
	cl spell.c
	spell -i single_words_test.txt
	
spell-4:
	cl spell.c
	spell -i single_words_test.txt -c
	
clean:
	del *.obj
	del *.exe	