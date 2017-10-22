#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define BUF_SIZE 1024

bool is_vowel(char c) { 
    /* 
     * Returns true if c is a vowel (upper or lower case), and 
     * false otherwise. 
     */
  char vowels[10] = {'a','e','i','o','u','A','E','I','O','U'};

  // Go through the array of vowels
  for(int i = 0; i < 10; i++) {
    
    // If the char c matches a vowel we return true;
    if(c == vowels[i]) {
      return true;
    }
  }
  
  // Return false if no vowels have been found
  return false;
}

int copy_non_vowels(int num_chars, char* in_buf, char* out_buf) {
    /*
     * Copy all the non-vowels from in_buf to out_buf. 
     * num_chars indicates how many characters are in in_buf, 
     * and this function should return the number of non-vowels that
     * that were copied over.
     */
  int non_vowels = 0;

  // Go through the in_buf char*
  for(int i = 0; i < num_chars; i++) {

    // If the element in_buf[i] is not a vowel, we copy it to
    // the out_buf char* and increment our non_vowels count
    if(!(is_vowel(in_buf[i]))) {
	out_buf[non_vowels] = in_buf[i];
	non_vowels++;
      }
  }

  // Return the number of non_vowels
    return non_vowels;
}

void disemvowel(FILE* inputFile, FILE* outputFile) { 
    /*
     * Copy all the non-vowels from inputFile to outputFile.
     * Create input and output buffers, and use fread() to repeatedly read
     * in a buffer of data, copy the non-vowels to the output buffer, and
     * use fwrite to write that out. 
     */

  // Created our in_buf and out_buf buffers with size BUF_SIZE
        char* in_buf = calloc(BUF_SIZE, sizeof(char));
	char* out_buf = calloc(BUF_SIZE, sizeof(char));
	int writeSize;
	int chars;
	bool isRunning = true;
  
	// Read from inputFile to the in_buf as long as there
	// are elements left to read
        while(isRunning) {

	  
	  // Number of elements succesfully read from inputFile
	  chars = fread(in_buf, 1, BUF_SIZE, inputFile);

	  
	  // fread returns 0 if it reaches the end of the file
	  // If we're at the end then stop looping
	  if (chars == 0) {
	    isRunning = false;
	  }
	  

	  // Copy the non-vowels from in_buf to out_buf and returns
	  // the number of non-vowels copied over
	  writeSize = copy_non_vowels(chars, in_buf, out_buf);

	  
	  // Writes to outputFile from out_buf 
	  fwrite(out_buf, 1, writeSize, outputFile);
        }

    // Close the input and output files
    fclose(inputFile);
    fclose(outputFile);

    // Free the allocated buffer memmory
    free(in_buf);
    free(out_buf);

       
}

int main(int argc, char *argv[]) { 
    FILE *inputFile;
    FILE *outputFile;
    
    // Code that processes the command line arguments 
    // and sets up inputFile and outputFile.

    // Check for how many arguements are given
    // and based on that what the input and output
    // files will be assigned
    
    if(argc == 3) {
      inputFile = fopen(argv[1], "r");
      outputFile = fopen(argv[2], "w");
    } else if (argc == 2) {
      inputFile = fopen(argv[1], "r");
      outputFile = stdout;
    } else if (argc == 1) {
      inputFile = stdin;
      outputFile = stdout;
    }

    // Disemvowels the given inputFile and writes it to the outputFile
    disemvowel(inputFile, outputFile);
    	  
    return 0; 
}
