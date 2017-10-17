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
    if(!(is_vowel(in_buf[i])) {
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

  char* in_buf = calloc(BUF_SIZE, sizeof(char));
	char* out_buf = calloc(BUF_SIZE, sizeof(char));
	fopen(inputFile, "w+");
	fopen(outputFile, "w+");
	while(fgets(in_buf,sizeof(in_buf),inputFile)){
		printf("%s\n",in_buf);
	}
	fread(in_buf, 1024, 1, inputFile);
}

int main(int argc, char *argv[]) { 
    FILE *inputFile; 
    FILE *outputFile;

    // Code that processes the command line arguments 
    // and sets up inputFile and outputFile.

    disemvowel(inputFile, outputFile);

    return 0; 
}
