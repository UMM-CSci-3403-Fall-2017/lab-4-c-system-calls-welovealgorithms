#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define BUF_SIZE 1024

bool is_vowel(char c) { 
    /* 
     * Returns true if c is a vowel (upper or lower case), and 
     * false otherwise. 
     */
  char vowels[11] = {'a','e','i','o','u','A','E','I','O','U','\0'};
  
  for(int i = 0; i < 10; i++) {
    if(c == vowels[i]) {
      return true;
    }
  }

  return false;
}

int copy_non_vowels(int num_chars, char* in_buf, char* out_buf) {
    /*
     * Copy all the non-vowels from in_buf to out_buf. 
     * num_chars indicates how many characters are in in_buf, 
     * and this function should return the number of non-vowels that
     * that were copied over.
     */
  int numberOfCopies = 0;

  for(int i = 0; i < num_chars; i++) {
    if(!(is_vowel(in_buf[i]))) {
	out_buf[numberOfCopies] = in_buf[i];
	numberOfCopies++;
      }
  }

    return numberOfCopies;
}

void disemvowel(FILE* inputFile, FILE* outputFile) { 
    /*
     * Copy all the non-vowels from inputFile to outputFile.
     * Create input and output buffers, and use fread() to repeatedly read
     * in a buffer of data, copy the non-vowels to the output buffer, and
     * use fwrite to write that out. 
     */

        char in_buf[BUF_SIZE];
	char out_buf[BUF_SIZE];

	if (inputFile != stdin) {
	  while(fread(in_buf, 1, BUF_SIZE, inputFile) == BUF_SIZE) {
	     int size = copy_non_vowels(sizeof(in_buf), in_buf, out_buf);
	     fwrite(out_buf, 1, size, outputFile);
	  }
	} else {
	  while(feof(inputFile) == 0) {
	    
	  }
	}



	
	
	

	
       
       
}

int main(int argc, char *argv[]) { 
    FILE *inputFile;
    FILE *outputFile;
    
    // Code that processes the command line arguments 
    // and sets up inputFile and outputFile.

    // Check to see if there are 3 arguements given and if so
    // we set the outputFile to open the second arguement for
    // reading and writing
    if(argc >= 3) {
      inputFile = fopen(argv[1], "r");
      outputFile = fopen(argv[2], "w+");
      disemvowel(inputFile, outputFile);
    } else if (argc == 2) {
      inputFile = fopen(argv[1], "r");
      outputFile = stdout;
      disemvowel(inputFile, stdout);
    } else {
      inputFile = stdin;
      outputFile = stdout;
      disemvowel(stdin, stdout);
    }

    fflush(stdout);
    fclose(inputFile);
    fclose(outputFile);

    

    return 0; 
}
